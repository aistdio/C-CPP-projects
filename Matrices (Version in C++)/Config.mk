CC = gcc
CF = clang-format -i
CFDIR = ./../materials/linters/
STD = c++17
COVERAGE = --coverage
CFLAGS = -std=$(STD) -Wall -Wextra -Werror
CFLAGSNOERROR = -std=$(STD) -Wall -Wextra
CPPCHECK = cppheck
CPPCHECKFLAGS = --enable=all --inconclusive --library=posix --std=$(STD) --suppress=missingIncludeSystem
FSANITIZE = -fsanitize=address -fsanitize=leak -fsanitize=undefined -fsanitize=unreachable
VALGRIND = valgrind --tool=memcheck --leak-check=yes --leak-check=full --show-leak-kinds=all
TARGET = s21_matrix_oop

BUILD_DIR = build/
TEST_DIR = tests/

SRC := $(shell find . -name '*.cc' -not -path "./$(TEST_DIR)*")
SRC_TEST := $(shell find $(TEST_DIR) -name '*.cc')
FILES_TO_FORMAT := $(shell find . -name '*.cc' -or -name '*.h')

OBJ := $(addprefix $(BUILD_DIR), $(SRC:.cc=.o))
OBJ_TEST := $(addprefix $(BUILD_DIR)$(TEST_DIR), $(SRC_TEST:$(TEST_DIR)%.cc=%.o))

DISTRO = $(shell uname -s)
LCOV = $(BUILD_DIR)$(TEST_DIR)coverage_report/index.html

LIBS = -lstdc++ -lm
LIBS_TEST = -lgtest -lgtest_main -pthread $(LIBS)