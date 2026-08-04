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
    int key = inputReadKey();
    if (key == -1)
        return MENU_ACTION_NONE;

    switch (key)
    {
    case KEY_UP:
    case 'w': case 'W':
        if (menu->selectedIndex > 0)
            menu->selectedIndex--;
        break;
    case KEY_DOWN:
    case 's': case 'S':
        if(menu->selectedIndex < menu->itemCount)
            menu->selectedIndex++;
        break;
    case KEY_ENTER:
        return menu->items[menu->selectedIndex].itemAction;
    case KEY_ESC:
        // TODO обработка ESC
        break;
    
    default:
        printf("Неверная клавиша");
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
    printf("\nИспользуйте W/S или стрелки вверх/вниз для другой раскладки и Enter\n");
}

int menuGetSelectedIndex(const Menu *menu) 
{
    return menu->selectedIndex;
}