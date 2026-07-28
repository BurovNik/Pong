#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>   // usleep (Linux); на Windows заменить на Sleep из windows.h
#include "input.h"
#include "menu.h"

void clear_screen() {
    #ifdef _WIN32
        system("cls");
    #else
        printf("\033[2J\033[H");
    #endif
}


int main()
{
    printf("main is start");

    inputInit();

    Menu mainMenu;
    menuInit(&mainMenu, "=========PONG=========");
    menuAddItem(&mainMenu, "1. Начать игру", MENU_ACTION_START);
    menuAddItem(&mainMenu, "0. Выход из игры", MENU_ACTION_EXIT);

    int isRunning = 1;
    while (isRunning)
    {
        MenuAction action = menuHandleInput(&mainMenu);
        switch (action) {
            case MENU_ACTION_START:
                clear_screen();
                printf("Игра началась бы здесь...\nНажмите любую клавишу для возврата в меню.\n");
                // Ждём нажатия
                while (!inputKeyPressed()) {
                    #ifdef _WIN32
                        sleep(10);
                    #else
                        usleep(10000);
                    #endif
                }
                inputReadKey(); // съесть символ, чтобы не попал в меню
                break;
            case MENU_ACTION_EXIT:
                isRunning = 0;
                break;
            default:
                break;
        }
        if (isRunning) {
            menuDraw(&mainMenu);
            // Небольшая пауза, чтобы не загружать процессор в цикле меню
            #ifdef _WIN32
                sleep(30);
            #else
                usleep(30000);
            #endif
        }
    }
    
    
    clear_screen();
    printf("Выход...\n");
    inputRestore();
    return 0;
}