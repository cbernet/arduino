import serial
arduino = serial.Serial('/dev/ttyACM0', 115200, timeout=0.1)
while True:
    data = arduino.readline().rstrip() #the last bit gets rid of the new-line chars
    if data:
        print data
