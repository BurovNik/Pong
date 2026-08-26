#ifndef PLATFORMS_H
#define PLATFORMS_H
#include "borders.h"

typedef struct             /// структура для подвижный платформ
{
    int Y;                 /// координата для вертикали
    int X;                 /// координата для горизонатли
    int widthPlatform;    /// ширина платформы
    int heightPlatform;   /// высота платформы
    int speedPlatform;     /// скорость передвижения платформы
}Platform;

/// @brief метод для инициализации платформ
/// @param Platform указатель на платформы
/// @param width ширина платформы
/// @param height высота платформы
/// @param speedPlatform скорость передвижения платформы
/// @return код ошбики 1 если проблема 0 если все правильно
int platformInit(Platform *platform, int height, int width, int speedPlatform, const Borders *field, int isLeft); 

/// @brief метод для изменение платформ
/// @param Platform указатель на платфомры
/// @param field указатель на поле
/// @param isDown перемещение вниз
void movePlatform(Platform *platform, const Borders *field, int isDown);
#endif
