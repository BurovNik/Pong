#ifndef MENU_H
#define MENU_H

#define MAX_MENU_ITEMS 10

typedef enum {
    MENU_ACTION_NONE, ///< пустое действие
    MENU_ACTION_START, ///< старт игры
    MENU_ACTION_SHOW_HISTORY, ///< показать результаты последних игр
    /// тут будут другие пункты меню
    MENU_ACTION_EXIT ///< выход
} MenuAction;


typedef struct 
{
    const char *itemText;
    MenuAction itemAction;
} MenuItem;

typedef struct 
{
    const char *menuTitle;
    MenuItem items[MAX_MENU_ITEMS];
    int itemCount;
    int selectedIndex;
} Menu;


void menuInit(Menu *menu, const char* menuTitle);

void menuAddItem(Menu *menu, const char *itemText, MenuAction action);

MenuAction menuHandleInput(Menu *menu);

void menuDraw(const Menu *menu);






#endif //MENU_H