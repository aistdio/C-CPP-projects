MAIN_DIR = main/
MAIN_NAME = s21_tetris
EXECUTABLE_DIR = executable/
OUTPUT_NAME = $(MAIN_NAME).exe

DVI_DIR = docs/

export BUILD_DIR = build/
TEST_DIR = tests/
BACKEND_DIR = brick_game/tetris/
FRONTEND_DIR = gui/cli/
export COMMON_DIR = common/
PROJECT_DIRS := $(BACKEND_DIR) $(FRONTEND_DIR) $(COMMON_DIR)

SRC := $(shell find $(PROJECT_DIRS) -type f -name '*.c')
SRC_TEST := $(shell find $(TEST_DIR) -type f -name '*.c')
SRC_TO_TEST := $(shell find $(BACKEND_DIR) $(COMMON_DIR) -type f -name '*.c')
HEADERS := $(addprefix -I, $(shell find $(PROJECT_DIRS) -type f -name '*.h' -exec dirname {} \; | sort -u))

OBJ := $(addprefix $(BUILD_DIR), $(SRC:.c=.o))
TEST_OBJ := $(addprefix $(BUILD_DIR)$(TEST_DIR), $(SRC_TEST:$(TEST_DIR)%.c=%.o))

export CC = gcc
CF = clang-format -i
CFDIR = ./../materials/linters/
STD = c11
CFLAGS = -Wall -Wextra -Werror -std=$(STD) -g $(HEADERS)
export SUBCFLAGS = -Wall -Wextra -Werror -std=$(STD) -g
CFLAGSNOERROR = -Wall -Wextra -std=$(STD) $(HEADERS)
CPPCHECKFLAGS = --enable=all --inconclusive --library=posix --std=$(STD)
FLAG_COV = --coverage
FSANITIZE = -fsanitize=address -fsanitize=leak -fsanitize=undefined -fsanitize=unreachable

DISTRO = $(shell uname -s)
LCOV = $(BUILD_DIR)$(TEST_DIR)coverage_report/index.html

ifeq (${DISTRO}, Darwin)
	LIBS:=-lcheck -lm -lncurses
else
	LIBS:=-lcheck -lsubunit -lm -lncurses
endif
export LIBS