import cv2
import numpy as np
from pyzbar.pyzbar import decode
import serial, time, os

############# ARDUINO SETTINGS #############
# Assign Arduino's serial port address
#   Windows example
# usb_port = 'COM3'
#   Raspberry example
# usb_port = '/dev/ttyACM0'
#   MacOSX example
# usb_port = '/dev/cu.usbmodem21201'

usb_port = os.environ.get('USB_PORT')
camera = int(os.environ.get('CAMERA'))

ser = serial.Serial(usb_port, 9600, timeout=1)

#############################################


def decoder(image):
    gray_img = cv2.cvtColor(image,0)
    barcode = decode(gray_img)

    for obj in barcode:
        points = obj.polygon
        (x,y,w,h) = obj.rect
        pts = np.array(points, np.int32)
        pts = pts.reshape((-1, 1, 2))
        cv2.polylines(image, [pts], True, (0, 255, 0), 3)

        barcodeData = obj.data.decode("utf-8")
        barcodeType = obj.type
        string = "Data: " + str(barcodeData) + " | Type: " + str(barcodeType)
        
        cv2.putText(frame, string, (x,y), cv2.FONT_HERSHEY_SIMPLEX,0.8,(0,0,255), 2)
        print("Barcode: "+barcodeData +" | Type: "+barcodeType)

        return barcodeData
       

cap = cv2.VideoCapture(camera)

while True:
    if ser.in_waiting > 0:
        msg = ser.readline().decode('utf-8')
        if msg == 'CARD':
            ret, frame = cap.read()
            data = decoder(frame)
            if data:
                ser.write(bytes(data, 'utf-8'))
                print("Led blinking {} times".format(data))
                time.sleep(0.05)

            # if ser.in_waiting > 0:
            #     line = ser.readline().decode('utf-8')
            #     print(line)
            #     ser.readline()

            cv2.imshow('Image', frame)
            code = cv2.waitKey(10)
            if code == ord('q'):
                break
    time.sleep(0.01)