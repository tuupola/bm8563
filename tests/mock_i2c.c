#include <stdint.h>

#include "bm8563.h"
#include "mock_i2c.h"

static uint8_t decimal2bcd (uint8_t decimal)
{
    return (((decimal / 10) << 4) | (decimal % 10));
}

static uint8_t bcd2decimal(uint8_t bcd)
{
   return (((bcd >> 4) * 10) + (bcd & 0x0f));
}

int32_t mock_i2c_read(uint8_t address, uint8_t reg, uint8_t *buffer, uint16_t size) {
    uint8_t bcd;

    /* 0..59 */
    bcd = decimal2bcd(30);
    buffer[0] = bcd & 0b01111111;

    /* 0..59 */
    bcd = decimal2bcd(15);
    buffer[1] = bcd & 0b01111111;

    /* 0..23 */
    bcd = decimal2bcd(23);
    buffer[2] = bcd & 0b00111111;

    /* 1..31 */
    bcd = decimal2bcd(27);
    buffer[3] = bcd & 0b00111111;

    /* 0..6 */
    bcd = decimal2bcd(1);
    buffer[4] = bcd & 0b00000111;

    /* 1..12 */
    bcd = decimal2bcd(11);
    buffer[5] = bcd & 0b00011111;

    /* If 2000 set the century bit. */
    if (106 >= 100) {
        buffer[5] |= BM8563_CENTURY_BIT;
    }

    /* 0..99 */
    bcd = decimal2bcd(106 % 100);
    buffer[6] = bcd & 0b11111111;

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
