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
    struct tm datetime = {0};
    bm8563_t bm;
    bm.read = &mock_failing_i2c_read;
    bm.write = &mock_i2c_write;

    ASSERT(BM8563_ERROR_OK == bm8563_init(&bm));
    ASSERT_FALSE(BM8563_ERROR_OK == bm8563_read(&bm, &datetime));
    PASS();
}

TEST should_read_and_write_time(void) {
    struct tm datetime = {0};;
    struct tm datetime2 = {0};;
    char buffer[128];
    bm8563_t bm;
    bm.read = &mock_i2c_read;
    bm.write = &mock_i2c_write;

    datetime.tm_sec = 35;
    datetime.tm_min = 15;
    datetime.tm_hour = 23;
    datetime.tm_mday = 27;
    /* Months since January. */
    datetime.tm_mon = 11 - 1;
    /* Years since 1900. */
    datetime.tm_year = 2002 - 1900;

    ASSERT(BM8563_ERROR_OK == bm8563_init(&bm));
    ASSERT(BM8563_ERROR_OK == bm8563_write(&bm, &datetime));
    ASSERT(BM8563_ERROR_OK == bm8563_read(&bm, &datetime2));

    PASS();
}

TEST should_handle_century(void) {
    struct tm datetime = {0};
    struct tm datetime2 = {0};
    char buffer[128];
    bm8563_t bm;
    bm.read = &mock_i2c_read;
    bm.write = &mock_i2c_write;

    datetime.tm_sec = 20;
    datetime.tm_min = 15;
    datetime.tm_hour = 23;
    datetime.tm_mday = 24;
    /* Months since January. */
    datetime.tm_mon = 12 - 1;
    /* Years since 1900. */
    datetime.tm_year = 2006 - 1900;

    ASSERT(BM8563_ERROR_OK == bm8563_init(&bm));
    ASSERT(BM8563_ERROR_OK == bm8563_write(&bm, &datetime));

    ASSERT(BM8563_ERROR_OK == bm8563_read(&bm, &datetime2));

    strftime(buffer, 128 ,"%c (day %j)" , &datetime2);
    ASSERT_STR_EQ("Sun Dec 24 23:15:20 2006 (day 358)", &buffer);
    PASS();
}

GREATEST_MAIN_DEFS();

int main(int argc, char **argv) {
    GREATEST_MAIN_BEGIN();

    RUN_TEST(should_pass);
    RUN_TEST(should_fail_init);
    RUN_TEST(should_init);
    RUN_TEST(should_fail_read_time);
    RUN_TEST(should_read_and_write_time);
    RUN_TEST(should_handle_century);

    GREATEST_MAIN_END();
}
