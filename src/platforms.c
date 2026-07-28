#include "stdlib.h"
#include "Platforms.h"
#include "borders.h"
#include <assert.h>

int PlatformInit(Platforms *Platforms, int height, int width, int speedPlatform, Borders* field, int isLeft)
{

    assert(Platforms != NULL);
    assert(field != NULL);
    int error = 0;
    if(height <= 0 || width <= 0 || speedPlatform <= 0)
    {
        error = 1;
    }else
    {  
        Platforms->heightPlatforms = height;
        Platforms->widthPlatforms = width;
        Platforms->speedPlatform = speedPlatform; // скорость тоже одинаковая, но как ее реализовать вводом или она будет статическая еще не понял)
        Platforms-> Y = field->height / 2 - Platforms->heightPlatforms / 2;
        if(isLeft == 1)
        {
            Platforms->X = field->width * 0.1;
        }else
        {
            Platforms->X = field->width * 0.9;

        }
    }
    return error;
}
int MovePlatform(Platforms *Platforms, Borders* field, int isDown)
{
    assert(Platforms != NULL);
    assert(field != NULL);
        if(isDown == 1 && Platforms->Y + Platforms->speedPlatform + Platforms->heightPlatforms < field->height)
        {
            Platforms->Y += Platforms->speedPlatform;
        }else if(isDown == 0 && Platforms->Y - Platforms->speedPlatform > field->height)
        {
            Platforms->Y -= Platforms->speedPlatform;
        }
        
    return 0;
}
