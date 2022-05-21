import serial, time
# Assign Arduino's serial port address
#   Windows example
#     usbport = 'COM3'
#   Linux example
#     usbport = '/dev/ttyUSB0'
#   MacOSX example
#     usbport = '/dev/tty.usbserial-FTALLOK2'
usbport = '/dev/cu.usbmodem21201'

# Set up serial baud rate
ser = serial.Serial(usbport, 9600, timeout=1)

while True:
    a=input("How many time should I blink? ").strip()
    
    ser.write(bytes(a, 'utf-8'))
    time.sleep(0.05)
    ser.readline()