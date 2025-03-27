from abutton import *
from servo import *
from mdv2 import *

async def on_abutton_BOOT_pressed():
  await servo1.run_angle(angle=90, speed=100)
  await servo2.run_angle(angle=90, speed=100)
  await servo3.run_angle(angle=180, speed=100)
  await servo4.run_angle(angle=180, speed=100)
  await asleep_ms(3000)
  await servo1.run_angle(angle=5, speed=100)
  await servo2.run_angle(angle=5, speed=100)
  await servo3.run_angle(angle=5, speed=100)
  await servo4.run_angle(angle=5, speed=100)
  await asleep_ms(3000)

btn_BOOT= aButton(BOOT_PIN)
md_v2 = MotorDriverV2()
servo1 = Servo(md_v2, S1, 180)
servo2 = Servo(md_v2, S2, 180)
servo3 = Servo(md_v2, S3, 180)
servo4 = Servo(md_v2, S4, 180)

def deinit():
  btn_BOOT.deinit()

import yolo_uno
yolo_uno.deinit = deinit

async def setup():

  print('App started')
  btn_BOOT.pressed(on_abutton_BOOT_pressed)

async def main():
  await setup()
  while True:
    await asleep_ms(100)

run_loop(main())
