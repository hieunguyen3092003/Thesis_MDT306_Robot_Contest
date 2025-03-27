# This file is executed on every boot (including wake-boot from deepsleep)
import os, time, gc, esp, sys, asyncio
from machine import Pin, reset
from neopixel import NeoPixel

from setting import *
from utility import *
from yolo_uno import *

esp.osdebug(None)

print('Firmware version:', VERSION)

def stop_all():
  pass

from ble import *
ble.start()