#ifndef GAME_H
#define GAME_H

#include "ball.h"
#include "score.h"
#include "aiplayer.h"

#define FIELD_WIDTH     80
#define FIELD_HEIGHT    24
#define MAX_SCORE       10
#define PLATFORM_WIDTH   4
#define PLATFORM_HEIGHT  4

typedef enum {
    STATE_MENU,
    STATE_PLAYING,
    STATE_PAUSE,
    STATE_GAME_OVER
} GameState;

typedef struct {
    Ball ball;
    Score score;
    Borders borders;
    Platform leftPlatform;
    Platform rightPlatform;
    AIPlayerLevel aiLevel;
    GameState state;
} Game;

/// @brief Инициализация игры (начальное состояние - меню)
/// @param game указатель на объект игры
void gameInit(Game *game);

/// @brief Старт новой партии с указанной сложностью ИИ
/// @param game указатель на объект игры
/// @param aiLevel сложность ИИ соперника
void gameStart(Game *game, AIPlayerLevel aiLevel);

/// @brief Обработка ввода в зависимости от состояния игры
/// @param game указатель на объект игры
/// @param key код клавиши (из input.h), -1 если клавиш нет
void gameHandleInput(Game *game, int key);

/// @brief Обновление логики игры (мяч, ИИ)
/// @param game указатель на объект игры
/// @param dt прошедший временной промежуток
void gameUpdate(Game *game, float dt);

#endif // GAME_H
