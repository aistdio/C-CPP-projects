include *.mk

all: clean $(TARGET).a

$(TARGET).a: $(OBJ)
	ar rc $@ $<
	ranlib $@

$(BUILD_DIR)%.o: $(SRC) create_dirs
	$(CC) $(CFLAGS) -c $< -o $@ $(LIBS)

$(BUILD_DIR)$(TEST_DIR)%.o: $(SRC_TEST) create_dirs
	$(CC) $(CFLAGS) -c $< -o $@ $(LIBS)

test: clean $(OBJ_TEST)
	$(CC) $(COVERAGE) $(CFLAGS) -o $(BUILD_DIR)$(TEST_DIR)$(TARGET)_test $(SRC) $(OBJ_TEST) $(LIBS_TEST)
	./$(BUILD_DIR)$(TEST_DIR)$(TARGET)_test

gcov_report: test
	@lcov -t "test" -c -d $(BUILD_DIR)$(TEST_DIR) -o $(BUILD_DIR)$(TEST_DIR)coverage.info
	@lcov --remove $(BUILD_DIR)$(TEST_DIR)coverage.info '/usr/*' --output-file $(BUILD_DIR)$(TEST_DIR)coverage.info
	@genhtml $(BUILD_DIR)$(TEST_DIR)coverage.info -o $(BUILD_DIR)$(TEST_DIR)coverage_report
	-@open $(LCOV)

.PHONY: create_dirs
create_dirs:
	@mkdir -p $(BUILD_DIR)$(TEST_DIR)

.PHONY: valgrind_check
valgrind_check: clang_format test
	@$(VALGRIND) ./$(BUILD_DIR)$(TEST_DIR)$(TARGET)_test

.PHONY: fsanitize_check
fsanitize_check: clang_format clean $(OBJ_TEST)
	$(CC) $(COVERAGE) $(CFLAGSNOERROR) $(FSANITIZE) -o $(BUILD_DIR)$(TEST_DIR)$(TARGET)_test $(SRC) $(OBJ_TEST) $(LIBS_TEST)
	./$(BUILD_DIR)$(TEST_DIR)$(TARGET)_test

.PHONY: quick_compile
quick_compile: clang_format
	@$(CC) $(CFLAGSNOERROR) $(FSANITIZE) $(SRC) $(LIBS) && ./a.out

.PHONY: cppcheck
cppcheck: clang_format
	-@$(CPPCHECK) $(CPPCHECKFLAGS) . -I .

.PHONY: git
git:
	-git checkout -b develop
	-git switch develop
	-git add $(FILES_TO_FORMAT)
	-git add Makefile
	-git status

.PHONY: clang_format
clang_format:
	-cp $(CFDIR).clang-format .clang-format
	-$(CF) $(FILES_TO_FORMAT)

.PHONY: rebuild
rebuild: clean all

.PHONY: clean
clean:
	-@rm -rf $(BUILD_DIR)
	-@rm -f $(TARGET).a
	-@rm -f a.out