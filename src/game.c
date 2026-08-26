#include "game.h"
#include "input.h"
#include <assert.h>
#include <stddef.h>
#include <string.h>

void gameInit(Game *game)
{
    assert(game != NULL);
    memset(game, 0, sizeof(*game));
    game->state = STATE_MENU;
    game->aiLevel = E_MEDIUM;
}

static void resetPlatforms(Game *game)
{
    assert(game != NULL);

    game->leftPlatform.heightPlatforms = PLATFORM_HEIGHT;
    game->leftPlatform.X = game->borders.width / 10;
    game->leftPlatform.Y = game->borders.height / 2 - game->leftPlatform.heightPlatforms / 2;

    game->rightPlatform.heightPlatforms = PLATFORM_HEIGHT;
    game->rightPlatform.X = game->borders.width - game->borders.width / 10 - PLATFORM_WIDTH;
    game->rightPlatform.Y = game->borders.height / 2 - game->rightPlatform.heightPlatforms / 2;
}

void gameStart(Game *game, AIPlayerLevel aiLevel)
{
    assert(game != NULL);

    game->borders.width = FIELD_WIDTH;
    game->borders.height = FIELD_HEIGHT;

    game->aiLevel = aiLevel;

    scoreInit(&game->score);
    setMaxScore(&game->score, MAX_SCORE);

    ballInit(&game->ball, FIELD_WIDTH, FIELD_HEIGHT, 10);

    resetPlatforms(game);

    game->state = STATE_PLAYING;
}

void gameHandleInput(Game *game, int key)
{
    assert(game != NULL);
    if (key == -1)
        return;

    switch (game->state)
    {
    case STATE_PLAYING:
        if (key == KEY_UP || key == 'w' || key == 'W')
            MovePlatform(&game->leftPlatform, &game->borders, 0);
        else if (key == KEY_DOWN || key == 's' || key == 'S')
            MovePlatform(&game->leftPlatform, &game->borders, 1);
        else if (key == KEY_ESC)
            game->state = STATE_PAUSE;
        break;

    case STATE_PAUSE:
        if (key == KEY_ESC)
            game->state = STATE_PLAYING;
        else if (key == 'q' || key == 'Q')
            game->state = STATE_MENU;
        break;

    case STATE_GAME_OVER:
        // любая клавиша возвращает в меню
        game->state = STATE_MENU;
        break;

    case STATE_MENU:
    default:
        break;
    }
}

void gameUpdate(Game *game, float dt)
{
    assert(game != NULL);

    if (game->state != STATE_PLAYING)
        return;

    ballUpdate(&game->ball, dt);
    ballConstrainToField(&game->ball, game->borders.height);

    aiMovePlatform(&game->rightPlatform, &game->ball, &game->borders, game->aiLevel);
}
