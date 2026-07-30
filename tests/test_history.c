#include "test_history.h"
#include "history.h"
#include "score.h"
#include "unity.h"

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
    formGameRecord(&record, &score);
    historyAddRecordAndSave(&record);

    GameRecord loaded[10];
    int count = historyLoad(loaded, 10);
    TEST_ASSERT_EQUAL_INT(1, count);
    TEST_ASSERT_EQUAL_INT(10, loaded[0].leftScore);
    TEST_ASSERT_EQUAL_INT(5, loaded[0].rightScore);
    TEST_ASSERT_EQUAL_STRING("Left", loaded[0].winner);
}

void testHistoryMaxEntries(void) 
{
    GameRecord records[10];
    // Сохраняем 12 записей (при максимуме 10)
    for (int i = 0; i < 12; i++) 
    {
        GameRecord r;
        r.gameDateTime = time(NULL) + i; // чтобы отличались
        r.leftScore = i;
        r.rightScore = 0;
        strcpy(r.winner, (i % 2 == 0) ? "Left" : "Right");
        historyAddRecordAndSave(&r);
    }
    int count = historyLoad(records, 10);
    TEST_ASSERT_EQUAL_INT(10, count);
    // Первая запись должна быть i=2 (т.к. 0 и 1 вытолкнуты)
    TEST_ASSERT_EQUAL_INT(2, records[0].leftScore);
    // Последняя i=11
    TEST_ASSERT_EQUAL_INT(11, records[9].leftScore);
}

void testHistoryClear(void)
{
    Score score;
    scoreInit(&score);
    score.leftScore = 7;
    score.rightScore = 3;
    GameRecord record;
    formGameRecord(&record, &score);
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
    formGameRecord(&record, &score);
    TEST_ASSERT_EQUAL_INT(8, record.leftScore);
    TEST_ASSERT_EQUAL_INT(10, record.rightScore);
    TEST_ASSERT_EQUAL_STRING("Right", record.winner);
}

void testAllHistory(void)
{
    RUN_TEST(testHistoryLoad);
    RUN_TEST(testHistorySave);
    RUN_TEST(testHistoryMaxEntries);
    RUN_TEST(testHistoryClear);
    RUN_TEST(testFormGameRecord);
}