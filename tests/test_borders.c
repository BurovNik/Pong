#include "../unity/unity.h"
#include "../src/borders.h"

void testBordersInitialization(void)
{
    Borders borders;
    bordersInit(&borders, 100, 200);
    TEST_ASSERT_EQUAL_INT(100, borders.height);
    TEST_ASSERT_EQUAL_INT(200, borders.width);
}

void testBordersFailInit(void)
{
    Borders borders;
    int result = bordersInit(&borders, -100, 200);
    TEST_ASSERT_EQUAL_INT(1, result);

    result = bordersInit(&borders, 100, -200);
    TEST_ASSERT_EQUAL_INT(1, result);

    result = bordersInit(&borders, -100, -200);
    TEST_ASSERT_EQUAL_INT(1, result);
}

void testBordersResize(void)
{
    Borders borders;
    bordersInit(&borders, 100, 200);
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