#ifndef MENU_H
#define MENU_H

#define MAX_MENU_ITEMS 10

typedef enum {
    MENU_ACTION_NONE, ///< пустое действие
    MENU_ACTION_START, ///< старт игры
    MENU_ACTION_SHOW_HISTORY, ///< показать результаты последних игр
    MENU_ACTION_CHOOSE_AI_DIFFICULTY, ///< выбрать сложность ИИ соперника
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

/// @brief Метод для инициализации игры
/// @param menu указатель на структуру меню
/// @param menuTitle Заголовок в меню
void menuInit(Menu *menu, const char* menuTitle);

/// @brief Метод для добавления пукта в меню
/// @param menu указатель на меню
/// @param itemText надпись в этом пункту
/// @param action действие пункта
void menuAddItem(Menu *menu, const char *itemText, MenuAction action);

/// @brief Обработка нажатия внутри меню
/// @param menu указатель на меню
/// @return Действие выбранного пункта меню
MenuAction menuHandleInput(Menu *menu);

/// @brief Отображение в консоли меню
/// @param menu указатель на меню
void menuDraw(const Menu *menu);

/// @brief Поиск индекса выбранного пункта
/// @param menu указатель на меню
/// @return индекс выбранного пункта
int menuGetSelectedIndex(const Menu *menu);





#endif //MENU_H