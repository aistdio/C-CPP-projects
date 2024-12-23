GCC=gcc -Wall -Werror -Wextra -std=c11
CF=clang-format -i
COPYCF=cp ../materials/linters/.clang-format .clang-format
Q1=../build/cipher

CPP=cppcheck --enable=all --suppress=missingIncludeSystem

# -D for define (для флагов в src)
# -c for single/separate file compilation
# -o for name of compiled object

all: clangF CPP cipher

cipher:
	$(GCC) -o $(Q1) cipher.c

1: cipher
	./$(Q1)

l1: cipher
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