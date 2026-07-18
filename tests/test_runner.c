#include "unity.h"
#include "test_ball.h"
#include "test_score.h"

void setUp(void) {}
void tearDown(void) {}

int main(void) {
    UNITY_BEGIN();

    // test_ball.c
    printf("\n==================\n test_ball \n==================\n");
    RUN_TEST(testDefaultBallPosition);
    RUN_TEST(testBallUpdate);
    RUN_TEST(testBallBounceVertical);
    RUN_TEST(testBallBounceHorizontal);
    RUN_TEST(testBallReset);

    //test_score.c
    printf("\n==================\n test_score \n==================\n");
    RUN_TEST(testDefaultScore);
    RUN_TEST(testIncreaseLeftAndRightPlayer);
    RUN_TEST(testSetMaxScore);
    RUN_TEST(testSetMaxScoreInvalid);
    RUN_TEST(testIsGameOver);
    RUN_TEST(testResetScore);

    //test_score.c
    return UNITY_END();
}