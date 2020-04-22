#include "greatest.h"
#include "bm8563.h"
#include "mock_i2c.h"

TEST should_pass(void) {
    PASS();
}

TEST should_fail_init(void) {
    bm8563_t bm;
    uint32_t status;
    bm.read = &mock_failing_i2c_read;
    bm.write = &mock_failing_i2c_write;

    ASSERT_FALSE(BM8563_ERROR_OK == bm8563_init(&bm));
    PASS();
}

TEST should_init(void) {
    bm8563_t bm;
    bm.read = &mock_i2c_read;
    bm.write = &mock_i2c_write;

    ASSERT(BM8563_ERROR_OK == bm8563_init(&bm));
    PASS();
}

TEST should_fail_read_date(void) {
    struct tm rtc;
    bm8563_t bm;
    bm.read = &mock_failing_i2c_read;
    bm.write = &mock_i2c_write;

    ASSERT(BM8563_ERROR_OK == bm8563_init(&bm));
    ASSERT_FALSE(BM8563_ERROR_OK == bm8563_read(&bm, &rtc));
    PASS();
}

TEST should_read_date(void) {
    struct tm rtc;
    char buffer[128];
    bm8563_t bm;
    bm.read = &mock_i2c_read;
    bm.write = &mock_i2c_write;

    ASSERT(BM8563_ERROR_OK == bm8563_init(&bm));
    ASSERT(BM8563_ERROR_OK == bm8563_read(&bm, &rtc));

    strftime(buffer, 128 ,"%c (day %j)" , &rtc);
    ASSERT_STR_EQ("Mon Nov 27 23:15:30 2006 (day 331)", &buffer);
    PASS();
}

GREATEST_MAIN_DEFS();

int main(int argc, char **argv) {
    GREATEST_MAIN_BEGIN();

    RUN_TEST(should_pass);
    RUN_TEST(should_fail_init);
    RUN_TEST(should_init);
    RUN_TEST(should_fail_read_date);
    RUN_TEST(should_read_date);

    GREATEST_MAIN_END();
}
