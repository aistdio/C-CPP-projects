CC = gcc
CF = clang-format -i
CFDIR = ./../materials/linters/
STD = c11
CFLAGS = -Wall -Wextra -Werror -std=$(STD)
CFLAGSNOERROR = -Wall -Wextra -std=$(STD)
CPPCHECK = cppcheck
CPPCHECKFLAGS = --enable=all --inconclusive --library=posix --std=$(STD) --suppress=missingIncludeSystem
FLAG_COV = --coverage
FSANITIZE=-fsanitize=address -fsanitize=leak -fsanitize=undefined -fsanitize=unreachable
TARGET=s21_matrix

BUILD_DIR=build/
TEST_DIR=tests/

SRC:=$(wildcard *.c)
SRC_TEST:=$(shell find $(TEST_DIR) -name '*.c')
FILES_TO_FORMAT:=$(shell find . -name '*.c' -or -name '*.h')

OBJ:=$(addprefix $(BUILD_DIR), $(SRC:.c=.o))
TEST_OBJ:=$(addprefix $(BUILD_DIR)$(TEST_DIR), $(SRC_TEST:$(TEST_DIR)%.c=%.o))

DISTRO=$(shell uname -s)
LCOV=$(BUILD_DIR)$(TEST_DIR)coverage_report/index.html

ifeq (${DISTRO}, Darwin)
	LIBS=-lcheck -lm
else
	LIBS=-lcheck -lm -lsubunit
endif

ifeq ("$(USER)", "aistdio")
	CPPCHECK = snap run cppcheck
	CPPCHECKFLAGS = --enable=all --inconclusive --library=posix --std=$(STD) --suppress=checkersReport
endif

all: $(TARGET).a

$(TARGET).a: $(OBJ)
	ar rc $(TARGET).a $(OBJ)
	ranlib $(TARGET).a

$(BUILD_DIR)%.o: %.c create_dir
	$(CC) $(CFLAGS) -c $< -o $@

test: clean $(TEST_OBJ)
	@$(CC) $(FLAG_COV) -o $(BUILD_DIR)$(TEST_DIR)/$(TARGET)_test $(TEST_OBJ) $(SRC) $(LIBS)
	./$(BUILD_DIR)$(TEST_DIR)$(TARGET)_test

$(BUILD_DIR)$(TEST_DIR)%.o: %.c create_dir
	$(CC) $(CFLAGS) -c $< -o $@

create_dir:
	@mkdir -p $(BUILD_DIR)$(TEST_DIR)

gcov_report: test
	@echo $(GCC) --version
	@lcov --ignore-errors 14 -t "test" -c -d $(BUILD_DIR)$(TEST_DIR) -o $(BUILD_DIR)$(TEST_DIR)coverage.info
ifeq ("$(DISTRO)", "Darwin")
	@lcov --remove $(BUILD_DIR)$(TEST_DIR)coverage.info '/usr/*' --output-file $(BUILD_DIR)$(TEST_DIR)coverage.info
endif
	@genhtml $(BUILD_DIR)$(TEST_DIR)coverage.info -o $(BUILD_DIR)$(TEST_DIR)coverage_report
	-@open $(LCOV)

.PHONY: v
v: clangF test
	@valgrind --tool=memcheck --leak-check=yes ./$(BUILD_DIR)$(TEST_DIR)$(TARGET)_test

.PHONY: q
q: clangF
	@$(CC) $(CFLAGSNOERROR) $(SRC) && valgrind -q --tool=memcheck --leak-check=yes ./a.out

.PHONY: f
f: clangF
	@$(CC) $(CFLAGSNOERROR) $(SRC) $(FSANITIZE) && ./a.out

.PHONY: cppcheck
cppcheck: clangF
	-@$(CPPCHECK) $(CPPCHECKFLAGS) -I $(wildcard *.h) ./$(TETRIS_DIR)/ ./$(GUI_DIR)/

.PHONY: git
git:
	-git checkout -b develop
	-git switch develop
	-git add $(FILES_TO_FORMAT)
	-git add Makefile

clangF:
#	-@copy $(CFDIR).clang-format .clang-format
	-@$(CF) $(FILES_TO_FORMAT)

rebuild: clean all

.PHONY: clean
clean:
	-@rm -rf $(BUILD_DIR)
	-@rm -f $(TARGET).a
	-@rm -f a.out