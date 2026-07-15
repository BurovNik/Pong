#ifndef SCORE_H
#define SCORE_H

/// @brief Структура для хранения информации о счете
typedef struct {
    int leftScore;  ///< счет левого игрока
    int rightScore; ///< счет правого игрока
    int maxScore;   ///< максимальный счет в партии
} Score; 

/// @brief Метод инициализации счета значениями по умолчанию
/// @param score указатель на структуру счета
void scoreInit(Score *score);

/// @brief Метод для проверки достижения максимального счета и окончания игры
/// @param score указатель на структуру счета
/// @return 1 игра закончена, 0 - игра продолжается
int isGameOver(const Score *score);

/// @brief Метод для увеличения счета "левого игрока"
/// @param score указатель на структуру счета
void increaseLeftScore(Score* score);
/// @brief Метод для увеличения счета "правого" игрока
/// @param score указатель на структуру счета
void increaseRightScore(Score *score);

/// @brief метод для сброса счета (при перезапуске игры)
/// @param score указатель на структуру счета
void resetScore(Score *score);

/// @brief метод для установки пользовательского максимального счета
/// @param score указатель на структуру счета
/// @param newMaxScore пользовательский максимальный счет (для установки должен быть больше 0)
void setMaxScore(Score *score, int newMaxScore);

#endif //SCORE_H