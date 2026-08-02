#include "aiplayer.h"
#include <stdlib.h>
#include <math.h>

void aiGodMode(Platform *aiPlatform, const Ball *ball, const Borders *borders)
{
    return;
}

void aiEasyMode(Platform *aiPlatform, int targetY, const Borders *borders)
{
    int random = rand() % 4;
    int currentY = aiPlatform->Y;
    int needDown = (currentY < targetY);
    if (random == 0) // в 25% случаев двигается в "неправильном" направлении
    {
        MovePlatform(aiPlatform, borders, !needDown);
    }
    else if (random == 3) // в 25% случаев двигается куда надо
    {
        MovePlatform(aiPlatform, borders, needDown);
    }
    // 1,2 ничего не делаем
    return;
}

void aiMediumMode(Platform *aiPlatform, int targetY, const Borders *borders)
{
    int random = rand() % 10;
    int currentY = aiPlatform->Y;
    int needDown = currentY < targetY;
    if (random <= 1) // в 20% случаев двигаемся не туда
    {
        MovePlatform(aiPlatform, borders, !needDown);
    } 
    else if (random >= 6) // в 40 % случаев двигаемся куда надо 
    {
        MovePlatform(aiPlatform, borders, needDown);
    }
    // 2 .. 5 не двигаемся в40 % случаев
    return;
}

void aiHardMode(Platform *aiPlatform, int targetY, const Borders *borders)
{
    int random = rand() % 20;
    int currentY = aiPlatform->Y;
    int needDown = currentY < targetY;
    if (random == 0) // в 5% случаев двигаемся не туда
    {
        MovePlatform(aiPlatform, borders, !needDown);
    } 
    else if (random >= 4) // в 80 % случаев двигаемся куда надо 
    {
        MovePlatform(aiPlatform, borders, needDown);
    }
    // 1 .. 3 не двигаемся в40 % случаев
    return;
}

void aiMovePlatform(Platform *aiPlatform, const Ball *ball,const Borders *borders, AIPlayerLevel aiLevel)
{
    float targetY = ball->yCor - aiPlatform->heightPlatforms / 2.0f;
   
    switch (aiLevel)
    {
        case E_GODMOD:
            aiGodMode(aiPlatform, ball, borders);
            break;
        case E_EASY:
            aiEasyMode(aiPlatform, targetY, borders);
            break;
        case E_MEDIUM:
            aiMediumMode(aiPlatform, targetY, borders);
            break;
        case E_HARD:
            aiHardMode(aiPlatform, targetY, borders);
            break;
        default:
            break;
    }

}   
