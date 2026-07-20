#include "stdlib.h"
#include "borders.h"
#include <assert.h>

int bordersResize(Borders *borders, int height,int width)
{
    assert(borders != NULL);
    int error = 0;
    if(height <= 0 || width <= 0) 
    {
        error = 1;
    }else{
    borders->height = height;
    borders->width = width;
    borders->scoreX = width / 2 - 3;
    borders->scoreY = height / 25;
    }

    return error;
}

int bordersInit(Borders *borders, int height,int width)
{
    return bordersResize(borders,  height, width); 
}



