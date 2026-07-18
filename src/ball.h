#ifndef BALL_H
#define BALL_H

/// @brief структура для представления мячв в программе
typedef struct {
    float xCor;         // координата мяча по x
    float yCor;         // координата мяча по y
    float Vx;           // проекция скорости мяча на Ось x
    float Vy;           // проекция скорости мяча на Ось y
    float maxSpeed;     // максимальная скорость мяча
} Ball;

/// @brief Метод для инициализации мяча в начале игры
/// @param ball указатель на объект структуры Ball
/// @param width ширина игрового поля
/// @param height высота игрового поля
/// @param maxSpeed максимальная скорость мяча
void ballInit(Ball *ball, float width, float height, float maxSpeed);

/// @brief Метод перезпуска мяча, мяч помещается в центр поля, ему задается произвольая скорось, не превышающая максимальную скорость 
/// @param ball  указатель на объект структуры Ball
/// @param width ширина игрового поля
/// @param height  высота игрового поля
void ballReset(Ball *ball, float width, float height);

/// @brief Метод для обновления информации о мяче, через промежуток
/// @param ball указатель на объект структуры Ball
/// @param dt прошедший временной промежуток
void ballUpdate(Ball *ball, float dt);

/// @brief Обработка отскока от границ поля и удержание внутри Вызывать после ball_update()
/// @param ball
/// @param fieldWidth
/// @param fieldHeight 
void ballConstrainToField(Ball *ball, float fieldHeight);

/// @brief Метод для обработку удара мяча о верхнюю/нижнюю поверхности
/// @param ball указатель на объект структуры Ball
void ballBounceVertical(Ball *ball);

/// @brief Метод для обработки удара мяча о боковые поверхности
/// @param ball указатель на объект структуры Ball
void ballBounceHorizontal(Ball *ball);

//TODO подумать може надо что-то добавить 

#endif // BALL_H