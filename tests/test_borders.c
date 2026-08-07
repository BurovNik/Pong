#include "../unity/unity.h"
#include "../src/borders.h"

static const int k_height = 100;
static const int k_width = 200;

void testBordersInitialization(void)
{
    Borders borders;
    bordersInit(&borders, k_height, k_width);
    TEST_ASSERT_EQUAL_INT(k_height, borders.height);
    TEST_ASSERT_EQUAL_INT(k_width, borders.width);
}

void testBordersFailInit(void)
{
    Borders borders;
    int result = bordersInit(&borders, -k_height, k_width);
    TEST_ASSERT_EQUAL_INT(1, result);

    result = bordersInit(&borders, k_height, -k_width);
    TEST_ASSERT_EQUAL_INT(1, result);

    result = bordersInit(&borders, -k_height, -k_width);
    TEST_ASSERT_EQUAL_INT(1, result);
}

void testBordersResize(void)
{
    Borders borders;
    bordersInit(&borders, k_height, k_width);
    bordersResize(&borders, 10, 20);
    TEST_ASSERT_EQUAL_INT(10, borders.height);
    TEST_ASSERT_EQUAL_INT(20, borders.width);
}
void testAllBorders(void)
{
    RUN_TEST(testBordersInitialization);
    RUN_TEST(testBordersFailInit);
    RUN_TEST(testBordersResize);
}