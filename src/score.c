#include "score.h"
#include <assert.h>
#include <stddef.h>

void scoreInit(Score *score)
{
    assert(score != NULL);
    score->leftScore = 0;
    score->rightScore = 0;
    score->maxScore = 10;
}

int isGameOver(const Score *score)
{
    assert(score != NULL);
    return (score->leftScore >= score->maxScore) || (score->rightScore >= score->maxScore);
}

void increaseLeftScore(Score* score)
{
    assert(score != NULL);
    score->leftScore++;
}

void increaseRightScore(Score *score)
{
    assert(score != NULL);
    score->rightScore++;
}

void resetScore(Score *score)
{
    assert(score != NULL);
    score->leftScore = 0;
    score->rightScore = 0;
}

void setMaxScore(Score *score, int newMaxScore)
{
    assert(score != NULL);
    if (newMaxScore > 0)
    {
        score->maxScore = newMaxScore;
        resetScore(score);
    }

}