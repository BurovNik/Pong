#include "ball.h"
#include <assert.h>
#include "stdlib.h"
#include "math.h"

void ballInit(Ball *ball, float width, float height, float maxSpeed)
{
    assert(ball != NULL);
    ball->maxSpeed = maxSpeed; 
    ballReset(ball, width, height);

}

void ballReset(Ball *ball, float width, float height)
{
    assert(ball != NULL);

    // размещаем  центре
    ball->xCor = width / 2.;
    ball->yCor = height / 2.;

    // задаем скорость
    float angle = (float)rand() / RAND_MAX * 2.0f * 3.14159f; // [0...2PI]
    float minSpeed = ball->maxSpeed * 0.6;
    float speed = minSpeed + (float)rand() / RAND_MAX * (ball->maxSpeed - minSpeed); // minspeed + [0...(maxSpeed - minSpeed)] 

    ball->Vx = speed * cos(angle);
    ball->Vy = speed * sin(angle);

    // Гарантируем, что мяч не полетит строго вертикально/горизонтально
    if (fabs(ball->Vx) < 0.1f) ball->Vx =  (ball->Vx < 0 ? -0.5f : 0.5f);

}

void ballUpdate(Ball *ball, float dt)
{
    assert(ball != NULL);
    ball->xCor += ball->Vx * dt;
    ball->yCor += ball->Vy * dt;

    // ограничение модуля скорости
    float speed = sqrt(ball->Vx * ball->Vx + ball->Vy * ball->Vy);
    if (speed > ball->maxSpeed) {
        float scale = ball->maxSpeed / speed;
        ball->Vx *= scale;
        ball->Vy *= scale;
    }
}

//TODO отскок от ракетки и гол будет расчитываться отдельно
void ballConstrainToField(Ball *ball, float fieldHeight)
{
   assert(ball != NULL);
    // Верхняя и нижняя границы (y от 0 до field_h - 1)
    if (ball->yCor < 0) 
    {
        ball->yCor = 0;
        ballBounceVertical(ball);
    } 
    else if (ball->yCor > fieldHeight - 1) 
    {
        ball->yCor = fieldHeight - 1;
        ballBounceVertical(ball);
    } 
}


void ballBounceVertical(Ball *ball)
{
    assert(ball != NULL);
    ball->Vy = -ball->Vy;
}

void ballBounceHorizontal(Ball *ball)
{
    assert(ball != NULL);
    ball->Vx = -ball->Vx;
}