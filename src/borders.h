#ifndef BORDERS_H
#define BORDERS_H

/// @brief структура поля, которая имеет координаты счета и размеры поля
typedef struct
{
    int height;         // высота поля
    int width;          // ширина поля
    int scoreX;         // координаты по x счета
    int scoreY;         // координаты по y счета
} Borders;

/// @brief метод для инициализации поля         
/// @param borders указатель на поле
/// @param height высота поля
/// @param width ширина поля
/// @return функция сделана так, что она работает с помощью вызова функции bordersResize
int bordersInit(Borders *borders, int height,int width); 

/// @brief метод для изменения размера поля
/// @param borders само поле
/// @param height высота поля
/// @param width ширина поля
/// @return код ошбики 1 если проблема 0 если все правильно
int bordersResize(Borders *borders, int height,int width);

#endif

