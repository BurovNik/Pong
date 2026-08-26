#include "test_history.h"
#include "history.h"
#include "score.h"
#include "unity.h"

#include <stdio.h>
#include <string.h>

void setUp(void) {
    // Перед каждым тестом удаляем тестовый файл, чтобы начать с чистого листа
    remove(TEST_HISTORY_FILE);
    historySetFile(TEST_HISTORY_FILE);
}

void tearDown(void) {
    // После каждого теста убираем за собой
    remove(TEST_HISTORY_FILE);
    historySetFile(HISTORY_FILE); // возвращаем стандартный путь
}

void testHistoryLoad(void)
{
    GameRecord records[10];
    int count = historyLoad(records, 10);
    TEST_ASSERT_EQUAL_INT(0, count);
}

void testHistorySave(void)
{
    Score score;
    scoreInit(&score);
    score.leftScore = 10;
    score.rightScore = 5;

    GameRecord record;
    formGameRecord(&record, &score, "Игрок 1", "Средний");
    historyAddRecordAndSave(&record);

    GameRecord loaded[10];
    int count = historyLoad(loaded, 10);
    TEST_ASSERT_EQUAL_INT(1, count);
    TEST_ASSERT_EQUAL_INT(10, loaded[0].leftScore);
    TEST_ASSERT_EQUAL_INT(5, loaded[0].rightScore);
    TEST_ASSERT_EQUAL_STRING("Игрок 1", loaded[0].leftPlayerName);
    TEST_ASSERT_EQUAL_STRING("Средний", loaded[0].rightPlayerName);
}

void testHistoryMaxEntries(void)
{
    GameRecord records[10];
    // Сохраняем 12 записей (при максимуме 10)
    for (int i = 0; i < 12; i++)
    {
        GameRecord r;
        memset(&r, 0, sizeof(r));
        r.gameDateTime = time(NULL) + i; // чтобы отличались
        r.leftScore = i;
        r.rightScore = 0;
        snprintf(r.leftPlayerName, sizeof(r.leftPlayerName), "L%d", i);
        snprintf(r.rightPlayerName, sizeof(r.rightPlayerName), "R%d", i);
        historyAddRecordAndSave(&r);
    }
    int count = historyLoad(records, 10);
    TEST_ASSERT_EQUAL_INT(10, count);
    // Первая запись должна быть i=2 (т.к. 0 и 1 вытолкнуты)
    TEST_ASSERT_EQUAL_INT(2, records[0].leftScore);
    // Последняя i=11
    TEST_ASSERT_EQUAL_INT(11, records[9].leftScore);
    TEST_ASSERT_EQUAL_STRING("L2", records[0].leftPlayerName);
    TEST_ASSERT_EQUAL_STRING("R2", records[0].rightPlayerName);
    TEST_ASSERT_EQUAL_STRING("L11", records[9].leftPlayerName);
}

void testHistoryClear(void)
{
    Score score;
    scoreInit(&score);
    score.leftScore = 7;
    score.rightScore = 3;
    GameRecord record;
    formGameRecord(&record, &score, "Игрок 1", "Сложный");
    historyAddRecordAndSave(&record);

    clearHistory();
    GameRecord loaded[10];
    int count = historyLoad(loaded, 10);
    TEST_ASSERT_EQUAL_INT(0, count);
}

void testFormGameRecord(void)
{
    Score score;
    scoreInit(&score);
    score.leftScore = 8;
    score.rightScore = 10;
    GameRecord record;
    formGameRecord(&record, &score, "Игрок 1", "Невозможный");
    TEST_ASSERT_EQUAL_INT(8, record.leftScore);
    TEST_ASSERT_EQUAL_INT(10, record.rightScore);
    TEST_ASSERT_EQUAL_STRING("Игрок 1", record.leftPlayerName);
    TEST_ASSERT_EQUAL_STRING("Невозможный", record.rightPlayerName);
}

void testNamesWithSpaces(void)
{
    Score score;
    scoreInit(&score);
    score.leftScore = 3;
    score.rightScore = 1;
    GameRecord record;
    formGameRecord(&record, &score, "Петя Иванов", "Легкий");
    historyAddRecordAndSave(&record);

    GameRecord loaded[10];
    int count = historyLoad(loaded, 10);
    TEST_ASSERT_EQUAL_INT(1, count);
    TEST_ASSERT_EQUAL_STRING("Петя Иванов", loaded[0].leftPlayerName);
    TEST_ASSERT_EQUAL_STRING("Легкий", loaded[0].rightPlayerName);
}

void testNameWithCommaSanitized(void)
{
    Score score;
    scoreInit(&score);
    GameRecord record;
    formGameRecord(&record, &score, "Вася,Петя", "ИИ");
    TEST_ASSERT_EQUAL_STRING("Вася Петя", record.leftPlayerName);
}

void testLongNameTruncation(void)
{
    Score score;
    scoreInit(&score);
    GameRecord record;
    formGameRecord(&record, &score, "ОченьОченьОченьДлинноеИмяИгрокаКотороеНеПоместитсяВМассив", "ИИ");
    TEST_ASSERT_EQUAL_INT(PLAYER_NAME_MAX_LEN - 1, strlen(record.leftPlayerName));
}

void testOldFormatRejected(void)
{
    // Старый формат (с колонкой winner вместо имён) должен отбрасываться
    FILE *f = fopen(TEST_HISTORY_FILE, "w");
    TEST_ASSERT_NOT_NULL(f);
    fprintf(f, "2026-08-06 12:00,10,5,Left\n");
    fclose(f);

    GameRecord records[10];
    int count = historyLoad(records, 10);
    TEST_ASSERT_EQUAL_INT(0, count);
}

void testAllHistory(void)
{
    RUN_TEST(testHistoryLoad);
    RUN_TEST(testHistorySave);
    RUN_TEST(testHistoryMaxEntries);
    RUN_TEST(testHistoryClear);
    RUN_TEST(testFormGameRecord);
    RUN_TEST(testNamesWithSpaces);
    RUN_TEST(testNameWithCommaSanitized);
    RUN_TEST(testLongNameTruncation);
    RUN_TEST(testOldFormatRejected);
}
