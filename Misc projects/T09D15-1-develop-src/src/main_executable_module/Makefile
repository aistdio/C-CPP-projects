# Clang-format не работает, воспринимает файл как С файл
CC=gcc
CWF=gcc -Wall -Wextra -Werror

SRCS=main_executable_module.c ../data_module/data_process.c ../yet_another_decision_module/decision.c ../data_libs/data_stat.c ../data_libs/data_io.c
HEADERS=../data_module/data_process.h ../yet_another_decision_module/decision.h ../data_libs/data_stat.h ../data_libs/data_io.h
MC=../data_module/data_process.o ../yet_another_decision_module/decision.o ../data_libs/data_stat.o ../data_libs/data_io.o
MAIN_MC=main_executable_module.o

all: $(SRCS) ../../build/Quest_3 build_with_static build_with_dynamic

#build : $(MAIN_MC) $(MC)
#	$(CC) $(MC) $(MAIN_MC) - o../../ build / Quest_3

# "main.o" target depends on main.c
# $(MAIN_MC): main_executable_module.c
#	$(CWF) main_executable_module.c

# data_process.o: ../data_module/data_process.c
#	$(CWF) ../data_module/data_process.c

# decision.o: ../yet_another_decision_module/decision.c
#	$(CWF) ../yet_another_decision_module/decision.c

# data_stat.o: ../data_libs/data_stat.c
#	$(CWF) ../data_libs/data_stat.c

# data_io.o: ../data_libs/data_io.c
#	$(CWF) ../data_libs/data_io.c

build_with_static: $(MAIN_MC) $(MC) data_stat.a
	$(CWF) $(MAIN_MC) $(MC) -o ../../build/Quest_5

build_with_dynamic: $(MAIN_MC) ../yet_another_decision_module/decision.o ../data_libs/data_stat.o ../data_libs/data_io.o data_process.so
	$(CWF) $(MAIN_MC) $(MC) -o ../../build/Quest_6

data_process.so: ../data_module/data_process.o ../data_libs/data_stat.o
	$(CWF) -shared -o data_process.so ../data_module/data_process.o ../data_libs/data_stat.o

data_stat.a: ../data_libs/data_stat.o
	ar rcs data_stat.a ../data_libs/data_stat.o

../../build/Quest_3: $(MAIN_MC) $(MC)
	$(CWF) $(MAIN_MC) $(MC) -o ../../build/Quest_3

clean:
	rm -rf ../../*/*/*.o
	rm -rf ../../*/*/*.out
	rm -rf ../../*/*.out
	rm -rf ../../*/*/*.a
	rm -rf ../../*/*.a
	rm -rf ../../*/*/*.so
	rm -rf ../../*/*.so
	rm -rf ../*/*.gch

rebuild: clean all