#ifndef PLATFORMS_H
#define PLATFORMS_H

typedef struct             /// структура для подвижный платформ
{
    int Y;                 /// координата для вертикали
    int X;                 /// координата для горизонатли
    int widthPlatforms;             /// ширина платформы
    int heightPlatforms;            /// высота платформы
    int speedPlatform;     /// скорость передвижения платформы
}Platforms;

/// @brief метод для инициализации платформ
/// @param Platforms указатель на платформы
/// @param width ширина платформы
/// @param height высота платформы
/// @param speedPlatform скорость передвижения платформы
/// @return код ошбики 1 если проблема 0 если все правильно
int PlatformInit(Platforms *Platforms, int height, int width, int speedPlatform, Borders* field, int isLeft); 

int MovePlatform(Platforms *Platforms, Borders* field, int isDown);
#endif