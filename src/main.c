#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#ifdef _WIN32
    #include <windows.h>
#else
    #include <unistd.h>
#endif

#include "input.h"
#include "menu.h"
#include "history.h"
#include "aiplayer.h"
#include "game.h"
#include "render.h"

#define FRAME_DELAY_US 30000 // ~30 кадров в секунду
#define FIXED_DT        0.05f

static void sleepFrame(void)
{
    #ifdef _WIN32
        Sleep(FRAME_DELAY_US / 1000);
    #else
        usleep(FRAME_DELAY_US);
    #endif
}

static void waitForKey(void)
{
    while (!inputKeyPressed())
        sleepFrame();
    inputReadKey(); // съедаем символ
}

static void runGame(Game *game, AIPlayerLevel aiLevel)
{
    gameStart(game, aiLevel);

    while (game->state != STATE_MENU)
    {
        clearScreen();
        int key = inputReadKey();
        gameHandleInput(game, key);
        gameUpdate(game, FIXED_DT);
        renderGame(game);
        sleepFrame();
    }
}

static void runDifficultyMenu(Menu *diffMenu, int levelCount, AIPlayerLevel *aiLevel, Game *game)
{
    diffMenu->selectedIndex = 0;
    while (1)
    {
        clearScreen();
        menuDraw(diffMenu);
        int key = inputReadKey();

        if (key == KEY_UP)
        {
            if (diffMenu->selectedIndex > 0)
                diffMenu->selectedIndex--;
        }
        else if (key == KEY_DOWN)
        {
            if (diffMenu->selectedIndex < diffMenu->itemCount - 1)
                diffMenu->selectedIndex++;
        }
        else if (key == KEY_ENTER)
        {
            int selected = menuGetSelectedIndex(diffMenu);
            if (selected >= 0 && selected < levelCount)
            {
                *aiLevel = aiGetLevelByIndex(selected);
                runGame(game, *aiLevel);
                return;
            }
            else if (selected == levelCount)
            {
                return; // "Назад"
            }
        }
        sleepFrame();
    }
}

int main()
{
    srand((unsigned int)time(NULL));
    inputInit();

    Game game;
    gameInit(&game);

    Menu mainMenu;
    menuInit(&mainMenu, "=========PONG=========");
    menuAddItem(&mainMenu, "1. Начать игру", MENU_ACTION_START);
    menuAddItem(&mainMenu, "2. История игр", MENU_ACTION_SHOW_HISTORY);
    menuAddItem(&mainMenu, "3. Выбор Сложности ИИ", MENU_ACTION_CHOOSE_AI_DIFFICULTY);
    menuAddItem(&mainMenu, "0. Выход из игры", MENU_ACTION_EXIT);

    Menu diffMenu;
    menuInit(&diffMenu, "=========Выберите сложность ИИ=========");
    int levelCount = aiGetLevelCount();
    for (int i = 0; i < levelCount; i++)
        menuAddItem(&diffMenu, aiGetLevelName(i), MENU_ACTION_NONE);
    menuAddItem(&diffMenu, "Назад", MENU_ACTION_NONE);

    AIPlayerLevel aiLevel = E_MEDIUM;

    int isRunning = 1;
    while (isRunning)
    {
        clearScreen();
        menuDraw(&mainMenu);
        MenuAction action = menuHandleInput(&mainMenu);

        switch (action)
        {
        case MENU_ACTION_START:
            runGame(&game, aiLevel);
            break;

        case MENU_ACTION_SHOW_HISTORY:
            clearScreen();
            historyDisplay();
            waitForKey();
            break;

        case MENU_ACTION_CHOOSE_AI_DIFFICULTY:
            runDifficultyMenu(&diffMenu, levelCount, &aiLevel, &game);
            break;

        case MENU_ACTION_EXIT:
            isRunning = 0;
            break;

        default:
            break;
        }

        sleepFrame();
    }

    clearScreen();
    printf("Выход...\n");
    inputRestore();
    return 0;
}
