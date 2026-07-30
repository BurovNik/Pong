#ifndef HISTORY_H
#define HISTORY_H
#include "time.h"
#include "score.h"
#include <string.h>

#define HISTORY_MAX_ENTRIES 10 ///< максимальное количество записей
#define HISTORY_FILE "res/history.csv" ///< название файла с записями

typedef struct {
    time_t gameDateTime;
    int leftScore;
    int rightScore;
    char winner[10];
} GameRecord;

/// @brief Метод для проверки сущесвтует ли директория с результатми и создает ее в случае необходимости
/// @param filepath путь до директории
void ensureDirectory(const char *filepath);


/// @brief Метод для загрузки записей с результатами из файла с историей
/// @param records СПИСОК записей
/// @param maxEntries максимальный размер списка
/// @return количество считанных записей
int historyLoad(GameRecord *records, int maxEntries);

/// @brief Метод для добавления записи в файл с историей
/// @param newRecord указатель на новую запись
void historyAddRecordAndSave(const GameRecord *newRecord);

/// @brief Метод для отображения записей из файла с историей
void historyDisplay();

/// @brief Метод для формирования записи на основе счета 
/// @param record Указатель на запись, которую передаем
/// @param score Указатель на счет
void formGameRecord(GameRecord *record, const Score *score);

/// @brief Метод для очистки файла с историей
void clearHistory();

/// @brief Установить свой путь к файлу истории (для тестов)
void historySetFile(const char *newPath);

#endif