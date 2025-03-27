# a complete program includes block "on start" and "forever"
# codes make you happy

import asyncio
from machine import Pin
from constants import *
import servo

LED_ONBOARD = Pin(LED_ONBOARD_PIN, Pin.OUT, value=1)
SERVO_1 = servo.RC_Servo(S1_PIN)

async def task_forever():
    while True:
        await asyncio.sleep_ms(50)
        LED_ONBOARD.value(0)
        await asyncio.sleep_ms(1000)
        LED_ONBOARD.value(1)
        await asyncio.sleep_ms(2000)

async def setup():
    print('App started')

    await asyncio.sleep_ms(1000)
    
    await SERVO_1.move_to(0, 100)

    asyncio.create_task(task_forever())

async def main():
    await setup()
    while True:
        await asyncio.sleep_ms(100)

if __name__ == "__main__":
    asyncio.run(main())


