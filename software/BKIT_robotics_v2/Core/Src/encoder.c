#include "encoder.h"

#include "gpio.h"

#ifdef __cplusplus
extern "C"
{
#endif /* __cplusplus */

    GPIO_TypeDef *ENCODER_A_PORT[NUMBER_OF_ENCODER] = {ENCODER1_A_GPIO_Port, ENCODER2_A_GPIO_Port, ENCODER3_A_GPIO_Port, ENCODER4_A_GPIO_Port};
    uint16_t ENCODER_A_PIN[NUMBER_OF_ENCODER] = {ENCODER1_A_Pin, ENCODER2_A_Pin, ENCODER3_A_Pin, ENCODER4_A_Pin};

    uint32_t encoder_pulse_count[NUMBER_OF_ENCODER] = {0};
    GPIO_PinState encoder_pin_a_state[NUMBER_OF_ENCODER] = {GPIO_PIN_RESET};

    /**
     * @brief This function should be called in interupt
     */
    void scanEncoder()
    {
        for (uint8_t i = 0; i < NUMBER_OF_ENCODER; ++i)
        {
            switch (HAL_GPIO_ReadPin(ENCODER_A_PORT[i], ENCODER_A_PIN[i]))
            {
            case GPIO_PIN_SET:
            {
                if (encoder_pin_a_state[i] == GPIO_PIN_RESET)
                {
                    encoder_pin_a_state[i] = GPIO_PIN_SET;

                    if (encoder_pulse_count[i] < 0xFFFFFFFF)
                    {
                        ++encoder_pulse_count[i];
                    }
                    else
                    {
                        encoder_pulse_count[i] = 0;
                    }
                }
                break;
            }
            case GPIO_PIN_RESET:
            {
                if (encoder_pin_a_state[i] == GPIO_PIN_SET)
                {
                    encoder_pin_a_state[i] = GPIO_PIN_RESET;
                }
                break;
            }
            }
        }
    }

    uint32_t getPulseCount(const enum Encoder encoder_id)
    {
        return encoder_pulse_count[encoder_id];
    }

    uint32_t getDeltaEncoder(const enum Encoder encoder_id)
    {
        static uint32_t prev_encoder_pulse_count[NUMBER_OF_ENCODER] = {0};

        uint32_t delta_encoder = encoder_pulse_count[encoder_id] - prev_encoder_pulse_count[encoder_id];

        prev_encoder_pulse_count[encoder_id] = encoder_pulse_count[encoder_id];

        return delta_encoder;
    }

#ifdef __cplusplus
}
#endif /* __cplusplus */