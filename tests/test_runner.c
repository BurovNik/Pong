#include "unity.h"
#include "test_ball.h"
#include "test_score.h"
#include "test_borders.h"
#include "test_Platforms.h"

void setUp(void) {}
void tearDown(void) {}

int main(void) {
    UNITY_BEGIN();

    // test_ball.c
    printf("\n==================\n test_ball \n==================\n");
    testAllBall();
    
    //test_score.c
    printf("\n==================\n test_score \n==================\n");
    testAllScore();

    //test_borders.c
    printf("\n==================\n test_Borders \n==================\n");
    testAllBorders();

    //test_platforms.c
    printf("\n==================\n test_Platforms \n==================\n");
    testPlatformsAll();
    return UNITY_END();
}