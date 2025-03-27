import asyncio
from machine import Pin
from time import tick_ms
from constants import *
from utility import *

class DC_Motor:
    def __init__(self, port):
        self.port = port
        
        self._encoder_enabled = False
        self._rpm = 0
        self._ppr = 0 # pulses per revolution
        self._gears = 0 # pulses per revolution
        self.ticks_per_rev = 0 # encoder ticks count per revolution
        self._max_pps = 0 # max count pulses per second

        # stalled config
        self._stalled_speed = 0.05 # < 5% of max speed considered stalled
        self._stalled_time = 1000 # 1 seconds

        if reversed:
            self._reversed = -1
        else:
            self._reversed = 1
        
        self.reset_angle()