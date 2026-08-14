#include "input.h"
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <termios.h>
#include <fcntl.h>
#include <sys/select.h>

static struct termios old_tio;

void inputInit()
{
    struct termios new_tio;
    tcgetattr(STDIN_FILENO, &old_tio);
    new_tio = old_tio;
    new_tio.c_lflag &= ~(ICANON | ECHO);
    tcsetattr(STDIN_FILENO, TCSANOW, &new_tio);
    fcntl(STDIN_FILENO, F_SETFL, O_NONBLOCK);
    

}

void inputRestore()
{
    tcsetattr(STDIN_FILENO, TCSANOW, &old_tio);
}

int inputKeyPressed()
{
    fd_set fds;
    FD_ZERO(&fds);
    FD_SET(STDIN_FILENO, &fds);
    struct timeval tv = {0, 0};
    return select(STDIN_FILENO + 1, &fds, NULL, NULL, &tv) > 0;
}

int inputReadKey()
{
    if (!inputKeyPressed())
        return -1;

    char c; 
    read(STDIN_FILENO, &c, 1);

    if (c == 27) // обработка стрелок стрелк при считывании с клавиш тоже начинается с кода ESC
    {
        usleep(10000);
        if (inputKeyPressed())
        {
            char c2;
            read(STDIN_FILENO, &c2, 1);
            if (c2 == '[')
            {
                if (inputKeyPressed())
                {
                    char c3;
                    read(STDIN_FILENO, &c3, 1);
                    switch (c3)
                    {
                    case 'A':
                        return KEY_UP;
                        break;
                    case 'B':
                        return KEY_DOWN;
                        break;
                    case 'C':
                        return KEY_RIGHT;
                        break;
                    case 'D':
                        return KEY_LEFT;
                        break;
                    default:
                        break;
                    }
                }
            }
        }
        return KEY_ESC;
    }
    else if (c == '\r' || c == '\n')
    {
        return KEY_ENTER;
    }
    return (unsigned char)c;
    
}