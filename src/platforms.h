#ifndef PLATFORMS_H
#define PLATFORMS_H

typedef struct  /// структура для подвижный платформ
{
    int leftY;             /// координата для левой платформы
    int rightY;            /// координата для правой платформы
    int X;                 /// общая координата для обеих платформ, чтобы они находились между собой
    int width;             /// ширина платформы
    int height;            /// высота платформы
    int speedPlatform;     /// скорость передвижения платформы
}Platforms;

/// @brief метод для инициализации платформ
/// @param Platforms указатель на платформы
/// @param width ширина платформы
/// @param height высота платформы
/// @param speedPlatform скорость передвижения платформы
/// @return код ошбики 1 если проблема 0 если все правильно
int PlatformInit(Platforms *Platforms, int height, int width, int speedPlatform); 
#endif