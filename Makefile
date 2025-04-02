NAME        = minishell
CC          = cc
CFLAGS      = -Wall -Wextra -Werror
RM          = rm -f

# Directory paths - remove trailing slashes
SRC_DIR     = src
OBJ_DIR     = obj
INC_DIR     = include

# Source files with explicit paths
SRC_FILES   = $(SRC_DIR)/minishell.c \
              $(SRC_DIR)/signal/signal.c \
              $(SRC_DIR)/exec/handler.c

# Object files with proper directory structure
OBJ_FILES   = $(OBJ_DIR)/minishell.o \
              $(OBJ_DIR)/signal/signal.o \
              $(OBJ_DIR)/exec/handler.o

# Include paths
INCLUDES    = -I$(INC_DIR)

# Libft settings
LIBFT_DIR   = $(INC_DIR)/libft
LIBFT       = $(LIBFT_DIR)/libft.a
LIBFT_FLAGS = -L$(LIBFT_DIR) -lft

# Readline library flags
READLINE_FLAGS = -lreadline

all: $(OBJ_DIR) $(NAME)

bonus: all

# Create object directories
$(OBJ_DIR):
	@mkdir -p $(OBJ_DIR)
	@mkdir -p $(OBJ_DIR)/signal
	@mkdir -p $(OBJ_DIR)/exec
	@mkdir -p $(OBJ_DIR)/parsing

$(LIBFT):
	@$(MAKE) -C $(LIBFT_DIR)

libft_bonus:
	@$(MAKE) -C $(LIBFT_DIR) bonus

# Compile source files
$(OBJ_DIR)/minishell.o: $(SRC_DIR)/minishell.c
	@mkdir -p $(dir $@)
	$(CC) $(CFLAGS) $(INCLUDES) -I$(LIBFT_DIR) -c $< -o $@

$(OBJ_DIR)/signal/signal.o: $(SRC_DIR)/signal/signal.c
	@mkdir -p $(dir $@)
	$(CC) $(CFLAGS) $(INCLUDES) -I$(LIBFT_DIR) -c $< -o $@

$(OBJ_DIR)/exec/handler.o: $(SRC_DIR)/exec/handler.c
	@mkdir -p $(dir $@)
	$(CC) $(CFLAGS) $(INCLUDES) -I$(LIBFT_DIR) -c $< -o $@

# Link object files to create executable
$(NAME): libft_bonus $(OBJ_FILES)
	$(CC) $(OBJ_FILES) $(LIBFT_FLAGS) $(READLINE_FLAGS) -o $(NAME)

clean:
	$(MAKE) -C $(LIBFT_DIR) clean
	$(RM) -r $(OBJ_DIR)

fclean: clean
	$(MAKE) -C $(LIBFT_DIR) fclean
	$(RM) $(NAME)

re: fclean all

.PHONY: all clean fclean re bonus libft_bonus