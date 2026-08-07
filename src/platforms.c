#include "stdlib.h"
#include "Platforms.h"
#include "borders.h"
#include <assert.h>

int platformInit(Platform *Platform, int height, int width, int speedPlatform, const Borders *field, int isLeft)
{

    assert(Platform != NULL);
    assert(field != NULL);
    int error = 0;
    if(height <= 0 || width <= 0 || speedPlatform <= 0)
    {
        error = 1;
    }else if (height > field->height - 2)
    {
        error = 2;
    }else if (width > field->width - 2)
    {
        error = 3;
    }else
    {  
        Platform->heightPlatforms = height;
        Platform->widthPlatforms = width;
        Platform->speedPlatform = speedPlatform; // скорость тоже одинаковая, но как ее реализовать вводом или она будет статическая еще не понял)
        Platform-> Y = field->height / 2 - Platform->heightPlatforms / 2;
        if(isLeft == 1)
        {
            Platform->X = field->width * 0.1;
        }else
        {
            Platform->X = field->width * 0.9;

        }
    }
    return error;
}
void movePlatform(Platform *Platform, const Borders *field, int isDown)
{
    assert(Platform != NULL);
    assert(field != NULL);
        if(isDown == 1 && Platform->Y + Platform->speedPlatform + Platform->heightPlatforms < field->height)
        {
            Platform->Y += Platform->speedPlatform;
        }else if(isDown == 0 && Platform->Y - Platform->speedPlatform > 0)
        {
            Platform->Y -= Platform->speedPlatform;
        }
}
