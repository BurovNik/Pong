#include "../unity/unity.h"
#include "../src/score.h"

void setUp(void) {}
void tearDown(void) {}

void testDefaultScore(void) 
{
    Score s;
    scoreInit(&s);
    TEST_ASSERT_EQUAL_INT(10, s.maxScore);
    TEST_ASSERT_EQUAL_INT(0, s.leftScore);
    TEST_ASSERT_EQUAL_INT(0, s.rightScore);
}


void testIncreaseLeftAndRightPlayer(void)
{
    Score s;
    scoreInit(&s);
    increaseLeftScore(&s);
    TEST_ASSERT_EQUAL_INT(1,s.leftScore);

    increaseRightScore(&s);
    TEST_ASSERT_EQUAL_INT(1, s.rightScore);
}

void testSetMaxScore(void)
{
    Score s;
    scoreInit(&s);
    setMaxScore(&s, 3);
    TEST_ASSERT_EQUAL_INT(3, s.maxScore);
}

void testSetMaxScoreInvalid(void)
{
    Score s;
    scoreInit(&s);
    setMaxScore(&s, -3);
    TEST_ASSERT_EQUAL_INT(10, s.maxScore);
}

void testIsGameOver(void) 
{
    Score s;
    scoreInit(&s);
    for (int i = 0; i < s.maxScore - 1; i++)
        increaseLeftScore(&s);
    TEST_ASSERT_EQUAL_INT(0, isGameOver(&s));

    increaseLeftScore(&s);
    TEST_ASSERT_EQUAL_INT(1, isGameOver(&s));
}

void testResetScore(void)
{
    Score s;
    scoreInit(&s);
    increaseLeftScore(&s);
    increaseRightScore(&s);
    resetScore(&s);
    TEST_ASSERT_EQUAL_INT(0, s.leftScore);
    TEST_ASSERT_EQUAL_INT(0, s.rightScore);
}


int main(void) 
{
    UNITY_BEGIN();
    RUN_TEST(testDefaultScore);
    RUN_TEST(testIncreaseLeftAndRightPlayer);
    RUN_TEST(testSetMaxScore);
    RUN_TEST(testSetMaxScoreInvalid);
    RUN_TEST(testIsGameOver);
    RUN_TEST(testResetScore);
    return UNITY_END();
}