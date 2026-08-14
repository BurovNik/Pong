#ifndef AIPLAYER_H
#define AIPLAYER_H

#include "ball.h"
// #include "borders.h"  
// #include "platfrom.h" 

// TODO убрать заглушки после мерджа
typedef struct {
    int X;
    int Y;
    int heightPlatforms;  // высота платформы
} Platform;

typedef struct {
    int width;
    int height;  // высота поля
} Borders;

void MovePlatform(Platform *Platforms, const Borders* field, int isDown);
// вот до сюда

typedef enum {
    E_EASY = 0,
    E_MEDIUM,
    E_HARD,
    E_GODMOD
} AIPlayerLevel;

/// @brief Метод который обрабатывает действия ИИ игрока, при самой низкой сложности будет "забывать" делать ход или делать в другую сторону
/// @param aiPlatform указатель на платформу ИИ игрока
/// @param ball Указатель на мяч
/// @param aiLevel сложность игры
void aiMovePlatform(Platform *aiPlatform, const Ball *ball, const Borders *borders, AIPlayerLevel aiLevel);

/// @brief Метод для получения количества уровней сложности ИИ
/// @return количество уровней сложности ИИ
int aiGetLevelCount(void);

/// @brief Метод для получения названия уровня сложности ИИ
/// @param index индекс сложности
/// @return 
const char* aiGetLevelName(int index);

/// @brief Функция для получения уровня игры по индексу
/// @param index индекс, как в меню
/// @return уровень игры
AIPlayerLevel aiGetLevelByIndex(int index);

#endif //AIPLAYER_H