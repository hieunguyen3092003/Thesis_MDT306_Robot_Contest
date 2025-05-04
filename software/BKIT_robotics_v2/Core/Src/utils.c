#include "utils.h"

/**
 * @brief Convert a 32-bit unsigned integer to bytes
 * @param input_32b The input unsigned integer
 * @param output_8b The output byte array in big-endian format
 * @note The output array should be at least 4*input_size bytes long
 * uint32_t input_32[] = {0x12345678, 0x9ABCDEF0};
 * uint32_to_bytes → [0x12, 0x34, 0x56, 0x78, 0x9A, 0xBC, 0xDE, 0xF0]
 */
void uint32_to_bytes(const uint32_t *input_32b, uint8_t *output_8b, const uint8_t input_size)
{
    for (uint8_t i = 0; i < input_size; i++)
    {
        output_8b[4 * i] = (input_32b[i] >> 24) & 0x000000FF;
        output_8b[4 * i + 1] = (input_32b[i] >> 16) & 0x000000FF;
        output_8b[4 * i + 2] = (input_32b[i] >> 8) & 0x000000FF;
        output_8b[4 * i + 3] = input_32b[i] & 0x000000FF;
    }
}

/**
 * @brief Convert a 16-bit unsigned integer to bytes
 * @param input The input unsigned integer
 * @param output The output byte array in big-endian format
 * @note The output array should be at least 2*input_size bytes long
 * uint16_t input_16[] = {0x1234, 0x5678};
 * uint16_to_bytes → [0x12, 0x34, 0x56, 0x78]
 */
void uint16_to_bytes(const uint16_t *input_16b, uint8_t *output_8b, const uint8_t input_size)
{
    for (uint8_t i = 0; i < input_size; i++)
    {
        output_8b[2 * i] = (input_16b[i] >> 8) & 0x00FF;
        output_8b[2 * i + 1] = input_16b[i] & 0x00FF;
    }
}
