#include "../unity/unity.h"
#include "../src/ball.h"

static const float k_width = 100.;
static const float k_height = 200.;
static const float k_maxSpeed = 10.;


void testDefaultBallPosition(void)
{
    Ball ball;
    ballInit(&ball, k_width, k_height, k_maxSpeed);
    TEST_ASSERT_EQUAL_FLOAT(k_width / 2., ball.xCor);
    TEST_ASSERT_EQUAL_FLOAT(k_height / 2., ball.yCor);
    TEST_ASSERT_EQUAL_FLOAT(k_maxSpeed, ball.maxSpeed);
}

void testBallUpdate(void)
{
    Ball ball;
    ballInit(&ball, k_width, k_height, k_maxSpeed);

    ball.xCor = 0;
    ball.yCor = 0;
    ball.Vx = 1;
    ball.Vy = 2;
    ballUpdate(&ball, 1);
    TEST_ASSERT_EQUAL_FLOAT(1, ball.xCor);
    TEST_ASSERT_EQUAL_FLOAT(2, ball.yCor);
}

void testBallBounceVertical(void)
{
    Ball ball;
    ballInit(&ball, k_width, k_height, k_maxSpeed);

    ball.Vx = 1;
    ball.Vy = 2;
    ballBounceVertical(&ball);
    TEST_ASSERT_EQUAL_FLOAT(-2, ball.Vy);

}

void testBallBounceHorizontal(void)
{
    Ball ball;
    ballInit(&ball, k_width, k_height, k_maxSpeed);

    ball.Vx = 1;
    ball.Vy = 2;
    ballBounceHorizontal(&ball);
    TEST_ASSERT_EQUAL_FLOAT(-1, ball.Vx);

}

void testBallReset(void)
{
    Ball ball;
    ballInit(&ball, k_width, k_height, k_maxSpeed);

    ball.xCor = 30.;
    ball.yCor = 30.;

    ballReset(&ball, k_width, k_height);
    TEST_ASSERT_EQUAL_FLOAT(k_width / 2., ball.xCor);
    TEST_ASSERT_EQUAL_FLOAT(k_height / 2., ball.yCor);
}

void testAllBall(void)
{
    RUN_TEST(testDefaultBallPosition);
    RUN_TEST(testBallUpdate);
    RUN_TEST(testBallBounceVertical);
    RUN_TEST(testBallBounceHorizontal);
    RUN_TEST(testBallReset);
}