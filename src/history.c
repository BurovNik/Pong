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

// Единый источник правды о формате строки в файле истории:
// "YYYY-MM-DD HH:MM,leftScore,rightScore,leftName,rightName"
static int historyParseLine(char *line, GameRecord *out)
{
    struct tm tm = {0};
    int fields = sscanf(line, "%d-%d-%d %d:%d,%d,%d,%31[^,],%31[^,\n]",
                        &tm.tm_year, &tm.tm_mon, &tm.tm_mday,
                        &tm.tm_hour, &tm.tm_min,
                        &out->leftScore, &out->rightScore,
                        out->leftPlayerName, out->rightPlayerName);
    if (fields != 9)
        return 0; // неверный формат строки

    tm.tm_year -= 1900;
    tm.tm_mon -= 1;
    out->gameDateTime = mktime(&tm);
    return 1;
}

static void historyFormatLine(const GameRecord *rec, char *buf, size_t bufSize)
{
    struct tm *tm = localtime(&rec->gameDateTime);
    snprintf(buf, bufSize, "%04d-%02d-%02d %02d:%02d,%d,%d,%s,%s\n",
             tm->tm_year + 1900, tm->tm_mon + 1, tm->tm_mday,
             tm->tm_hour, tm->tm_min,
             rec->leftScore, rec->rightScore,
             rec->leftPlayerName, rec->rightPlayerName);
}

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
    char line[256];
    while (count < maxEntries && fgets(line, sizeof(line), file))
    {
        GameRecord tmpRecord = {0};
        if (historyParseLine(line, &tmpRecord))
        {
            records[count] = tmpRecord;
            count++;
        }
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
        char line[256];
        historyFormatLine(&existing[i], line, sizeof(line));
        fputs(line, file);
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
        printf("| #  | Дата и время        | Счёт  | Левый игрок   | Правый игрок  | Победитель   |\n");
        printf("|----|---------------------|-------|---------------|---------------|--------------|\n");
        for (int i = 0; i < count; i++) {
            char time_buf[20];
            struct tm *tm = localtime(&records[i].gameDateTime);
            strftime(time_buf, sizeof(time_buf), "%Y-%m-%d %H:%M", tm);

            const char *winner = (records[i].leftScore > records[i].rightScore)
                                 ? records[i].leftPlayerName
                                 : records[i].rightPlayerName;

            printf("| %2d | %19s | %2d:%-2d | %-13s | %-13s | %-12s |\n",
                   i + 1, time_buf,
                   records[i].leftScore, records[i].rightScore,
                   records[i].leftPlayerName, records[i].rightPlayerName,
                   winner);
        }
    }
}


// Копирует имя в буфер, заменяя запятые (разделитель CSV) на пробел
static void copySanitizedName(char *dst, size_t dstSize, const char *src)
{
    if (dstSize == 0)
        return;
    size_t i = 0;
    for (; i < dstSize - 1 && src[i] != '\0'; i++)
        dst[i] = (src[i] == ',') ? ' ' : src[i];
    dst[i] = '\0';
}

void formGameRecord(GameRecord *record, const Score *score,
                    const char *leftName, const char *rightName)
{
    assert(record != NULL);
    assert(score != NULL);
    assert(leftName != NULL);
    assert(rightName != NULL);

    record->gameDateTime = time(NULL);
    record->leftScore = score->leftScore;
    record->rightScore = score->rightScore;
    copySanitizedName(record->leftPlayerName, sizeof(record->leftPlayerName), leftName);
    copySanitizedName(record->rightPlayerName, sizeof(record->rightPlayerName), rightName);
}

void clearHistory()
{
    ensureDirectory(historyFilePath);

    FILE *file = fopen(historyFilePath, "w");
    if(!file)
        return;
    
    fclose(file);
}