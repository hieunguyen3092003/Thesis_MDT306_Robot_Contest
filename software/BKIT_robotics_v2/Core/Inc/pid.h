#ifndef INC_PID_H_
#define INC_PID_H_

#include <stdint.h>
#include "encoder.h"
struct PID
{
    float Kp;             // Hệ số tỉ lệ
    float Ki;             // Hệ số tích phân
    float Kd;             // Hệ số vi phân
    int set_speed;        // Pulse per sample_time
    float integral;       // Tích phân lỗi
    float derivative;     // dao ham
    int previous_error;   // Lỗi trước đó
    uint16_t sample_time; // Thời gian lấy mẫu (giây)
};

void initPIDMotor(const enum Encoder encoder_id, const float Kp, const float Ki, const float Kd, const uint16_t sample_time_ms);
void setSpeedPIDMotor(const enum Encoder encoder_id, int speed_pulse_per_sec);
float computePIDMotor(const enum Encoder encoder_id);

#endif /* INC_PID_H_ */
