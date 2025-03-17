include Config.mk
include Extra.mk
include Libraries.mk
SHOW_OBJECT_FILES = FALSE
DEPENDENCIES := $(addprefix $(BUILD_DIR), backend.a frontend.a)

all: install

install: clean create_dir build_main clean_obj
	-@mkdir -p $(EXECUTABLE_DIR)
	-cp $(BUILD_DIR)$(OUTPUT_NAME) $(EXECUTABLE_DIR)$(OUTPUT_NAME)

build_main: $(DEPENDENCIES)
	$(CC) $(CFLAGS) $(MAIN_DIR)$(MAIN_NAME).c $^ $(LIBS) -o $(BUILD_DIR)$(OUTPUT_NAME)

uninstall:
	-rm -rf $(EXECUTABLE_DIR)

dvi:
	-@mkdir -p $(DVI_DIR)
	doxygen Doxyfile
	-open $(DVI_DIR)/html/index.html

dist: Doxyfile Makefile *.mk *.pdf
	tar -czf $(MAIN_NAME)-1.0.tar.gz main brick_game gui common Doxyfile Makefile *.mk *.pdf

test: clean $(TEST_OBJ)
	$(CC) $(CFLAGS) $(FLAG_COV) -o $(BUILD_DIR)$(TEST_DIR)/$(OUTPUT_NAME)_test $(TEST_OBJ) $(SRC_TO_TEST) $(LIBS)
	./$(BUILD_DIR)$(TEST_DIR)$(OUTPUT_NAME)_test

$(BUILD_DIR)$(TEST_DIR)%.o: $(TEST_DIR)%.c create_dir_tests
	$(CC) $(CFLAGS) -c $< -o $@

gcov_report: test
	@lcov -t "test" -c -d $(BUILD_DIR)$(TEST_DIR) -o $(BUILD_DIR)$(TEST_DIR)coverage.info
ifeq ("$(DISTRO)", "Darwin")
	@lcov --remove $(BUILD_DIR)$(TEST_DIR)coverage.info '/usr/*' --output-file $(BUILD_DIR)$(TEST_DIR)coverage.info
endif
	@genhtml $(BUILD_DIR)$(TEST_DIR)coverage.info -o $(BUILD_DIR)$(TEST_DIR)coverage_report
	-@open $(LCOV)

rebuild: clean all

create_dir:
	-@mkdir -p $(BUILD_DIR)

create_dir_tests:
	-@mkdir -p $(BUILD_DIR)$(TEST_DIR)

clean: FORCE
	-rm -rf $(BUILD_DIR)
	-rm -rf $(EXECUTABLE_DIR)
	-rm -rf $(DVI_DIR)
#	-rm -f tetris_save_data.txt
	-rm -f $(MAIN_NAME)-1.0.tar.gz
	-@find $(PROJECT_DIRS) $(MAIN_DIR) -name '$(BUILD_DIR:/=)' -type d -exec rm -rf {} +

clean_obj: FORCE
ifeq ("$(SHOW_OBJECT_FILES)", "FALSE")
	-@find $(PROJECT_DIRS) $(MAIN_DIR) -name '$(BUILD_DIR:/=)' -type d -exec rm -rf {} +
endif

FORCE:

.PHONY: $(DEPENDENCIES) all install build_main uninstall dvi dist test gcov_report rebuild create_dir create_dir_tests clean clean_obj