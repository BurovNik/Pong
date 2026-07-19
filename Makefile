# Компилятор и флаги
CC       = gcc
CFLAGS   = -Wall -Wextra -g -I./src -I./unity -I./tests

# Определяем расширение исполняемых файлов
ifeq ($(OS),Windows_NT)
    EXE     = .exe
    RM      = del /Q
    MKDIR   = mkdir
    LDFLAGS =
else
    EXE     =
    RM      = rm -f
    MKDIR   = mkdir -p
    LDFLAGS = -lm
endif

# Папки
SRC_DIR  = src
TEST_DIR = tests
UNITY_DIR = unity
BUILD_DIR = build

# Исходники игры (все .c, кроме main.c)
GAME_SRC = $(filter-out $(SRC_DIR)/main.c, $(wildcard $(SRC_DIR)/*.c))
GAME_OBJ = $(GAME_SRC:$(SRC_DIR)/%.c=$(BUILD_DIR)/%.o)

# Главный файл игры
MAIN_SRC = $(SRC_DIR)/main.c
MAIN_OBJ = $(BUILD_DIR)/main.o

# Все тестовые исходники (раннер + все модули тестов)
TEST_SRC = $(wildcard $(TEST_DIR)/*.c)
TEST_OBJ = $(TEST_SRC:$(TEST_DIR)/%.c=$(BUILD_DIR)/%.o)

UNITY_SRC = $(UNITY_DIR)/unity.c
UNITY_OBJ = $(BUILD_DIR)/unity.o

# Итоговые исполняемые файлы (с расширением, если нужно)
GAME_TARGET = pong$(EXE)
TEST_TARGET = run_tests$(EXE)

.PHONY: all game test clean

all: game

game: $(GAME_TARGET)

$(GAME_TARGET): $(MAIN_OBJ) $(GAME_OBJ)
	$(CC) $(CFLAGS) -o $@ $^ $(LDFLAGS)

test: $(TEST_TARGET)
	./$(TEST_TARGET)

$(TEST_TARGET): $(TEST_OBJ) $(GAME_OBJ) $(UNITY_OBJ)
	$(CC) $(CFLAGS) -o $@ $^ $(LDFLAGS)

# Компиляция .c -> .o
$(BUILD_DIR)/%.o: $(SRC_DIR)/%.c | $(BUILD_DIR)
	$(CC) $(CFLAGS) -c $< -o $@

$(BUILD_DIR)/%.o: $(TEST_DIR)/%.c | $(BUILD_DIR)
	$(CC) $(CFLAGS) -c $< -o $@

$(BUILD_DIR)/%.o: $(UNITY_DIR)/%.c | $(BUILD_DIR)
	$(CC) $(CFLAGS) -c $< -o $@

# Создание папки build
$(BUILD_DIR):
	$(MKDIR) $(BUILD_DIR)

# Очистка
clean:
	$(RM) $(GAME_TARGET) $(TEST_TARGET)
	$(RM) $(BUILD_DIR)/*.o