#include "test_Platforms.h"
#include "unity.h"
#include "platforms.h"
#include "borders.h"

static const int k_height = 15;
static const int k_width = 1;
static const int k_speedPlatforms = 5;





void testPlatformInit(void)
{
    Platform platformleft;
    Borders field;
    bordersInit(&field, 100, 200);
    int isLeft = 1;
    int result = platformInit(&platformleft, k_height, k_width, k_speedPlatforms, &field, isLeft);
    TEST_ASSERT_EQUAL_INT(0, result);
    TEST_ASSERT_EQUAL_INT(k_height, platformleft.heightPlatforms);
    TEST_ASSERT_EQUAL_INT(k_width, platformleft.widthPlatforms);
    TEST_ASSERT_EQUAL_INT(k_speedPlatforms, platformleft.speedPlatform);
    TEST_ASSERT_EQUAL_INT(field.width * 0.1, platformleft.X);
    TEST_ASSERT_EQUAL_INT(field.height / 2 - platformleft.heightPlatforms / 2, platformleft.Y);

    Platform PlatformRight;
    isLeft = 0;
    result = platformInit(&PlatformRight, k_height, k_width, k_speedPlatforms, &field, isLeft);
    TEST_ASSERT_EQUAL_INT(0, result);
    TEST_ASSERT_EQUAL_INT(k_height, PlatformRight.heightPlatforms);
    TEST_ASSERT_EQUAL_INT(k_width, PlatformRight.widthPlatforms);
    TEST_ASSERT_EQUAL_INT(k_speedPlatforms, PlatformRight.speedPlatform);
    TEST_ASSERT_EQUAL_INT(field.width * 0.9, PlatformRight.X);
    TEST_ASSERT_EQUAL_INT(field.height / 2 - PlatformRight.heightPlatforms / 2, PlatformRight.Y);
}
void testPLatformFailInit(void)
{
    Platform Platformleft;
    Borders field;
    bordersInit(&field, 100, 200);
    int isLeft = 1;
    int result = platformInit(&Platformleft, -k_height, k_width, k_speedPlatforms, &field, isLeft);
    TEST_ASSERT_EQUAL_INT(1, result);

    result = platformInit(&Platformleft, k_height, -k_width, k_speedPlatforms, &field, isLeft);
    TEST_ASSERT_EQUAL_INT(1, result);

    result = platformInit(&Platformleft, k_height, k_width, -k_speedPlatforms, &field, isLeft);
    TEST_ASSERT_EQUAL_INT(1, result);
}
void testMovePlatform(void)
{
    testMoveUpPlatform();
    testMoveDownPlatform();
}
void testMoveUpPlatform(void)
{
    Platform Platformleft;
    Borders field;
    bordersInit(&field, 100, 200);
    int isLeft = 1;
    int result = platformInit(&Platformleft, k_height, k_width, k_speedPlatforms, &field, isLeft);
    TEST_ASSERT_EQUAL_INT(0, result);
    int isDown = 0;
    int yBeforeMove = Platformleft.Y;
    movePlatform(&Platformleft, &field, isDown);
    TEST_ASSERT_EQUAL_INT(yBeforeMove - Platformleft.speedPlatform, Platformleft.Y);
}

void testMoveDownPlatform(void)
{
    Platform platformleft;
    Borders field;
    bordersInit(&field, 100, 200);
    int isLeft = 1;
    int result = platformInit(&platformleft, k_height, k_width, k_speedPlatforms, &field, isLeft);
    TEST_ASSERT_EQUAL_INT(0, result);
    int isDown = 1;
    int yBeforeMove = platformleft.Y;
    movePlatform(&platformleft, &field, isDown);
    TEST_ASSERT_EQUAL_INT(yBeforeMove + platformleft.speedPlatform, platformleft.Y);
}
void testMoveFailUpPlatform(void)
{
    Platform Platformleft;
    Borders field;
    bordersInit(&field, 100, 200);
    int isLeft = 1;
    int result = platformInit(&Platformleft, k_height, k_width, k_speedPlatforms, &field, isLeft);
    TEST_ASSERT_EQUAL_INT(0, result);
    int isDown = 0;
    Platformleft.Y = 0;
    movePlatform(&Platformleft, &field, isDown);
    TEST_ASSERT_EQUAL_INT(0, Platformleft.Y);

}
void testMoveFailDownPlatform(void)
{
    Platform Platformleft;
    Borders field;
    bordersInit(&field, 100, 200);
    int isLeft = 1;
    int result = platformInit(&Platformleft, k_height, k_width, k_speedPlatforms, &field, isLeft);
    TEST_ASSERT_EQUAL_INT(0, result);
    int isDown = 1;
    Platformleft.Y = field.height - Platformleft.heightPlatforms;
    movePlatform(&Platformleft, &field, isDown);
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