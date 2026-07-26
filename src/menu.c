#include "menu.h"
#include "input.h"
#include <stdio.h>

void menuInit(Menu *menu, const char* menuTitle)
{
    menu->menuTitle = menuTitle;
    menu->itemCount = 0;
    menu->selectedIndex = 0;
}

void menuAddItem(Menu *menu, const char *itemText, MenuAction action)
{
    if (menu->itemCount == MAX_MENU_ITEMS)
        return;
    menu->items[menu->itemCount].itemText = itemText;
    menu->items[menu->itemCount].itemAction = action;
    menu->itemCount++;

}

MenuAction menuHandleInput(Menu *menu)
{
    if (!input_key_pressed()) return MENU_ACTION_NONE;
    char key = input_read_key();

    switch (key) {
        case 'w': case 'W': // эмулируем шаг вверх
            if (menu->selectedIndex > 0)
                menu->selectedIndex--;
            break;
        case 's': case 'S': // эмулируем шаг вниз
            if (menu->selectedIndex < menu->itemCount - 1)
                menu->selectedIndex++;
            break;
        case '\r': case '\n': // Enter
            return menu->items[menu->selectedIndex].itemAction;
        case 27: // ESC - можно назначить как выход или назад
            // Пока не используем
            break;
    }
    return MENU_ACTION_NONE;
}

void menuDraw(const Menu *menu)
{
        printf("\033[2J\033[H"); // очистка экрана (ANSI)
    printf("%s\n\n", menu->menuTitle);
    for (int i = 0; i < menu->itemCount; i++) {
        if (i == menu->selectedIndex)
            printf(" > %s\n", menu->items[i].itemText);
        else
            printf("   %s\n", menu->items[i].itemText);
    }
    printf("\nИспользуйте W/S и Enter\n");
}