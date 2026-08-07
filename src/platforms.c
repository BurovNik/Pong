#include "stdlib.h"
#include "platforms.h"
#include "borders.h"
#include <assert.h>

int platformInit(Platform *platform, int height, int width, int speedPlatform, const Borders *field, int isLeft)
{

    assert(platform != NULL);
    assert(field != NULL);
    int error = 0;
    if(height <= 0 || width <= 0 || speedPlatform <= 0)
    {
        error = 1;
    }else if (height > field->height - 2)
    {
        error = 1;
    }else if (width > field->width - 2)
    {
        error = 1;
    }else
    {  
        platform->heightPlatform = height;
        platform->widthPlatform = width;
        platform->speedPlatform = speedPlatform; // скорость тоже одинаковая, но как ее реализовать вводом или она будет статическая еще не понял)
        platform-> Y = field->height / 2 - platform->heightPlatform / 2;
        if(isLeft == 1)
        {
            platform->X = field->width * 0.1;
        }else
        {
            platform->X = field->width * 0.9;

        }
    }
    return error;
}
void movePlatform(Platform *Platform, const Borders *field, int isDown)
{
    assert(Platform != NULL);
    assert(field != NULL);
        if(isDown == 1 && Platform->Y + Platform->speedPlatform + Platform->heightPlatform < field->height)
        {
            Platform->Y += Platform->speedPlatform;
        }else if(isDown == 0 && Platform->Y - Platform->speedPlatform > 0)
        {
            Platform->Y -= Platform->speedPlatform;
        }
}
