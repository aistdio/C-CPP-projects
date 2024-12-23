GCC=gcc -Wall -Werror -Wextra -Wshadow
CF=clang-format -i
COPYCF=cp ../materials/linters/.clang-format .clang-format
Quest_1=../build/Quest_1
Quest_2=../build/Quest_2
Quest_3=../build/Quest_3
CPP=cppcheck --enable=all --suppress=missingIncludeSystem

# -D for define (для флагов в src)
# -c for single/separate file compilation
# -o for name of compiled object

all: clangF CPP door_struct list_test stack_test

door_struct:
	$(GCC) -c -o dmanager_module.o dmanager_module.c
	$(GCC) -o $(Quest_1) dmanager_module.o

list_test:
	$(GCC) -c -o list.o list.c
	$(GCC) -c -o list_test.o list_test.c
	$(GCC) -o $(Quest_2) list.o list_test.o

stack_test:
	$(GCC) -c -o stack_test.o stack_test.c
	$(GCC) -c -o stack.o stack.c
	$(GCC) -o $(Quest_3) stack_test.o stack.o

1: door_struct
	./$(Quest_1)

2: list_test
	./$(Quest_2)

3: stack_test
	./$(Quest_3)

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
	$(CPP) *.h

clean:
	rm -rf *.o
	rm -rf *.out
	rm -rf ../build/*_*

rebuild: clean all