import time
from neopixel import NeoPixel
from machine import Pin

class RGBLed:
    def __init__(self, pin, num_leds):
        self._np = NeoPixel(Pin(pin), num_leds, 3, 1)
        self._num_leds = num_leds

    def show(self, index, color, delay=None):
        if index == 0:
            for i in range(self._num_leds):
                self._np[i] = color
            self._np.write()
        elif (index > 0) and (index <= self._num_leds) :
            self._np[index - 1] = color
            self._np.write()
        
        if delay != None:
            time.sleep(delay)
            if index == 0:
                for i in range(self._num_leds):
                    self._np[i] = (0, 0, 0)
                self._np.write()
            elif (index > 0) and (index <= self._num_leds) :
                self._np[index - 1] = (0, 0, 0)
                self._np.write()

    def off(self, index):
        self.show(index, (0, 0, 0))