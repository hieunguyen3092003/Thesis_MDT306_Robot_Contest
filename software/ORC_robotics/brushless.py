import asyncio
from machine import PWM, Pin
from utility import *
from mdv2 import *

class Brushless:
    def __init__(self, *args):
        if len(args) == 3:
            if isinstance(args[0], MotorDriverV2):
                self._driver = args[0]
                self._port = int(args[1])
                self._max_angle = int(args[2])
            else:
                raise ValueError('Invalid brushless argument')

        elif len(args) == 2:
            if isinstance(args[0], int):
                self._port = PWM(Pin(int(args[0])))
                self._port.freq(50)
                self._driver = None
                self._max_angle = int(args[1])
            else:
                raise ValueError('Invalid brushless argument')


    def speed(self, speed):
        _speed = translate(speed, 0, 100, 50, 100)
        #50-100

        if self._driver:
            self._driver.set_servo(self._port, _speed, 180)
        else:
            self._port.duty(_speed)