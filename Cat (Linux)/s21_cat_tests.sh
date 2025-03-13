#!/bin/bash
DIRECTORY="tests"
make s21_cat_tests
./s21_cat_tests

if [ ! -d "$DIRECTORY" ]; then
  mkdir "$DIRECTORY"
fi

cp test.txt "$DIRECTORY"/test.txt
cp s21_cat "$DIRECTORY"/s21_cat

cd "$DIRECTORY"

counter=1

# СТРУКТУРА ТЕСТОВ:
# 0. Задаем тест-кейсу флаг
# 1. Применяем команду cat и ./s21_cat с флагом
# 2. Сравнение через diff
# 3. Вывод в консоль результата

# TEST 1: Без флагов
cat test.txt > cat"$counter".txt
./s21_cat test.txt > cat"$counter"_s21.txt
echo "--- Testing ./s21_cat test.txt"
# valgrind --tool=memcheck --leak-check=yes ./s21_cat test.txt
DIFF=$(diff cat"$counter".txt cat"$counter"_s21.txt)
if [ "$DIFF" == "" ]; then
  echo "Test $counter: SUCCESS"
else
  echo "Test $counter: FAIL"
  echo "---DIFF OUTPUT---"
  diff cat"$counter".txt cat"$counter"_s21.txt
  echo "---END OF DIFF---"
fi
((counter++))


# TESTS 2: Тестируем каждый флаг из задания
case="-b"
cat test.txt "$case" > cat"$counter".txt
./s21_cat test.txt "$case" > cat"$counter"_s21.txt
echo "--- Testing ./s21_cat test.txt $case"
# valgrind --tool=memcheck --leak-check=yes ./s21_cat test.txt "$case"
DIFF=$(diff cat"$counter".txt cat"$counter"_s21.txt)
if [ "$DIFF" == "" ]; then
  echo "Test $counter: SUCCESS"
else
  echo "Test $counter: FAIL"
  echo "---DIFF OUTPUT---"
  diff cat"$counter".txt cat"$counter"_s21.txt
  echo "---END OF DIFF---"
fi
((counter++))


case="--number-nonblank"
cat test.txt "$case" > cat"$counter".txt
./s21_cat test.txt "$case" > cat"$counter"_s21.txt
echo "--- Testing ./s21_cat test.txt $case"
# valgrind --tool=memcheck --leak-check=yes ./s21_cat test.txt "$case"
DIFF=$(diff cat"$counter".txt cat"$counter"_s21.txt)
if [ "$DIFF" == "" ]; then
  echo "Test $counter: SUCCESS"
else
  echo "Test $counter: FAIL"
  echo "---DIFF OUTPUT---"
  diff cat"$counter".txt cat"$counter"_s21.txt
  echo "---END OF DIFF---"
fi
((counter++))


case="-e"
cat test.txt "$case" > cat"$counter".txt
./s21_cat test.txt "$case" > cat"$counter"_s21.txt
echo "--- Testing ./s21_cat test.txt $case"
# valgrind --tool=memcheck --leak-check=yes ./s21_cat test.txt "$case"
DIFF=$(diff cat"$counter".txt cat"$counter"_s21.txt)
if [ "$DIFF" == "" ]; then
  echo "Test $counter: SUCCESS"
else
  echo "Test $counter: FAIL"
  echo "---DIFF OUTPUT---"
  diff cat"$counter".txt cat"$counter"_s21.txt
  echo "---END OF DIFF---"
fi
((counter++))


case="-E"
cat test.txt "$case" > cat"$counter".txt
./s21_cat test.txt "$case" > cat"$counter"_s21.txt
echo "--- Testing ./s21_cat test.txt $case"
# valgrind --tool=memcheck --leak-check=yes ./s21_cat test.txt "$case"
DIFF=$(diff cat"$counter".txt cat"$counter"_s21.txt)
if [ "$DIFF" == "" ]; then
  echo "Test $counter: SUCCESS"
else
  echo "Test $counter: FAIL"
  echo "---DIFF OUTPUT---"
  diff cat"$counter".txt cat"$counter"_s21.txt
  echo "---END OF DIFF---"
fi
((counter++))


case="-n"
cat test.txt "$case" > cat"$counter".txt
./s21_cat test.txt "$case" > cat"$counter"_s21.txt
echo "--- Testing ./s21_cat test.txt $case"
# valgrind --tool=memcheck --leak-check=yes ./s21_cat test.txt "$case"
DIFF=$(diff cat"$counter".txt cat"$counter"_s21.txt)
if [ "$DIFF" == "" ]; then
  echo "Test $counter: SUCCESS"
else
  echo "Test $counter: FAIL"
  echo "---DIFF OUTPUT---"
  diff cat"$counter".txt cat"$counter"_s21.txt
  echo "---END OF DIFF---"
fi
((counter++))


case="--number"
cat test.txt "$case" > cat"$counter".txt
./s21_cat test.txt "$case" > cat"$counter"_s21.txt
echo "--- Testing ./s21_cat test.txt $case"
# valgrind --tool=memcheck --leak-check=yes ./s21_cat test.txt "$case"
DIFF=$(diff cat"$counter".txt cat"$counter"_s21.txt)
if [ "$DIFF" == "" ]; then
  echo "Test $counter: SUCCESS"
else
  echo "Test $counter: FAIL"
  echo "---DIFF OUTPUT---"
  diff cat"$counter".txt cat"$counter"_s21.txt
  echo "---END OF DIFF---"
fi
((counter++))


case="-s"
cat test.txt "$case" > cat"$counter".txt
./s21_cat test.txt "$case" > cat"$counter"_s21.txt
echo "--- Testing ./s21_cat test.txt $case"
# valgrind --tool=memcheck --leak-check=yes ./s21_cat test.txt "$case"
DIFF=$(diff cat"$counter".txt cat"$counter"_s21.txt)
if [ "$DIFF" == "" ]; then
  echo "Test $counter: SUCCESS"
else
  echo "Test $counter: FAIL"
  echo "---DIFF OUTPUT---"
  diff cat"$counter".txt cat"$counter"_s21.txt
  echo "---END OF DIFF---"
fi
((counter++))


case="--squeeze-blank"
cat test.txt "$case" > cat"$counter".txt
./s21_cat test.txt "$case" > cat"$counter"_s21.txt
echo "--- Testing ./s21_cat test.txt $case"
# valgrind --tool=memcheck --leak-check=yes ./s21_cat test.txt "$case"
DIFF=$(diff cat"$counter".txt cat"$counter"_s21.txt)
if [ "$DIFF" == "" ]; then
  echo "Test $counter: SUCCESS"
else
  echo "Test $counter: FAIL"
  echo "---DIFF OUTPUT---"
  diff cat"$counter".txt cat"$counter"_s21.txt
  echo "---END OF DIFF---"
fi
((counter++))


case="-t"
cat test.txt "$case" > cat"$counter".txt
./s21_cat test.txt "$case" > cat"$counter"_s21.txt
echo "--- Testing ./s21_cat test.txt $case"
# valgrind --tool=memcheck --leak-check=yes ./s21_cat test.txt "$case"
DIFF=$(diff cat"$counter".txt cat"$counter"_s21.txt)
if [ "$DIFF" == "" ]; then
  echo "Test $counter: SUCCESS"
else
  echo "Test $counter: FAIL"
  echo "---DIFF OUTPUT---"
  diff cat"$counter".txt cat"$counter"_s21.txt
  echo "---END OF DIFF---"
fi
((counter++))


case="-T"
cat test.txt "$case" > cat"$counter".txt
./s21_cat test.txt "$case" > cat"$counter"_s21.txt
echo "--- Testing ./s21_cat test.txt $case"
# valgrind --tool=memcheck --leak-check=yes ./s21_cat test.txt "$case"
DIFF=$(diff cat"$counter".txt cat"$counter"_s21.txt)
if [ "$DIFF" == "" ]; then
  echo "Test $counter: SUCCESS"
else
  echo "Test $counter: FAIL"
  echo "---DIFF OUTPUT---"
  diff cat"$counter".txt cat"$counter"_s21.txt
  echo "---END OF DIFF---"
fi
((counter++))


case="-v"
cat test.txt "$case" > cat"$counter".txt
./s21_cat test.txt "$case" > cat"$counter"_s21.txt
echo "--- Testing ./s21_cat test.txt $case"
# valgrind --tool=memcheck --leak-check=yes ./s21_cat test.txt "$case"
DIFF=$(diff cat"$counter".txt cat"$counter"_s21.txt)
if [ "$DIFF" == "" ]; then
  echo "Test $counter: SUCCESS"
else
  echo "Test $counter: FAIL"
  echo "---DIFF OUTPUT---"
  diff cat"$counter".txt cat"$counter"_s21.txt
  echo "---END OF DIFF---"
fi
((counter++))


# TESTS 3: With mixed flags
# case="-beEns"
# cat test.txt "$case" > cat"$counter".txt
# ./s21_cat test.txt "$case" > cat"$counter"_s21.txt

# DIFF=$(diff cat"$counter".txt cat"$counter"_s21.txt)
# if [ "$DIFF" == "" ]; then
#   echo "Test $counter: SUCCESS"
# else
#   echo "Test $counter: FAIL"
#   echo "---DIFF OUTPUT---"
#   diff cat"$counter".txt cat"$counter"_s21.txt
#   echo "---END OF DIFF---"
# fi
# ((counter++))

# TESTS 4: With multiple long options
# case="--number-nonblank --number --squeeze-blank"
# cat test.txt "$case" > cat"$counter".txt
# ./s21_cat test.txt "$case" > cat"$counter"_s21.txt

# DIFF=$(diff cat"$counter".txt cat"$counter"_s21.txt)
# if [ "$DIFF" == "" ]; then
#   echo "Test $counter: SUCCESS"
# else
#   echo "Test $counter: FAIL"
#   echo "---DIFF OUTPUT---"
#   diff cat"$counter".txt cat"$counter"_s21.txt
#   echo "---END OF DIFF---"
# fi
# ((counter++))

# TESTS 5: With all of multiple flags and long options
# case="-b -e -E -n -s -t -T -v --number-nonblank --number --squeeze-blank"
# cat test.txt "$case" > cat"$counter".txt
# ./s21_cat test.txt "$case" > cat"$counter"_s21.txt

# DIFF=$(diff cat"$counter".txt cat"$counter"_s21.txt)
# if [ "$DIFF" == "" ]; then
#   echo "Test $counter: SUCCESS"
# else
#   echo "Test $counter: FAIL"
#   echo "---DIFF OUTPUT---"
#   diff cat"$counter".txt cat"$counter"_s21.txt
#   echo "---END OF DIFF---"
# fi
# ((counter++))