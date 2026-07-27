#ifdef _WIN32
#include "input.h"
#include <conio.h>

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

int input_read_key()
{
    if (!_kbhit()) return -1;

    int c = _getch();
    if (c == 0xE0 || c == 0x00) { // расширенная клавиша
        c = _getch(); // читаем скан-код
        switch (c) {
            case 72: return KEY_UP;
            case 80: return KEY_DOWN;
            case 75: return KEY_LEFT;
            case 77: return KEY_RIGHT;
        }
        return -1; // неизвестная расширенная клавиша
    }
    else if (c == 13) { // Enter
        return KEY_ENTER;
    }
    else if (c == 27) { // ESC
        return KEY_ESC;
    }
    return (unsigned char)c;
}
#endif