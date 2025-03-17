LIB_NAME =
SRC := $(shell find . -type f -name '*.c')
OBJ := $(addprefix $(BUILD_DIR), $(SRC:.c=.o))
HEADERS := $(addprefix -I, $(shell find ./ ./../../$(COMMON_DIR:/=) -type f -name '*.h' -exec dirname {} \; | sort -u))

$(LIB_NAME): clean $(OBJ)
	ar crs $(LIB_NAME) $(OBJ)
	@ranlib $(LIB_NAME)

$(BUILD_DIR)%.o: %.c create_dir
	$(CC) $(SUBCFLAGS) $(HEADERS) $(LIBS) -c $< -o $@

create_dir:
	-@mkdir -p $(shell dirname $(OBJ))

clean:
	@rm -rf $(BUILD_DIR)