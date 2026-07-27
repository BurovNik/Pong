#ifndef INPUT_H
#define INPUT_H

#define KEY_UP      300
#define KEY_DOWN    301
#define KEY_LEFT    302
#define KEY_RIGHT   303
#define KEY_ENTER   304
#define KEY_ESC     305

void input_init();
void input_restore();
int input_key_pressed();
int input_read_key();


#endif // INPUT_H
