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
usb_port = '/dev/cu.usbmodem21101'

camera = 0 #Depend on your machine, should be between (-1 and 1)

ser = serial.Serial(usb_port, 9600, timeout=1)

#############################################


def decoder(image):
    frame = image
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
        #print("Barcode: "+barcodeData +" | Type: "+barcodeType)

        return barcodeData

def read_card():
    data = None
    while not data:
        ret, frame = cap.read()
        cv2.normalize(frame, frame, 0, 255, cv2.NORM_MINMAX)
        data = decoder(frame)
    return data

cap = cv2.VideoCapture(camera)

def main():
    while True:
        if ser.in_waiting > 0:
            msg = ser.readline().decode('utf-8')
            print("{}".format(msg))
            if msg == 'CARD':
                print("Reading a card...")
                data = read_card()
                if data:
                    ser.write(bytes(data, 'utf-8'))
                    print("It's a {}".format(data))
                    #print("Waiting for messages...")
                    time.sleep(0.05)
        else:
            time.sleep(0.01)

if __name__ == '__main__':
    main()
