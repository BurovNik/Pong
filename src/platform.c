#include "stdlib.h"
#include "Platforms.h"
#include <assert.h>

int PlatformInit(Platforms *Platforms, int height, int width, int speedPlatform)
{
    assert(Platforms != NULL);
    int error = 0;
    if(height <= 0 || width <= 0 || speedPlatform <= 0)
    {
        error = 1;
    }else
    {
    Platforms->height = height;
    Platforms->width = width;
    Platforms->speedPlatform = speedPlatform; // скорость тоже одинаковая, но как ее реализовать вводом или она будет статическая еще не понял)
    Platforms->leftY / 5 - 15 ; // если я не тупой то тут получется по вертикальной оси 5
    Platforms->rightY / 5 + 90; // тут, если также не тупой то по вертикали 95
    // у обеих платформ отступ от левой и правойграницы 5, ЕСЛИ Я НЕ ТУПОЙ!
    Platforms->X / 5 - 15; // это по горизонтали, у них одна точка, чтобы были напротив друг друга
    }
    return error;
}