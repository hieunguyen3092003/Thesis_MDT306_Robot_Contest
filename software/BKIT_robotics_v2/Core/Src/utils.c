#include "utils.h"

void int32_to_4_uint8(int32_t value, uint8_t *bytes)
{
    value = abs(value);
    bytes[0] = (value >> 24) & 0xFF;
    bytes[1] = (value >> 16) & 0xFF;
    bytes[2] = (value >> 8) & 0xFF;
    bytes[3] = value & 0xFF;
}