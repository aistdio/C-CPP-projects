GCC=gcc -Wall -Wextra -std=c11 -Werror
CF=clang-format -i
COPYCF=cp ../../materials/linters/.clang-format .clang-format
CPP=cppcheck --enable=all --suppress=missingIncludeSystem
# Поменять название ниже
T1=s21_cat
Docker=../../materials/build/run.sh
cmd=

# -D for define (для флагов в src)
# -c for single/separate file compilation
# -o for name of compiled object

all: $(T1)

# Поменять clangF_onlyC на clangF, если в проекте есть .h файлы
$(T1):
	$(GCC) -o $(T1) $(T1).c

$(T1)_tests: $(T1)
	$(GCC) -o $(T1)_tests $(T1)_tests.c

1: $(T1)
	./$(T1) $(cmd)

t1: clean
	bash $(T1)_tests.sh

v1: $(T1)
	valgrind --tool=memcheck --leak-check=yes  ./$(T1) $(cmd) |& grep -e contexts -e SUCCESS

f1:
	gcc -o $(T1) $(T1).c -fsanitize=address -fsanitize=leak -fsanitize=undefined -fsanitize=unreachable && ./$(T1) $(cmd)

d1:
	chmod 777 $(Docker)
	./$(Docker)

l1: $(T1)
	leaks --atExit -- ./$(T1) $(cmd)

clangF_onlyC:
	$(COPYCF)
	$(CF) *.c

clangF:
	$(COPYCF)
	$(CF) *.c
	$(CF) *.h

push:
	git checkout develop
	git add *.c
	git add *.h
	git add *.sh
	git add Makefile
	git commit -m 'Quests'
	git push origin develop

CPP:
	$(CPP) *.c
	$(CPP) *.h

clean:
	rm -f $(T1)
	rm -f $(T1)_tests
	rm -rf *.o
	rm -rf *.out
	rm -rf tests
	rm -f test.txt
#	rm -rf ../build/*_*

rebuild: clean all