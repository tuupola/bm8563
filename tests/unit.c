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

TEST should_fail_read_time(void) {
    struct tm time;
    bm8563_t bm;
    bm.read = &mock_failing_i2c_read;
    bm.write = &mock_i2c_write;

    ASSERT(BM8563_ERROR_OK == bm8563_init(&bm));
    ASSERT_FALSE(BM8563_ERROR_OK == bm8563_read(&bm, &time));
    PASS();
}

TEST should_write_time(void) {
    struct tm time;
    char buffer[128];
    bm8563_t bm;
    bm.read = &mock_i2c_read;
    bm.write = &mock_i2c_write;

    time.tm_sec = 30;
    time.tm_min = 15;
    time.tm_hour = 23;
    time.tm_mday = 27;
    time.tm_mon = 11 - 1;
    time.tm_year = 2006;

    ASSERT(BM8563_ERROR_OK == bm8563_init(&bm));
    ASSERT(BM8563_ERROR_OK == bm8563_write(&bm, &time));
    PASS();
}

TEST should_read_time(void) {
    struct tm time;
    char buffer[128];
    bm8563_t bm;
    bm.read = &mock_i2c_read;
    bm.write = &mock_i2c_write;

    ASSERT(BM8563_ERROR_OK == bm8563_init(&bm));
    ASSERT(BM8563_ERROR_OK == bm8563_read(&bm, &time));

    strftime(buffer, 128 ,"%c (day %j)" , &time);
    ASSERT_STR_EQ("Mon Nov 27 23:15:30 2006 (day 331)", &buffer);
    PASS();
}
GREATEST_MAIN_DEFS();

int main(int argc, char **argv) {
    GREATEST_MAIN_BEGIN();

    RUN_TEST(should_pass);
    RUN_TEST(should_fail_init);
    RUN_TEST(should_init);
    RUN_TEST(should_fail_read_time);
    RUN_TEST(should_write_time);
    RUN_TEST(should_read_time);

    GREATEST_MAIN_END();
}
