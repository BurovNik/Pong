# Компилятор и флаги
CC       = gcc
CFLAGS   = -Wall -Wextra -g -I./src -I./unity -I./tests
LDFLAGS  =

# Папки
SRC_DIR  = src
TEST_DIR = tests
UNITY_DIR = unity
BUILD_DIR = build

# Исходники игры (все .c файлы в src, кроме main.c — он отдельно)
GAME_SRC = $(filter-out $(SRC_DIR)/main.c, $(wildcard $(SRC_DIR)/*.c))
GAME_OBJ = $(GAME_SRC:$(SRC_DIR)/%.c=$(BUILD_DIR)/%.o)

# Главный файл игры
MAIN_SRC = $(SRC_DIR)/main.c
MAIN_OBJ = $(BUILD_DIR)/main.o

# Исходники тестов (все .c в tests) + нужные модули из src
TEST_SRC = $(wildcard $(TEST_DIR)/*.c)
TEST_MODULES = $(GAME_SRC)               # все модули игры, кроме main
UNITY_SRC = $(UNITY_DIR)/unity.c

TEST_OBJ = $(TEST_SRC:$(TEST_DIR)/%.c=$(BUILD_DIR)/%.o)
MODULE_OBJ_TEST = $(GAME_OBJ)            # объектные файлы модулей игры (те же)
UNITY_OBJ = $(BUILD_DIR)/unity.o

# Итоговые исполняемые файлы
GAME_TARGET = pong
TEST_TARGET = run_tests

# Цели
.PHONY: all game test clean

all: game

# Сборка игры
game: $(GAME_TARGET)

$(GAME_TARGET): $(MAIN_OBJ) $(GAME_OBJ)
	$(CC) $(CFLAGS) -o $@ $^ $(LDFLAGS)

# Сборка тестов
test: $(TEST_TARGET)
	./$(TEST_TARGET)

$(TEST_TARGET): $(TEST_OBJ) $(MODULE_OBJ_TEST) $(UNITY_OBJ)
	$(CC) $(CFLAGS) -o $@ $^ $(LDFLAGS)

# Правила компиляции .c -> .o
$(BUILD_DIR)/%.o: $(SRC_DIR)/%.c | $(BUILD_DIR)
	$(CC) $(CFLAGS) -c $< -o $@

$(BUILD_DIR)/%.o: $(TEST_DIR)/%.c | $(BUILD_DIR)
	$(CC) $(CFLAGS) -c $< -o $@

$(BUILD_DIR)/%.o: $(UNITY_DIR)/%.c | $(BUILD_DIR)
	$(CC) $(CFLAGS) -c $< -o $@

# Создание папки build, если её нет
$(BUILD_DIR):
	mkdir -p $(BUILD_DIR)

# Очистка
clean:
	rm -rf $(BUILD_DIR) $(GAME_TARGET) $(TEST_TARGET)

# Удобное сокращение
rebuild: clean all