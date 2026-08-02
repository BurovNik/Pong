#ifndef AIPLAYER_H
#define AIPLAYER_H

#include "ball.h"
// #include "borders.h"  
// #include "platfrom.h" 

// TODO убрать заглушки после мерджа
typedef struct {
    int Y;
    int heightPlatforms;  // высота платформы
} Platform;

typedef struct {
    int height;  // высота поля
} Borders;

void MovePlatform(Platform *Platforms, const Borders* field, int isDown) {}
// вот до сюда

typedef enum {
    E_EASY = 1,
    E_MEDIUM,
    E_HARD,
    E_GODMOD
} AIPlayerLevel;

/// @brief Метод который обрабатывает действия ИИ игрока, при самой низкой сложности будет "забывать" делать ход или делать в другую сторону
/// @param aiPlatform указатель на платформу ИИ игрока
/// @param ball Указатель на мяч
/// @param aiLevel сложность игры
void aiMovePlatform(Platform *aiPlatform, const Ball *ball, const Borders *borders, AIPlayerLevel aiLevel);


#endif //AIPLAYER_H