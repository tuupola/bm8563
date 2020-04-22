#include "greatest.h"
#include "bm8563.h"
#include "mock_i2c.h"

TEST should_pass(void) {
    PASS();
}

TEST i2c_init_should_fail(void) {
    bm8563_t bm;
    uint32_t status;
    bm.read = &mock_failing_i2c_read;
    bm.write = &mock_failing_i2c_write;

    ASSERT_FALSE(BM8563_ERROR_OK == bm8563_init(&bm));
}

TEST i2c_init_should_pass(void) {
    bm8563_t bm;
    bm.read = &mock_i2c_read;
    bm.write = &mock_i2c_write;

    ASSERT(BM8563_ERROR_OK == bm8563_init(&bm));
}

GREATEST_MAIN_DEFS();

int main(int argc, char **argv) {
    GREATEST_MAIN_BEGIN();

    RUN_TEST(should_pass);
    RUN_TEST(i2c_init_should_fail);
    RUN_TEST(i2c_init_should_pass);

    GREATEST_MAIN_END();
}
