#include "unity.h"
#include "test_ball.h"
#include "test_score.h"
#include "test_menu.h"
#include "test_history.h"

void setUp(void);
void tearDown(void);

int main(void) {
    UNITY_BEGIN();

    // test_ball.c
    printf("\n==================\n test_ball \n==================\n");
    testAllBall();
    
    //test_score.c
    printf("\n==================\n test_score \n==================\n");
    testAllScore();

    //test_menu.c
    printf("\n==================\n test_menu \n==================\n");
    testAllMenu();

    //test_history.c
    printf("\n==================\n test_menu \n==================\n");
    testAllHistory();
    
    return UNITY_END();
}