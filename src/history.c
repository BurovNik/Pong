#include "history.h"

#include <assert.h>
#include <stdio.h>

#include <stdlib.h>

// TODO может вынести в utility какой-нибудь ? 
#include <sys/stat.h>
#include <string.h>

#ifdef _WIN32
    #include <direct.h>   // _mkdir
    #define MKDIR(path) _mkdir(path)
#else
    #include <sys/stat.h> // mkdir
    #define MKDIR(path) mkdir(path, 0755)
#endif


static const char *historyFilePath = HISTORY_FILE;

void historySetFile(const char *newPath)
{
    historyFilePath = newPath;
}

void ensureDirectory(const char *filepath) 
{
    // Копируем путь в буфер, чтобы не испортить оригинал
    char path[256];
    strncpy(path, filepath, sizeof(path) - 1);
    path[sizeof(path) - 1] = '\0';

    // Ищем последний слеш
    char *last_slash = strrchr(path, '/');
    #ifdef _WIN32
        // На Windows также проверяем обратный слеш
        char *last_backslash = strrchr(path, '\\');
        if (last_backslash > last_slash) last_slash = last_backslash;
    #endif

    if (last_slash != NULL) {
        *last_slash = '\0';  // обрезаем до имени папки
        MKDIR(path);         // создаём (если уже есть — проигнорирует ошибку)
    }
}
// вот до сюда 

int historyLoad(GameRecord *records, int maxEntries)
{
    ensureDirectory(historyFilePath);
    assert(records != NULL);
    // Открываем файл
    FILE *file = fopen(historyFilePath, "r");
    if (!file) 
        return 0;

    // считываем данные пока есть куда и не конец файла
    int count = 0;
    while (count < maxEntries && !feof(file))
    {
        GameRecord tmpRecord;
        struct tm tm = {0};
        char winner[10];
        int fields = fscanf(file, "%d-%d-%d %d:%d,%d,%d,%s\n",
                            &tm.tm_year, &tm.tm_mon, &tm.tm_mday,
                            &tm.tm_hour, &tm.tm_min,
                            &tmpRecord.leftScore, &tmpRecord.rightScore, winner);
        if (fields != 8) break;  // неверный формат строки

        tm.tm_year -= 1900;
        tm.tm_mon -= 1;
        tmpRecord.gameDateTime = mktime(&tm);
        strncpy(tmpRecord.winner, winner, sizeof(tmpRecord.winner) - 1);
        records[count] = tmpRecord;
        count++;
    }
    fclose(file);
    return count;
       
}


void historyAddRecordAndSave(const GameRecord *newRecord)
{
    assert(newRecord != NULL);
    // Читаем существующие записи
    GameRecord existing[HISTORY_MAX_ENTRIES];
    int count = historyLoad(existing, HISTORY_MAX_ENTRIES);

    // Добавляем новую (если есть место — в конец, иначе сдвигаем)
    if (count < HISTORY_MAX_ENTRIES) {
        existing[count] = *newRecord;
        count++;
    } else {
        // сдвигаем все на одну позицию влево (удаляем самую старую)
        for (int i = 1; i < HISTORY_MAX_ENTRIES; i++)
            existing[i - 1] = existing[i];
        existing[HISTORY_MAX_ENTRIES - 1] = *newRecord;
    }

    // Перезаписываем файл
    ensureDirectory(historyFilePath); // на всякий случай, но по идее в load уже должны были проверить
    FILE *file = fopen(historyFilePath, "w");
    if (!file) 
        return;

    for (int i = 0; i < count; i++) {
        struct tm *tm = localtime(&existing[i].gameDateTime);
        fprintf(file, "%04d-%02d-%02d %02d:%02d,%d,%d,%s\n",
                tm->tm_year + 1900, tm->tm_mon + 1, tm->tm_mday,
                tm->tm_hour, tm->tm_min,
                existing[i].leftScore, existing[i].rightScore,
                existing[i].winner);
    }
    fclose(file);
}


void historyDisplay()
{
    // Читаем существующие записи
    GameRecord records[HISTORY_MAX_ENTRIES];
    int count = historyLoad(records, HISTORY_MAX_ENTRIES);

    printf("\033[2J\033[H");  // очистка экрана
    printf("===== История последних игр =====\n\n");

        if (count == 0) {
        printf("История пуста.\n");
    } else {
        printf("| #  | Дата и время        | Счёт  | Победитель |\n");
        printf("|----|---------------------|-------|------------|\n");
        for (int i = 0; i < count; i++) {
            char time_buf[20];
            struct tm *tm = localtime(&records[i].gameDateTime);
            strftime(time_buf, sizeof(time_buf), "%Y-%m-%d %H:%M", tm);

            printf("| %2d | %19s | %2d:%-2d | %-10s |\n",
                   i + 1, time_buf,
                   records[i].leftScore, records[i].rightScore,
                   records[i].winner);
        }
    }
}


void formGameRecord(GameRecord *record, const Score *score)
{
    assert(record != NULL);
    assert(score != NULL);

    record->gameDateTime = time(NULL);
    record->leftScore = score->leftScore;
    record->rightScore = score->rightScore;
    strcpy(record->winner, (score->leftScore > score->rightScore) ? "Left" : "Right");
}

void clearHistory()
{
    ensureDirectory(historyFilePath);

    FILE *file = fopen(historyFilePath, "w");
    if(!file)
        return;
    
    fclose(file);
}