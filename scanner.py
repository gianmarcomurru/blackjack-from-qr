import cv2
import numpy as np
from pyzbar.pyzbar import decode
import serial, time

############# ARDUINO SETTINGS #############
# Assign Arduino's serial port address
#   Windows example
#     usbport = 'COM3'
#   Linux example
#     usbport = '/dev/ttyUSB0'
#   MacOSX example
#     usbport = '/dev/tty.usbserial-FTALLOK2'
usbport = '/dev/cu.usbmodem21201'

ser = serial.Serial(usbport, 9600, timeout=1)

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
        ser.write(bytes(barcodeData, 'utf-8'))
        print("Led blinking {} times".format(barcodeData))
        # time.sleep(0.05)
        time.sleep(2)
        ser.readline()

cap = cv2.VideoCapture(1) # for testing
# cap = cv2.VideoCapture(-1) # for raspberry pi
while True:
    ret, frame = cap.read()
    decoder(frame)
    cv2.imshow('Image', frame)
    code = cv2.waitKey(10)
    if code == ord('q'):
        break