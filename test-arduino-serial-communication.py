import serial, time
# Assign Arduino's serial port address
#   Windows example
#     usbport = 'COM3'
#   Raspberry example
# usbport = '/dev/ttyACM0'
#   MacOSX example
usbport = '/dev/cu.usbmodem12301'

# Set up serial baud rate
ser = serial.Serial(usbport, 9600, timeout=1)

while True:
    if ser.in_waiting > 0:
        line = ser.readline().decode('utf-8')
        print(line)
        time.sleep(0.5)
