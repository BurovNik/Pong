#include "render.h"
#include "game.h"
#include "aiplayer.h"
#include <assert.h>
#include <stdio.h>
#include <stdlib.h>

void clearScreen(void)
{
    #ifdef _WIN32
        system("cls");
    #else
        printf("\033[2J\033[H");
    #endif
}

void renderGame(const Game *game)
{
    assert(game != NULL);
    clearScreen();

    // Верхняя граница
    for (int x = 0; x < game->borders.width; x++)
        putchar('-');
    putchar('\n');

    // Игровое поле
    for (int y = 0; y < game->borders.height; y++) {
        for (int x = 0; x < game->borders.width; x++) {
            if (x == 0 || x == game->borders.width - 1)
                putchar('|');
            else if (x >= game->leftPlatform.X && x < game->leftPlatform.X + PLATFORM_WIDTH &&
                     y >= game->leftPlatform.Y && y < game->leftPlatform.Y + game->leftPlatform.heightPlatforms)
                putchar('#');
            else if (x >= game->rightPlatform.X && x < game->rightPlatform.X + PLATFORM_WIDTH &&
                     y >= game->rightPlatform.Y && y < game->rightPlatform.Y + game->rightPlatform.heightPlatforms)
                putchar('#');
            else if (x == (int)game->ball.xCor && y == (int)game->ball.yCor)
                putchar('O');
            else
                putchar(' ');
        }
        putchar('\n');
    }

    // Нижняя граница
    for (int x = 0; x < game->borders.width; x++)
        putchar('-');

    const char *leftName = "Игрок";
    const char *rightName = aiGetLevelName(game->aiLevel);
    printf("\n%s %d : %d %s\n", leftName, game->score.leftScore, game->score.rightScore, rightName);

    if (game->state == STATE_PAUSE) {
        printf("\nПАУЗА. ESC - продолжить, Q - выйти в меню\n");
    } else if (game->state == STATE_GAME_OVER) {
        const char *winner = (game->score.leftScore > game->score.rightScore) ? leftName : rightName;
        printf("\nПобедил %s! Нажмите любую клавишу...\n", winner);
    } else {
        printf("\nESC - пауза\n");
    }
}
