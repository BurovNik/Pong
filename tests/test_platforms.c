#include "test_Platforms.h"
#include "unity.h"
#include "platforms.h"
#include "borders.h"

static const int k_height = 15;
static const int k_width = 1;
static const int k_speedPlatforms = 5;





void testPlatformInit(void)
{
    Platforms Platformleft;
    Borders field;
    bordersInit(&field, 100, 200);
    int isLeft = 1;
    int result = PlatformInit(&Platformleft, k_height, k_width, k_speedPlatforms, &field, isLeft);
    TEST_ASSERT_EQUAL_INT(0, result);
    TEST_ASSERT_EQUAL_INT(k_height, Platformleft.heightPlatforms);
    TEST_ASSERT_EQUAL_INT(k_width, Platformleft.widthPlatforms);
    TEST_ASSERT_EQUAL_INT(k_speedPlatforms, Platformleft.speedPlatform);
    TEST_ASSERT_EQUAL_INT(field.width * 0.1, Platformleft.X);
    TEST_ASSERT_EQUAL_INT(field.height / 2 - Platformleft.heightPlatforms / 2, Platformleft.Y);

    Platforms PlatformRight;
    isLeft = 0;
    result = PlatformInit(&PlatformRight, k_height, k_width, k_speedPlatforms, &field, isLeft);
    TEST_ASSERT_EQUAL_INT(0, result);
    TEST_ASSERT_EQUAL_INT(k_height, PlatformRight.heightPlatforms);
    TEST_ASSERT_EQUAL_INT(k_width, PlatformRight.widthPlatforms);
    TEST_ASSERT_EQUAL_INT(k_speedPlatforms, PlatformRight.speedPlatform);
    TEST_ASSERT_EQUAL_INT(field.width * 0.9, PlatformRight.X);
    TEST_ASSERT_EQUAL_INT(field.height / 2 - PlatformRight.heightPlatforms / 2, PlatformRight.Y);
}
void testPLatformFailInit(void)
{
    Platforms Platformleft;
    Borders field;
    bordersInit(&field, 100, 200);
    int isLeft = 1;
    int result = PlatformInit(&Platformleft, -k_height, k_width, k_speedPlatforms, &field, isLeft);
    TEST_ASSERT_EQUAL_INT(1, result);

    result = PlatformInit(&Platformleft, k_height, -k_width, k_speedPlatforms, &field, isLeft);
    TEST_ASSERT_EQUAL_INT(1, result);

    result = PlatformInit(&Platformleft, k_height, k_width, -k_speedPlatforms, &field, isLeft);
    TEST_ASSERT_EQUAL_INT(1, result);
}
void testMovePlatform(void)
{
    testMoveUpPlatform();
    testMoveDownPlatform();
}
void testMoveUpPlatform(void)
{
    Platforms Platformleft;
    Borders field;
    bordersInit(&field, 100, 200);
    int isLeft = 1;
    int result = PlatformInit(&Platformleft, k_height, k_width, k_speedPlatforms, &field, isLeft);
    TEST_ASSERT_EQUAL_INT(0, result);
    int isDown = 0;
    int yBeforeMove = Platformleft.Y;
    MovePlatform(&Platformleft, &field, isDown);
    TEST_ASSERT_EQUAL_INT(yBeforeMove - Platformleft.speedPlatform, Platformleft.Y);
}

void testMoveDownPlatform(void)
{
    Platforms Platformleft;
    Borders field;
    bordersInit(&field, 100, 200);
    int isLeft = 1;
    int result = PlatformInit(&Platformleft, k_height, k_width, k_speedPlatforms, &field, isLeft);
    TEST_ASSERT_EQUAL_INT(0, result);
    int isDown = 1;
    int yBeforeMove = Platformleft.Y;
    MovePlatform(&Platformleft, &field, isDown);
    TEST_ASSERT_EQUAL_INT(yBeforeMove + Platformleft.speedPlatform, Platformleft.Y);
}
void testMoveFailUpPlatform(void)
{
    Platforms Platformleft;
    Borders field;
    bordersInit(&field, 100, 200);
    int isLeft = 1;
    int result = PlatformInit(&Platformleft, k_height, k_width, k_speedPlatforms, &field, isLeft);
    TEST_ASSERT_EQUAL_INT(0, result);
    int isDown = 0;
    Platformleft.Y = 0;
    MovePlatform(&Platformleft, &field, isDown);
    TEST_ASSERT_EQUAL_INT(0, Platformleft.Y);

}
void testMoveFailDownPlatform(void)
{
    Platforms Platformleft;
    Borders field;
    bordersInit(&field, 100, 200);
    int isLeft = 1;
    int result = PlatformInit(&Platformleft, k_height, k_width, k_speedPlatforms, &field, isLeft);
    TEST_ASSERT_EQUAL_INT(0, result);
    int isDown = 1;
    Platformleft.Y = field.height - Platformleft.heightPlatforms;
    MovePlatform(&Platformleft, &field, isDown);
    TEST_ASSERT_EQUAL_INT(field.height - Platformleft.heightPlatforms, Platformleft.Y);
}
void testPlatformsAll(void)
{
    RUN_TEST(testPlatformInit);
    RUN_TEST(testPLatformFailInit);
    RUN_TEST(testMoveFailUpPlatform);
    RUN_TEST(testMoveFailDownPlatform);
    RUN_TEST(testMovePlatform);
    RUN_TEST(testMoveDownPlatform);
    RUN_TEST(testMoveUpPlatform);
}