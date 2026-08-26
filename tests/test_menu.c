#include "../unity/unity.h"
#include "../src/menu.h"

void testMenuInit()
{
    Menu m;
    menuInit(&m, "Test Menu");
    TEST_ASSERT_EQUAL_STRING("Test Menu", m.menuTitle);
    TEST_ASSERT_EQUAL_INT(0, m.itemCount);
    TEST_ASSERT_EQUAL_INT(0, m.selectedIndex);
}

void testMenuAddItem()
{
    Menu m;
    menuInit(&m, "Test");
    menuAddItem(&m, "Start", MENU_ACTION_START);
    TEST_ASSERT_EQUAL_INT(1, m.itemCount);
    TEST_ASSERT_EQUAL_STRING("Start", m.items[0].itemText);
    TEST_ASSERT_EQUAL_INT(MENU_ACTION_START, m.items[0].itemAction);

    menuAddItem(&m, "Exit", MENU_ACTION_EXIT);
    TEST_ASSERT_EQUAL_INT(2, m.itemCount);
    TEST_ASSERT_EQUAL_STRING("Exit", m.items[1].itemText);
    TEST_ASSERT_EQUAL_INT(MENU_ACTION_EXIT, m.items[1].itemAction);
}

void testAllMenu()
{
    RUN_TEST(testMenuInit);
    RUN_TEST(testMenuAddItem);
}