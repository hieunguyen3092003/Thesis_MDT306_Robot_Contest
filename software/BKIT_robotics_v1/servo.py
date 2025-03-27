import asyncio
from machine import Pin, PWM
from constants import S1_PIN, S2_PIN, S3_PIN, S4_PIN, S5_PIN, S6_PIN

class RC_Servo:
    # default values
    __servo_pwm_freq = 50
    __min_u10_duty = 26 - 0 # offset for correction
    __max_u10_duty = 123- 0  # offset for correction
    __Servo_pins = [S1_PIN, S2_PIN, S3_PIN, S4_PIN, S5_PIN, S6_PIN]


    def __init__(self, *args):
        self._min_angle = 0
        if len(args) == 1:
            self._max_angle = 180
        elif len(args) == 2:
            if not (0 < args[1] <= 360):
                raise ValueError("Invalid servo angle value. Must be between 1 and 360.")

            self._max_angle = args[1]
        else: 
            raise ValueError('Invalid number of arguments')

        if args[0] in RC_Servo.__Servo_pins:
            self.__initialise(args[0])
        else:
            raise ValueError(f"Invalid servo pin: {args[0]}")
        
        self._current_angle = None
        
    def __initialise(self, pin):
        self.__limit_min = self._min_angle
        self.__limit_max = self._max_angle

        self._pin = Pin(pin)

        self.__angle_conversion_factor = (self.__max_u10_duty - self.__min_u10_duty) / (self._max_angle - self._min_angle)
        self.__servo = PWM(Pin(pin))
        self.__servo.freq(self.__servo_pwm_freq)

    def _update_settings(self, servo_pwm_freq, min_u10_duty, max_u10_duty, min_angle, max_angle, pin):
        self.__servo_pwm_freq = servo_pwm_freq
        self.__min_u10_duty = min_u10_duty
        self.__max_u10_duty = max_u10_duty
        self._min_angle = min_angle
        self._max_angle = max_angle
        self.__initialise(pin)

    def __angle_to_u10_duty(self, angle):
        return int((angle - self._min_angle) * self.__angle_conversion_factor) + self.__min_u10_duty
    
    @staticmethod
    def __translate_to_delay(speed):
        """
        Chuyển đổi giá trị speed thành độ trễ.
        speed == 100 -> delay = 0.0
        speed == 1 -> delay = 50.0
        """
        if speed < 1 or speed > 100:
            raise ValueError("Speed must be between 1 and 100.")
        
        # Công thức tính độ trễ
        return (100 - speed + 1) * 50.0 / 100
    
    def limit(self, min_angle, max_angle):
        if min_angle < 0 or min_angle > max_angle or max_angle > self._max_angle:
            raise ValueError('Invalid servo limit value')

        self.__limit_min = min_angle
        self.__limit_max = max_angle

    def _move(self, angle):
        angle = int(max(min(self.__limit_max, angle), self.__limit_min))

        if angle == self._current_angle:
            return
        self._current_angle = angle
        duty_u10 = self.__angle_to_u10_duty(angle)
        self.__servo.duty(duty_u10)

    async def move_to(self, angle, speed = 100):
        if speed == 100 or self._current_angle is None:
            self._move(angle)
            return
        
        delay = self.__translate_to_delay(int(speed))

        if self._current_angle > angle:
            for i in range(self._current_angle, angle, -1):
                self._move(i)
                await asyncio.sleep_ms(delay)
        else:
            for i in range(self._current_angle, angle, 1):
                self._move(i)
                await asyncio.sleep_ms(delay)
    
