#!/bin/bash
DIRECTORY="tests"
make s21_grep_tests
./s21_grep_tests

if [ ! -d "$DIRECTORY" ]; then
  mkdir "$DIRECTORY"
fi

cp test.txt "$DIRECTORY"/test.txt
cp s21_grep "$DIRECTORY"/s21_grep

cd "$DIRECTORY"

counter=1

# СТРУКТУРА ТЕСТОВ:
# 0. Задаем тест-кейсу флаг
# 1. Применяем команду grep и ./s21_grep с флагом
# 2. Сравнение через diff
# 3. Вывод в консоль результата

# TEST 1: Без флагов
word="asd"
grep "$word" test.txt > grep"$counter".txt
./s21_grep "$word" test.txt > grep"$counter"_s21.txt
echo "--- Testing ./s21_grep "$word" test.txt"

# valgrind --tool=memcheck --leak-check=yes ./s21_grep "$word" test.txt

DIFF=$(diff grep"$counter".txt grep"$counter"_s21.txt)
if [ "$DIFF" == "" ]; then
  echo "Test $counter: SUCCESS"
else
  echo "Test $counter: FAIL"
  echo "---DIFF OUTPUT---"
  diff grep"$counter".txt grep"$counter"_s21.txt
  echo "---END OF DIFF---"
fi
((counter++))


# TESTS 2: Тестируем каждый флаг из задания
word="asd"
flags="-i"
grep "$flags" "$word" test.txt > grep"$counter".txt
./s21_grep "$flags" "$word" test.txt > grep"$counter"_s21.txt
echo "--- Testing ./s21_grep "$flags" "$word" test.txt"

# valgrind --tool=memcheck --leak-check=yes ./s21_grep "$flags" "$word" test.txt

DIFF=$(diff grep"$counter".txt grep"$counter"_s21.txt)
if [ "$DIFF" == "" ]; then
  echo "Test $counter: SUCCESS"
else
  echo "Test $counter: FAIL"
  echo "---DIFF OUTPUT---"
  diff grep"$counter".txt grep"$counter"_s21.txt
  echo "---END OF DIFF---"
fi
((counter++))


word="asd"
flags="-e"
grep "$flags" "$word" test.txt > grep"$counter".txt
./s21_grep "$flags" "$word" test.txt > grep"$counter"_s21.txt
echo "--- Testing ./s21_grep "$flags" "$word" test.txt"
# valgrind --tool=memcheck --leak-check=yes ./s21_grep "$flags" "$word" test.txt
DIFF=$(diff grep"$counter".txt grep"$counter"_s21.txt)
if [ "$DIFF" == "" ]; then
  echo "Test $counter: SUCCESS"
else
  echo "Test $counter: FAIL"
  echo "---DIFF OUTPUT---"
  diff grep"$counter".txt grep"$counter"_s21.txt
  echo "---END OF DIFF---"
fi
((counter++))


word="asd"
flags="-v"
grep "$flags" "$word" test.txt > grep"$counter".txt
./s21_grep "$flags" "$word" test.txt > grep"$counter"_s21.txt
echo "--- Testing ./s21_grep "$flags" "$word" test.txt"
# valgrind --tool=memcheck --leak-check=yes ./s21_grep "$flags" "$word" test.txt
DIFF=$(diff grep"$counter".txt grep"$counter"_s21.txt)
if [ "$DIFF" == "" ]; then
  echo "Test $counter: SUCCESS"
else
  echo "Test $counter: FAIL"
  echo "---DIFF OUTPUT---"
  diff grep"$counter".txt grep"$counter"_s21.txt
  echo "---END OF DIFF---"
fi
((counter++))


word="asd"
flags="-c"
grep "$flags" "$word" test.txt > grep"$counter".txt
./s21_grep "$flags" "$word" test.txt > grep"$counter"_s21.txt
echo "--- Testing ./s21_grep "$flags" "$word" test.txt"
# valgrind --tool=memcheck --leak-check=yes ./s21_grep "$flags" "$word" test.txt
DIFF=$(diff grep"$counter".txt grep"$counter"_s21.txt)
if [ "$DIFF" == "" ]; then
  echo "Test $counter: SUCCESS"
else
  echo "Test $counter: FAIL"
  echo "---DIFF OUTPUT---"
  diff grep"$counter".txt grep"$counter"_s21.txt
  echo "---END OF DIFF---"
fi
((counter++))


word="asd"
flags="-l"
grep "$flags" "$word" test.txt > grep"$counter".txt
./s21_grep "$flags" "$word" test.txt > grep"$counter"_s21.txt
echo "--- Testing ./s21_grep "$flags" "$word" test.txt"
# valgrind --tool=memcheck --leak-check=yes ./s21_grep "$flags" "$word" test.txt
DIFF=$(diff grep"$counter".txt grep"$counter"_s21.txt)
if [ "$DIFF" == "" ]; then
  echo "Test $counter: SUCCESS"
else
  echo "Test $counter: FAIL"
  echo "---DIFF OUTPUT---"
  diff grep"$counter".txt grep"$counter"_s21.txt
  echo "---END OF DIFF---"
fi
((counter++))


word="asd"
flags="-n"
grep "$flags" "$word" test.txt > grep"$counter".txt
./s21_grep "$flags" "$word" test.txt > grep"$counter"_s21.txt
echo "--- Testing ./s21_grep "$flags" "$word" test.txt"
# valgrind --tool=memcheck --leak-check=yes ./s21_grep "$flags" "$word" test.txt
DIFF=$(diff grep"$counter".txt grep"$counter"_s21.txt)
if [ "$DIFF" == "" ]; then
  echo "Test $counter: SUCCESS"
else
  echo "Test $counter: FAIL"
  echo "---DIFF OUTPUT---"
  diff grep"$counter".txt grep"$counter"_s21.txt
  echo "---END OF DIFF---"
fi
((counter++))


word="asd"
flags="-h"
grep "$flags" "$word" test.txt > grep"$counter".txt
./s21_grep "$flags" "$word" test.txt > grep"$counter"_s21.txt
echo "--- Testing ./s21_grep "$flags" "$word" test.txt"
# valgrind --tool=memcheck --leak-check=yes ./s21_grep "$flags" "$word" test.txt
DIFF=$(diff grep"$counter".txt grep"$counter"_s21.txt)
if [ "$DIFF" == "" ]; then
  echo "Test $counter: SUCCESS"
else
  echo "Test $counter: FAIL"
  echo "---DIFF OUTPUT---"
  diff grep"$counter".txt grep"$counter"_s21.txt
  echo "---END OF DIFF---"
fi
((counter++))


word="asd"
flags="-s"
grep "$flags" "$word" test.txt > grep"$counter".txt
./s21_grep "$flags" "$word" test.txt > grep"$counter"_s21.txt
echo "--- Testing ./s21_grep "$flags" "$word" test.txt"
# valgrind --tool=memcheck --leak-check=yes ./s21_grep "$flags" "$word" test.txt
DIFF=$(diff grep"$counter".txt grep"$counter"_s21.txt)
if [ "$DIFF" == "" ]; then
  echo "Test $counter: SUCCESS"
else
  echo "Test $counter: FAIL"
  echo "---DIFF OUTPUT---"
  diff grep"$counter".txt grep"$counter"_s21.txt
  echo "---END OF DIFF---"
fi
((counter++))


# -f В баше почему-то не работает - греп так не видит названия дальше флага -f
# grep -f test0.txt test.txt > grep"$counter".txt
# ./s21_grep -f test0.txt test.txt > grep"$counter"_s21.txt
# echo "--- Testing ./s21_grep -f test0.txt test.txt"

# DIFF=$(diff grep"$counter".txt grep"$counter"_s21.txt)
# if [ "$DIFF" == "" ]; then
#   echo "Test $counter: SUCCESS"
# else
#   echo "Test $counter: FAIL"
#   echo "---DIFF OUTPUT---"
#   diff grep"$counter".txt grep"$counter"_s21.txt
#   echo "---END OF DIFF---"
# fi
# ((counter++))


word="asd"
flags="-o"
grep "$flags" "$word" test.txt > grep"$counter".txt
./s21_grep "$flags" "$word" test.txt > grep"$counter"_s21.txt
echo "--- Testing ./s21_grep "$flags" "$word" test.txt"
# valgrind --tool=memcheck --leak-check=yes ./s21_grep "$flags" "$word" test.txt
DIFF=$(diff grep"$counter".txt grep"$counter"_s21.txt)
if [ "$DIFF" == "" ]; then
  echo "Test $counter: SUCCESS"
else
  echo "Test $counter: FAIL"
  echo "---DIFF OUTPUT---"
  diff grep"$counter".txt grep"$counter"_s21.txt
  echo "---END OF DIFF---"
fi
((counter++))


# TESTS 3: With multiple files/patterns
word1="asd"
word2="s"
flagsM="-inv"
flags="$flagsM"
case="-e $word1 -e $word2"
filesM="test.txt test.txt"
files="test.txt"

grep $flags $case $files > grep"$counter".txt
./s21_grep $flags $case $files > grep"$counter"_s21.txt
echo "--- Testing ./s21_grep $flags $case $files"
# valgrind --tool=memcheck --leak-check=yes ./s21_grep $flags $case $files
DIFF=$(diff grep"$counter".txt grep"$counter"_s21.txt)
if [ "$DIFF" == "" ]; then
  echo "Test $counter: SUCCESS"
else
  echo "Test $counter: FAIL"
  echo "---DIFF OUTPUT---"
  diff grep"$counter".txt grep"$counter"_s21.txt
  echo "---END OF DIFF---"
fi
((counter++))

word1="asd"
flags="$flagsM"
case="$word1"
files="$filesM"

grep $flags $case $files > grep"$counter".txt
./s21_grep $flags $case $files > grep"$counter"_s21.txt
echo "--- Testing ./s21_grep $flags $case $files"
# valgrind --tool=memcheck --leak-check=yes ./s21_grep $flags $case $files
DIFF=$(diff grep"$counter".txt grep"$counter"_s21.txt)
if [ "$DIFF" == "" ]; then
  echo "Test $counter: SUCCESS"
else
  echo "Test $counter: FAIL"
  echo "---DIFF OUTPUT---"
  diff grep"$counter".txt grep"$counter"_s21.txt
  echo "---END OF DIFF---"
fi
((counter++))


word1="asd"
word2="s"
flags="$flagsM"
case="-e $word1 -e $word2"
files="$filesM"

grep $flags $case $files > grep"$counter".txt
./s21_grep $flags $case $files > grep"$counter"_s21.txt
echo "--- Testing ./s21_grep $flags $case $files"
# valgrind --tool=memcheck --leak-check=yes ./s21_grep $flags $case $files
DIFF=$(diff grep"$counter".txt grep"$counter"_s21.txt)
if [ "$DIFF" == "" ]; then
  echo "Test $counter: SUCCESS"
else
  echo "Test $counter: FAIL"
  echo "---DIFF OUTPUT---"
  diff grep"$counter".txt grep"$counter"_s21.txt
  echo "---END OF DIFF---"
fi
((counter++))


# word1="asd"
# word2="s"
# flags="-ion"
# case="-e $word1 -e $word2"
# files="$filesM"

# grep $flags $case $files > grep"$counter".txt
# ./s21_grep $flags $case $files > grep"$counter"_s21.txt
# echo "--- Testing ./s21_grep $flags $case $files"

# DIFF=$(diff grep"$counter".txt grep"$counter"_s21.txt)
# if [ "$DIFF" == "" ]; then
#   echo "Test $counter: SUCCESS"
# else
#   echo "Test $counter: FAIL"
#   echo "---DIFF OUTPUT---"
#   diff grep"$counter".txt grep"$counter"_s21.txt
#   echo "---END OF DIFF---"
# fi
# ((counter++))


word1="asd"
word2="s"
flags="-ivnhs"
case="-e $word1 -e $word2"
files="$filesM"

grep $flags $case $files > grep"$counter".txt
./s21_grep $flags $case $files > grep"$counter"_s21.txt
echo "--- Testing ./s21_grep $flags $case $files"
# valgrind --tool=memcheck --leak-check=yes ./s21_grep $flags $case $files
DIFF=$(diff grep"$counter".txt grep"$counter"_s21.txt)
if [ "$DIFF" == "" ]; then
  echo "Test $counter: SUCCESS"
else
  echo "Test $counter: FAIL"
  echo "---DIFF OUTPUT---"
  diff grep"$counter".txt grep"$counter"_s21.txt
  echo "---END OF DIFF---"
fi
((counter++))


word1="asd"
word2="s"
flags="-ivlcnhso"
case="-e $word1 -e $word2"
files="$filesM"

grep $flags $case $files > grep"$counter".txt
./s21_grep $flags $case $files > grep"$counter"_s21.txt
echo "--- Testing ./s21_grep $flags $case $files"
# valgrind --tool=memcheck --leak-check=yes ./s21_grep $flags $case $files
DIFF=$(diff grep"$counter".txt grep"$counter"_s21.txt)
if [ "$DIFF" == "" ]; then
  echo "Test $counter: SUCCESS"
else
  echo "Test $counter: FAIL"
  echo "---DIFF OUTPUT---"
  diff grep"$counter".txt grep"$counter"_s21.txt
  echo "---END OF DIFF---"
fi
((counter++))


word1="asd"
word2="s"
flags="-ivcnhso"
case="-e $word1 -e $word2"
files="$filesM"

grep $flags $case $files > grep"$counter".txt
./s21_grep $flags $case $files > grep"$counter"_s21.txt
echo "--- Testing ./s21_grep $flags $case $files"
# valgrind --tool=memcheck --leak-check=yes ./s21_grep $flags $case $files
DIFF=$(diff grep"$counter".txt grep"$counter"_s21.txt)
if [ "$DIFF" == "" ]; then
  echo "Test $counter: SUCCESS"
else
  echo "Test $counter: FAIL"
  echo "---DIFF OUTPUT---"
  diff grep"$counter".txt grep"$counter"_s21.txt
  echo "---END OF DIFF---"
fi
((counter++))


word1="asd"
word2="s"
flags="-ivnhso"
case="-e $word1 -e $word2"
files="$filesM"

grep $flags $case $files > grep"$counter".txt
./s21_grep $flags $case $files > grep"$counter"_s21.txt
echo "--- Testing ./s21_grep $flags $case $files"
# valgrind --tool=memcheck --leak-check=yes ./s21_grep $flags $case $files
DIFF=$(diff grep"$counter".txt grep"$counter"_s21.txt)
if [ "$DIFF" == "" ]; then
  echo "Test $counter: SUCCESS"
else
  echo "Test $counter: FAIL"
  echo "---DIFF OUTPUT---"
  diff grep"$counter".txt grep"$counter"_s21.txt
  echo "---END OF DIFF---"
fi
((counter++))


word1="asd"
word2="s"
flags="-inhso"
case="-e $word1 -e $word2"
files="$filesM"

grep $flags $case $files > grep"$counter".txt
./s21_grep $flags $case $files > grep"$counter"_s21.txt
echo "--- Testing ./s21_grep $flags $case $files"
# valgrind --tool=memcheck --leak-check=yes --track-origins=yes ./s21_grep $flags $case $files
DIFF=$(diff grep"$counter".txt grep"$counter"_s21.txt)
if [ "$DIFF" == "" ]; then
  echo "Test $counter: SUCCESS"
else
  echo "Test $counter: FAIL"
  echo "---DIFF OUTPUT---"
  diff grep"$counter".txt grep"$counter"_s21.txt
  echo "---END OF DIFF---"
fi
((counter++))


word1="asd"
word2="s"
flags="-ilcnhso"
case="-e $word1 -e $word2"
files="$filesM"

grep $flags $case $files > grep"$counter".txt
./s21_grep $flags $case $files > grep"$counter"_s21.txt
echo "--- Testing ./s21_grep $flags $case $files"
# valgrind --tool=memcheck --leak-check=yes ./s21_grep $flags $case $files
DIFF=$(diff grep"$counter".txt grep"$counter"_s21.txt)
if [ "$DIFF" == "" ]; then
  echo "Test $counter: SUCCESS"
else
  echo "Test $counter: FAIL"
  echo "---DIFF OUTPUT---"
  diff grep"$counter".txt grep"$counter"_s21.txt
  echo "---END OF DIFF---"
fi
((counter++))


# Regular * for files
word1="asd"
word2="s"
flags="$flagsM"
case="$word1"
files="*est.txt"

grep $flags $case $files > grep"$counter".txt
./s21_grep $flags $case $files > grep"$counter"_s21.txt
echo "--- Testing ./s21_grep $flags $case $files"
# valgrind --tool=memcheck --leak-check=yes ./s21_grep $flags $case $files
DIFF=$(diff grep"$counter".txt grep"$counter"_s21.txt)
if [ "$DIFF" == "" ]; then
  echo "Test $counter: SUCCESS"
else
  echo "Test $counter: FAIL"
  echo "---DIFF OUTPUT---"
  diff grep"$counter".txt grep"$counter"_s21.txt
  echo "---END OF DIFF---"
fi
((counter++))


# word="asd"
# flags="-c"
# grep "$flags" "$word" test.txt > grep"$counter".txt
# ./s21_grep "$flags" "$word" test.txt > grep"$counter"_s21.txt
# echo "--- Testing ./s21_grep "$flags" "$word" test.txt"

# DIFF=$(diff grep"$counter".txt grep"$counter"_s21.txt)
# if [ "$DIFF" == "" ]; then
#   echo "Test $counter: SUCCESS"
# else
#   echo "Test $counter: FAIL"
#   echo "---DIFF OUTPUT---"
#   diff grep"$counter".txt grep"$counter"_s21.txt
#   echo "---END OF DIFF---"
# fi
# ((counter++))


# word="asd"
# flags="-l"
# grep "$flags" "$word" test.txt > grep"$counter".txt
# ./s21_grep "$flags" "$word" test.txt > grep"$counter"_s21.txt
# echo "--- Testing ./s21_grep "$flags" "$word" test.txt"

# DIFF=$(diff grep"$counter".txt grep"$counter"_s21.txt)
# if [ "$DIFF" == "" ]; then
#   echo "Test $counter: SUCCESS"
# else
#   echo "Test $counter: FAIL"
#   echo "---DIFF OUTPUT---"
#   diff grep"$counter".txt grep"$counter"_s21.txt
#   echo "---END OF DIFF---"
# fi
# ((counter++))


# word="asd"
# flags="-n"
# grep "$flags" "$word" test.txt > grep"$counter".txt
# ./s21_grep "$flags" "$word" test.txt > grep"$counter"_s21.txt
# echo "--- Testing ./s21_grep "$flags" "$word" test.txt"

# DIFF=$(diff grep"$counter".txt grep"$counter"_s21.txt)
# if [ "$DIFF" == "" ]; then
#   echo "Test $counter: SUCCESS"
# else
#   echo "Test $counter: FAIL"
#   echo "---DIFF OUTPUT---"
#   diff grep"$counter".txt grep"$counter"_s21.txt
#   echo "---END OF DIFF---"
# fi
# ((counter++))


# case="-i"
# grep "$word" test.txt "$case" > grep"$counter".txt
# ./s21_grep "$word" test.txt "$case" > grep"$counter"_s21.txt

# DIFF=$(diff grep"$counter".txt grep"$counter"_s21.txt)
# if [ "$DIFF" == "" ]; then
#   echo "Test $counter: SUCCESS"
# else
#   echo "Test $counter: FAIL"
#   echo "---DIFF OUTPUT---"
#   diff grep"$counter".txt grep"$counter"_s21.txt
#   echo "---END OF DIFF---"
# fi
# ((counter++))


# case="-v"
# grep "$word" test.txt "$case" > grep"$counter".txt
# ./s21_grep "$word" test.txt "$case" > grep"$counter"_s21.txt

# DIFF=$(diff grep"$counter".txt grep"$counter"_s21.txt)
# if [ "$DIFF" == "" ]; then
#   echo "Test $counter: SUCCESS"
# else
#   echo "Test $counter: FAIL"
#   echo "---DIFF OUTPUT---"
#   diff grep"$counter".txt grep"$counter"_s21.txt
#   echo "---END OF DIFF---"
# fi
# ((counter++))


# case="-c"
# grep "$word" test.txt "$case" > grep"$counter".txt
# ./s21_grep "$word" test.txt "$case" > grep"$counter"_s21.txt

# DIFF=$(diff grep"$counter".txt grep"$counter"_s21.txt)
# if [ "$DIFF" == "" ]; then
#   echo "Test $counter: SUCCESS"
# else
#   echo "Test $counter: FAIL"
#   echo "---DIFF OUTPUT---"
#   diff grep"$counter".txt grep"$counter"_s21.txt
#   echo "---END OF DIFF---"
# fi
# ((counter++))


# case="-l"
# grep "$word" test.txt "$case" > grep"$counter".txt
# ./s21_grep "$word" test.txt "$case" > grep"$counter"_s21.txt

# DIFF=$(diff grep"$counter".txt grep"$counter"_s21.txt)
# if [ "$DIFF" == "" ]; then
#   echo "Test $counter: SUCCESS"
# else
#   echo "Test $counter: FAIL"
#   echo "---DIFF OUTPUT---"
#   diff grep"$counter".txt grep"$counter"_s21.txt
#   echo "---END OF DIFF---"
# fi
# ((counter++))


# case="-n"
# grep "$word" test.txt "$case" > grep"$counter".txt
# ./s21_grep "$word" test.txt "$case" > grep"$counter"_s21.txt

# DIFF=$(diff grep"$counter".txt grep"$counter"_s21.txt)
# if [ "$DIFF" == "" ]; then
#   echo "Test $counter: SUCCESS"
# else
#   echo "Test $counter: FAIL"
#   echo "---DIFF OUTPUT---"
#   diff grep"$counter".txt grep"$counter"_s21.txt
#   echo "---END OF DIFF---"
# fi
# ((counter++))


# case="-h"
# grep "$word" test.txt "$case" > grep"$counter".txt
# ./s21_grep "$word" test.txt "$case" > grep"$counter"_s21.txt

# DIFF=$(diff grep"$counter".txt grep"$counter"_s21.txt)
# if [ "$DIFF" == "" ]; then
#   echo "Test $counter: SUCCESS"
# else
#   echo "Test $counter: FAIL"
#   echo "---DIFF OUTPUT---"
#   diff grep"$counter".txt grep"$counter"_s21.txt
#   echo "---END OF DIFF---"
# fi
# ((counter++))


# case="-s"
# grep "$word" test.txt "$case" > grep"$counter".txt
# ./s21_grep "$word" test.txt "$case" > grep"$counter"_s21.txt

# DIFF=$(diff grep"$counter".txt grep"$counter"_s21.txt)
# if [ "$DIFF" == "" ]; then
#   echo "Test $counter: SUCCESS"
# else
#   echo "Test $counter: FAIL"
#   echo "---DIFF OUTPUT---"
#   diff grep"$counter".txt grep"$counter"_s21.txt
#   echo "---END OF DIFF---"
# fi
# ((counter++))


# case="-f"
# grep "$word" test.txt "$case" > grep"$counter".txt
# ./s21_grep "$word" test.txt "$case" > grep"$counter"_s21.txt

# DIFF=$(diff grep"$counter".txt grep"$counter"_s21.txt)
# if [ "$DIFF" == "" ]; then
#   echo "Test $counter: SUCCESS"
# else
#   echo "Test $counter: FAIL"
#   echo "---DIFF OUTPUT---"
#   diff grep"$counter".txt grep"$counter"_s21.txt
#   echo "---END OF DIFF---"
# fi
# ((counter++))


# case="-o"
# grep "$word" test.txt "$case" > grep"$counter".txt
# ./s21_grep "$word" test.txt "$case" > grep"$counter"_s21.txt

# DIFF=$(diff grep"$counter".txt grep"$counter"_s21.txt)
# if [ "$DIFF" == "" ]; then
#   echo "Test $counter: SUCCESS"
# else
#   echo "Test $counter: FAIL"
#   echo "---DIFF OUTPUT---"
#   diff grep"$counter".txt grep"$counter"_s21.txt
#   echo "---END OF DIFF---"
# fi
# ((counter++))


# case="-iv"
# grep "$word" test.txt "$case" > grep"$counter".txt
# ./s21_grep "$word" test.txt "$case" > grep"$counter"_s21.txt

# DIFF=$(diff grep"$counter".txt grep"$counter"_s21.txt)
# if [ "$DIFF" == "" ]; then
#   echo "Test $counter: SUCCESS"
# else
#   echo "Test $counter: FAIL"
#   echo "---DIFF OUTPUT---"
#   diff grep"$counter".txt grep"$counter"_s21.txt
#   echo "---END OF DIFF---"
# fi
# ((counter++))


# TESTS 3: With mixed flags
# case="-in"
# grep "$word" test.txt "$case" > grep"$counter".txt
# ./s21_grep "$word" test.txt "$case" > grep"$counter"_s21.txt

# DIFF=$(diff grep"$counter".txt grep"$counter"_s21.txt)
# if [ "$DIFF" == "" ]; then
#   echo "Test $counter: SUCCESS"
# else
#   echo "Test $counter: FAIL"
#   echo "---DIFF OUTPUT---"
#   diff grep"$counter".txt grep"$counter"_s21.txt
#   echo "---END OF DIFF---"
# fi
# ((counter++))

# TESTS 4: With multiple long options
# case="--number-nonblank --number --squeeze-blank"
# grep "$word" test.txt "$case" > grep"$counter".txt
# ./s21_grep "$word" test.txt "$case" > grep"$counter"_s21.txt

# DIFF=$(diff grep"$counter".txt grep"$counter"_s21.txt)
# if [ "$DIFF" == "" ]; then
#   echo "Test $counter: SUCCESS"
# else
#   echo "Test $counter: FAIL"
#   echo "---DIFF OUTPUT---"
#   diff grep"$counter".txt grep"$counter"_s21.txt
#   echo "---END OF DIFF---"
# fi
# ((counter++))

# TESTS 5: With all of multiple flags and long options
# case="-b -e -E -n -s -t -T -v --number-nonblank --number --squeeze-blank"
# grep "$word" test.txt "$case" > grep"$counter".txt
# ./s21_grep "$word" test.txt "$case" > grep"$counter"_s21.txt

# DIFF=$(diff grep"$counter".txt grep"$counter"_s21.txt)
# if [ "$DIFF" == "" ]; then
#   echo "Test $counter: SUCCESS"
# else
#   echo "Test $counter: FAIL"
#   echo "---DIFF OUTPUT---"
#   diff grep"$counter".txt grep"$counter"_s21.txt
#   echo "---END OF DIFF---"
# fi
# ((counter++))