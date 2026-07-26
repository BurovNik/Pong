#include "input.h"

void input_init()
{

}

void input_restore()
{

}

int input_key_pressed()
{
    return _kbhit();
}

char input_read_key()
{
    if (_kbhit())
        return _getch();
    return '\0';
}