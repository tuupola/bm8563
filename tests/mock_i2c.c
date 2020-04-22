#include <stdint.h>
#include <string.h>

#include "bm8563.h"
#include "mock_i2c.h"

uint8_t memory[BM8563_TIME_SIZE] = {0};

static uint8_t decimal2bcd (uint8_t decimal)
{
    return (((decimal / 10) << 4) | (decimal % 10));
}

static uint8_t bcd2decimal(uint8_t bcd)
{
   return (((bcd >> 4) * 10) + (bcd & 0x0f));
}

int32_t mock_i2c_read(uint8_t address, uint8_t reg, uint8_t *buffer, uint16_t size) {
    memcpy(buffer, memory, size);
    return BM8563_ERROR_OK;
}

int32_t mock_i2c_write(uint8_t address, uint8_t reg, const uint8_t *buffer, uint16_t size) {
    memcpy(memory, buffer, size);
    return BM8563_ERROR_OK;
}

int32_t mock_failing_i2c_read(uint8_t address, uint8_t reg, uint8_t *buffer, uint16_t size) {
    return 3;
}

int32_t mock_failing_i2c_write(uint8_t address, uint8_t reg, const uint8_t *buffer, uint16_t size) {
    return 4;
}
