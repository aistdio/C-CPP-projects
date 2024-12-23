GCC=gcc -Wall -Werror -Wextra -Wshadow
CF=clang-format -i
COPYCF=cp ../materials/linters/.clang-format .clang-format
Q1=../build/Quest_1

CPP=cppcheck --enable=all --suppress=missingIncludeSystem

# -D for define (для флагов в src)
# -c for single/separate file compilation
# -o for name of compiled object

all: clangF CPP print_module

print_module:
	$(GCC) -c -o main_module_entry_point.o main_module_entry_point.c
	$(GCC) -c -o documentation_module.o documentation_module.c
	$(GCC) -c -o print_module.o print_module.c
	$(GCC) -o $(Q1) main_module_entry_point.o documentation_module.o print_module.o

1: print_module
	./$(Q1)

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