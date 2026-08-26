#ifndef RENDER_H
#define RENDER_H

#include "game.h"

/// @brief Очистка экрана (кроссплатформенная)
void clearScreen(void);

/// @brief Отрисовка игрового поля, платформ, мяча и счёта
/// @param game указатель на объект игры
void renderGame(const Game *game);

#endif // RENDER_H
