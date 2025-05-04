#ifndef INC_UTILS_H_
#define INC_UTILS_H_

#include <stdint.h>
#include <stdlib.h>

void uint32_to_bytes(const uint32_t *input_32b, uint8_t *output_8b, const uint8_t input_size);
void uint16_to_bytes(const uint16_t *input_16b, uint8_t *output_8b, const uint8_t input_size);

#endif /* INC_UTILS_H_ */
