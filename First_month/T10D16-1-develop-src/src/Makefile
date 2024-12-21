GCC=gcc -std=c11 -Wall -Werror -Wextra -Wshadow
CPP=cppcheck --enable=all --suppress=missingIncludeSystem
CF=clang-format -i
COPYCF=cp ../materials/linters/.clang-format .clang-format
SRCS=s21_string_test.c s21_string.c
OBJECTS=s21_string_test.c s21_string.c
Quest_1=../build/Quest_1
Quest_2=../build/Quest_2
Quest_3=../build/Quest_3
Quest_4=../build/Quest_4
Quest_5=../build/Quest_5
Quest_6=../build/Quest_6
Quest_7=../build/Quest_7

# -D for define (для флагов в src)
# -c for single/separate file compilation
# -o for name of compiled object

all: clangF strlen_tests strcmp_tests strcpy_tests strcat_tests strchr_tests

strlen_tests:
	$(GCC) -c -D QUEST1 -o s21_string_test.o s21_string_test.c
	$(GCC) -c -o s21_string.o s21_string.c
	$(GCC) -o $(Quest_1) s21_string_test.o s21_string.o

strcmp_tests:
	$(GCC) -c -D QUEST2 -o s21_string_test.o s21_string_test.c
	$(GCC) -c -o s21_string.o s21_string.c
	$(GCC) -o $(Quest_2) s21_string_test.o s21_string.o

strcpy_tests:
	$(GCC) -c -D QUEST3 -o s21_string_test.o s21_string_test.c
	$(GCC) -c -o s21_string.o s21_string.c
	$(GCC) -o $(Quest_3) s21_string.o s21_string_test.o

strcat_tests:
	$(GCC) -c -D QUEST4 -o s21_string_test.o s21_string_test.c
	$(GCC) -c -o s21_string.o s21_string.c
	$(GCC) -o $(Quest_4) s21_string.o s21_string_test.o

strchr_tests:
	$(GCC) -c -D QUEST5 -o s21_string_test.o s21_string_test.c
	$(GCC) -c -o s21_string.o s21_string.c
	$(GCC) -o $(Quest_5) s21_string.o s21_string_test.o

strstr_tests:
	$(GCC) -c -D QUEST5 -o s21_string_test.o s21_string_test.c
	$(GCC) -c -o s21_string.o s21_string.c
	$(GCC) -o $(Quest_6) s21_string.o s21_string_test.o

strtok_tests:
	$(GCC) -c -D QUEST5 -o s21_string_test.o s21_string_test.c
	$(GCC) -c -o s21_string.o s21_string.c
	$(GCC) -o $(Quest_7) s21_string.o s21_string_test.o

clangF:
	$(COPYCF)
	$(CF) *.c
	$(CF) *.h

push:
	git checkout develop
	git add *.c
	git add *.h
	git add Makefile
	git commit -m 'Quests'
	git push origin develop

CPP:
	$(CPP) *.c

1: strlen_tests
	./$(Quest_1)

2: strcmp_tests
	./$(Quest_2)

3: strcpy_tests
	./$(Quest_3)

4: strcat_tests
	./$(Quest_4)

5: strchr_tests
	./$(Quest_5)

6: strstr_tests
	./$(Quest_6)

7: strtok_tests
	./$(Quest_7)

clean:
	rm -rf *.o
	rm -rf *.out
	rm -rf ../build/*_*

rebuild: clean all