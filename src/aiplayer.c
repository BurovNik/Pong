#include "aiplayer.h"
#include <stdlib.h>
#include <math.h>

void aiGodMode(Platform *aiPlatform, const Ball *ball, const Borders *borders)
{
    int movingToward = 0; // показывает двигается ли мяч К платформе или от нее 
    int isBallMovingDown = ball->Vy > 0; // показывает двигается ли мяч вверх или вниз
    int targetX;

    if (aiPlatform->X < borders->width / 2.0) // ИИ платформа слева
    {
        movingToward = ball->Vx < 0;
        targetX = aiPlatform->X + 1;
    }
    else // ИИ ракетка справа
    {
        movingToward = ball->Vx > 0;
        targetX = aiPlatform->X - 1;
    }

    if (!movingToward)
        return; // если летит не к платформе - ничего не делаем
    
    int timeToBallArrive = (targetX - ball->xCor) / ball->Vx;

    if (timeToBallArrive < 0) // по идее так не может получиться
        return;

    int predictedY = ball->yCor + timeToBallArrive * ball->Vy;
    while (predictedY < 0 || predictedY > borders->height)
    {
        if (predictedY < 0)
            predictedY = -predictedY;
        else
            predictedY = 2 * borders->height - predictedY;
    }

    int targetY = predictedY - (aiPlatform->Y / 2.);
    if (targetY < 0) 
        targetY = 0;
    if (targetY + aiPlatform->heightPlatforms > borders->height)
        targetY =  borders->height - aiPlatform->heightPlatforms;

    int currentY = aiPlatform->Y;
    if (fabs(currentY - targetY) < 0.5f) // уже на месте
        return; 

    if (currentY < targetY)
        MovePlatform(aiPlatform, borders, 1);
    else
        MovePlatform(aiPlatform, borders, 0);

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
    float targetY = ball->yCor - aiPlatform->heightPlatforms / 2.0f; // targetY такой, чтобы кордината мяча была по центру платформы
   
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
