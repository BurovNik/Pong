#include "input.h"
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <termios.h>
#include <fcntl.h>
#include <sys/select.h>

static struct termios old_tio;

void input_init()
{
    struct termios new_tio;
    tcgetattr(STDIN_FILENO, &old_tio);
    new_tio = old_tio;
    new_tio.c_lflag &= ~(ICANON | ECHO);
    tcsetattr(STDIN_FILENO, TCSANOW, &new_tio);
    fcntl(STDIN_FILENO, F_SETFL, O_NONBLOCK);
    

}

void input_restore()
{
    tcsetattr(STDIN_FILENO, TCSANOW, &old_tio);
}

int input_key_pressed()
{
    fd_set fds;
    FD_ZERO(&fds);
    FD_SET(STDIN_FILENO, &fds);
    struct timeval tv = {0, 0};
    return select(STDIN_FILENO + 1, &fds, NULL, NULL, &tv) > 0;
}

char input_read_key()
{
    char c = '\0';
    if (input_key_pressed()) {
        read(STDIN_FILENO, &c, 1);
    }
    return c;
}