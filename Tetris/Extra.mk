valgrind_quick: clean clangF quick_compile
	valgrind --tool=memcheck --leak-check=yes ./$(BUILD_DIR)quick_test

valgrind_test_quick: clean clangF test
	valgrind --tool=memcheck --leak-check=yes ./$(BUILD_DIR)$(TEST_DIR)$(OUTPUT_NAME)_test

quick: clean clangF quick_compile
	./$(BUILD_DIR)quick_test

quick_compile: create_dir
	@$(CC) $(CFLAGSNOERROR) $(SRC) $(MAIN_DIR)$(MAIN_NAME).c $(LIBS) -o $(BUILD_DIR)quick_test

fsanitize_quick: clean clangF create_dir
	@$(CC) $(CFLAGSNOERROR) $(SRC) $(MAIN_DIR)$(MAIN_NAME).c $(LIBS) $(FSANITIZE) -o $(BUILD_DIR)quick_test && $(BUILD_DIR)quick_test

cppcheck: clangF
ifeq ("$(USER)", "aistdio")
	-@snap run cppcheck $(CPPCHECKFLAGS) $(HEADERS) ./$(TETRIS_DIR) ./$(GUI_DIR) --suppress=checkersReport
else
	-@cppcheck $(CPPCHECKFLAGS) $(HEADERS) ./$(TETRIS_DIR) ./$(GUI_DIR) --suppress=missingIncludeSystem
endif

git: clean
	-git checkout -b develop
	-git switch develop
	-find . \( -name '*.c' -or -name '*.h' -or -name '*.mk' -or -name 'Makefile' -or -name '*.pdf' -or -name 'Doxyfile' \) -type f -exec git add {} +
	-find . -name 'documentation.tex' -type f -exec git add {} +
	git status

clangF:
	-@find . \( -name '*.c' -or -name '*.h' \) -type f -exec clang-format -i -style=file:../materials/linters/.clang-format {} +

.PHONY: s v q f cppcheck git clangF