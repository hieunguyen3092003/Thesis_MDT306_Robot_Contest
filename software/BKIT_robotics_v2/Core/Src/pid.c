#include "pid.h"

#include <stdlib.h>

#define MAX_REVOLUTIONS_PER_SEC 2

#ifdef __cplusplus
extern "C"
{
#endif /* __cplusplus */

    struct PID pid_motors[NUMBER_OF_ENCODER] = {0};

    void initPIDMotor(const enum Encoder encoder_id, const float Kp, const float Ki, const float Kd, const uint16_t sample_time_ms)
    {
        pid_motors[encoder_id].Kp = Kp;
        pid_motors[encoder_id].Ki = Ki;
        pid_motors[encoder_id].Kd = Kd;
        pid_motors[encoder_id].Kd = Kd;

        pid_motors[encoder_id].set_speed = 0;

        pid_motors[encoder_id].integral = 0;
        pid_motors[encoder_id].derivative = 0;

        pid_motors[encoder_id].previous_error = 0;
        pid_motors[encoder_id].sample_time = sample_time_ms;
    }

    void setSpeedPIDMotor(const enum Encoder encoder_id, int speed_pulse_per_sec)
    {
        if (speed_pulse_per_sec > (MAX_REVOLUTIONS_PER_SEC * PULSE_PER_REVOLUTION))
        {
            speed_pulse_per_sec = (MAX_REVOLUTIONS_PER_SEC * PULSE_PER_REVOLUTION);
        }
        else if (speed_pulse_per_sec < -(MAX_REVOLUTIONS_PER_SEC * PULSE_PER_REVOLUTION))
        {
            speed_pulse_per_sec = -(MAX_REVOLUTIONS_PER_SEC * PULSE_PER_REVOLUTION);
        }

        pid_motors[encoder_id].set_speed = speed_pulse_per_sec * (pid_motors[encoder_id].sample_time * 0.001f);
    }

    float computePIDMotor(const enum Encoder encoder_id)
    {
        // Lấy số xung từ encoder
        uint32_t pulse_count = getDeltaEncoder(encoder_id);

        // Tính lỗi
        float error = (abs(pid_motors[encoder_id].set_speed) - abs(pulse_count)) * (pid_motors[encoder_id].set_speed / abs(pid_motors[encoder_id].set_speed));

        // Cập nhật tích phân
        pid_motors[encoder_id].integral += error * pid_motors[encoder_id].sample_time;

        // Tính vi phân
        pid_motors[encoder_id].derivative = (error - pid_motors[encoder_id].previous_error) / pid_motors[encoder_id].sample_time;

        float output = pid_motors[encoder_id].Kp * error + pid_motors[encoder_id].Ki * pid_motors[encoder_id].integral + pid_motors[encoder_id].Kd * pid_motors[encoder_id].derivative;

        pid_motors[encoder_id].previous_error = error;

        return output;
    }

#ifdef __cplusplus
}
#endif /* __cplusplus */