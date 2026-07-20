#include "unity.h"
#include "test_ball.h"
#include "test_score.h"
#include "test_borders.h"

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
    return UNITY_END();
}