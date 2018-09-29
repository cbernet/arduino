#!/usr/bin/python
import sys
import time
from arduino import Arduino

ard = Arduino()

ard.pinMode(13, ard.OUTPUT)

val = int(sys.argv[1])
if val == 1:
    ard.digitalWrite(13, ard.HIGH)
elif val == 0:
    ard.digitalWrite(13, ard.LOW)
