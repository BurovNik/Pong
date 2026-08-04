#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>   // usleep (Linux); на Windows заменить на Sleep из windows.h
#include "input.h"
#include "menu.h"
#include "history.h"
#include "aiplayer.h"

// временно 
#include "ball.h"
#include "score.h"

void clear_screen() {
    #ifdef _WIN32
        system("cls");
    #else
        printf("\033[2J\033[H");
    #endif
}
#define FIELD_WIDTH  80
#define FIELD_HEIGHT 24
#define MAX_SCORE    10

// Заглушка для отрисовки игрового поля (без ракеток)
void render_game(const Ball *ball, const Score *score) {
    clear_screen();
    // Верхняя граница
    for (int x = 0; x < FIELD_WIDTH; x++) putchar('-');
    putchar('\n');
    // Игровое поле
    for (int y = 0; y < FIELD_HEIGHT; y++) {
        for (int x = 0; x < FIELD_WIDTH; x++) {
            if (x == 0 || x == FIELD_WIDTH-1) putchar('|');
            else if (x == (int)ball->xCor && y == (int)ball->yCor) putchar('O');
            else putchar(' ');
        }
        putchar('\n');
    }
    // Нижняя граница
    for (int x = 0; x < FIELD_WIDTH; x++) putchar('-');
    printf("\nScore: Left %d - %d Right\n", score->leftScore, score->rightScore);
}


int main()
{
    printf("main is start");
    srand((unsigned int)time(NULL));

    inputInit();

    Ball ball;
    ballInit(&ball, FIELD_WIDTH, FIELD_HEIGHT, 10);

    Score score;
    scoreInit(&score);

    Menu mainMenu;
    menuInit(&mainMenu, "=========PONG=========");
    menuAddItem(&mainMenu, "1. Начать игру", MENU_ACTION_START);
    menuAddItem(&mainMenu, "2. История игр", MENU_ACTION_SHOW_HISTORY);
    menuAddItem(&mainMenu, "3. Выбор Сложности ИИ",MENU_ACTION_CHOOSE_AI_DIFFICULTY);
    menuAddItem(&mainMenu, "0. Выход из игры", MENU_ACTION_EXIT);

    // Построение меню сложности
    Menu diffMenu;
    menuInit(&diffMenu, "=========Выберите сложность ИИ=========");

    int levelCount = aiGetLevelCount();
    for (int i = 0; i < levelCount; i++) 
    {
        menuAddItem(&diffMenu, aiGetLevelName(i), MENU_ACTION_NONE);
    }
    menuAddItem(&diffMenu, "Назад", MENU_ACTION_NONE); 
    AIPlayerLevel aiLevel = E_MEDIUM;

    int isRunning = 1;
    int state = 0; // заглушка, 0 - меню, 1 - заглушка игры, 2 заглушка истории, 3 - Заглушка выброа сложности ИИ
    while (isRunning)
    {
        if(state == 0) 
        {
            menuDraw(&mainMenu);
            MenuAction action = menuHandleInput(&mainMenu);
            switch (action) {
                case MENU_ACTION_START:
                    clear_screen();
                    render_game(&ball, &score);
                    printf("Игра началась бы здесь...\nНажмите любую клавишу для возврата в меню.\n");
                    state = 1;
                    break;
                case MENU_ACTION_SHOW_HISTORY:
                    historyDisplay();
                    printf("Нажмите любую клавишу для возврата в меню.\n");
                    state = 2; // показ истории
                    break;
                case MENU_ACTION_CHOOSE_AI_DIFFICULTY:
                    state = 3; // выбор сложности ИИ
                    break; 
                case MENU_ACTION_EXIT:
                    isRunning = 0;
                    break;
                default:
                    break;
            }
        } // Меню
        else if (state == 3)
        {
            menuDraw(&diffMenu);
            int key = inputReadKey();
            if (key == KEY_UP)
            {
                if (diffMenu.selectedIndex > 0) 
                    diffMenu.selectedIndex--;
            } 
            else if (key == KEY_DOWN) 
            {
                if (diffMenu.selectedIndex < diffMenu.itemCount - 1) 
                diffMenu.selectedIndex++;
            } 
            else if (key == KEY_ENTER)
            {
                int selected = menuGetSelectedIndex(&diffMenu);
                if (selected >= 0 && selected < levelCount) 
                {
                    // Выбран конкретный уровень
                    aiLevel = aiGetLevelByIndex(selected);
                    state = 1; // игра против ИИ
                    clear_screen();
                    // … здесь позже запустится реальный игровой цикл с aiLevel
                    printf("Игра против ИИ (%s)\n", aiGetLevelName(selected));
                    printf("Нажмите любую клавишу для возврата...\n");
                } 
                else if (selected == levelCount) 
                {
                    // "Назад"
                    state = 0; // вернуться в главное меню
                }
            }
        }// выбор сложности ИИ
        else 
        {
            if (inputKeyPressed()) 
            {
                inputReadKey(); // съедаем символ
                state = 0;       // возвращаемся в меню
                clear_screen();  // очистим перед следующей отрисовкой меню
            }
            #ifdef _WIN32
                sleep(10);
            #else
                usleep(10000);
            #endif

        } // игра или история
        // Небольшая пауза, чтобы не загружать процессор в цикле меню
        #ifdef _WIN32
            sleep(30);
        #else
            usleep(30000);
        #endif
    }
    
    
    clear_screen();
    printf("Выход...\n");
    inputRestore();
    return 0;
}