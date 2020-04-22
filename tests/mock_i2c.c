#include <stdint.h>

#include "bm8563.h"
#include "mock_i2c.h"

int32_t mock_i2c_read(uint8_t address, uint8_t reg, uint8_t *buffer, uint16_t size) {
    return BM8563_ERROR_OK;
}

int32_t mock_i2c_write(uint8_t address, uint8_t reg, const uint8_t *buffer, uint16_t size) {
    return BM8563_ERROR_OK;
}

int32_t mock_failing_i2c_read(uint8_t address, uint8_t reg, uint8_t *buffer, uint16_t size) {
    return 3;
}

int32_t mock_failing_i2c_write(uint8_t address, uint8_t reg, const uint8_t *buffer, uint16_t size) {
    return 4;
}
