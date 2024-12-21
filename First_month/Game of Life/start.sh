#!/bin/bash

# Количество аргументов
if [[ $# -eq 0 ]]
then 
    echo "Enter name of the file: ./start.sh NAME.txt"
    
else if [[ -f "$1" ]] 
    then    gcc -Wall -Wextra -Werror game_of_life.c -lncurses && cat "$1" | ./a.out
    else    echo "No file, enter .TXT file from folder P02D13-1/src/"
    fi
fi