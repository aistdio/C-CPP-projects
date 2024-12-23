GCC=gcc -Wall -Werror -Wextra
CF=clang-format -i
COPYCF=cp ../materials/linters/.clang-format .clang-format
Q1=../build/graph

CPP=cppcheck --enable=all --suppress=missingIncludeSystem

# -D for define (для флагов в src)
# -c for single/separate file compilation
# -o for name of compiled object

all: clangF CPP build

build:
	$(GCC) -c -o graph.o graph.c
	$(GCC) -c -o stack.o stack.c
	$(GCC) -c -o pNotation.o pNotation.c
	$(GCC) -o $(Q1) graph.o stack.o pNotation.o

1: build
	./$(Q1)

l1: build
	leaks --atExit -- ./$(Q1)

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