#ifndef INPUT_H
#define INPUT_H

#define KEY_UP      300
#define KEY_DOWN    301
#define KEY_LEFT    302
#define KEY_RIGHT   303
#define KEY_ENTER   304
#define KEY_ESC     305

/// @brief инициализация для ввода для отдельного использования в *nix системах и в win
void inputInit();

/// @brief метод для восстановления раскладки
void inputRestore();

/// @brief Обработка нажатия на кнопки
/// @return код кнопки
int inputKeyPressed();

/// @brief обрабтка чтения что под этой кнопкой подразумевается
/// @return код кнопки
int inputReadKey();


#endif // INPUT_H
