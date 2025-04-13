ifneq ($(filter clean fclean, $(MAKECMDGOALS)),)
$(info Cleaning Minishell 🚮)
else
$(info Compiling Minishell 📟)
endif

NAME         = minishell
CC           = cc
CFLAGS       = -Wall -Wextra -Werror
RM           = rm -f
MAKEFLAGS   += --no-print-directory

# Directory paths
SRC_DIR      = src
OBJ_DIR      = obj
INC_DIR      = include
LIBFT_DIR    = $(INC_DIR)/libft

# Source files list
SRC_FILES    = \
	$(SRC_DIR)/minishell.c \
	$(SRC_DIR)/signal/signal.c \
	$(SRC_DIR)/exec/handler.c \
	$(SRC_DIR)/built-in/echo.c \
	$(SRC_DIR)/built-in/env.c \
	$(SRC_DIR)/built-in/exit.c \
	$(SRC_DIR)/built-in/export.c \
	$(SRC_DIR)/built-in/pwd.c \
	$(SRC_DIR)/built-in/unset.c \
	$(SRC_DIR)/parsing/input_parser.c \
	$(SRC_DIR)/parsing/ft_split_str_mini.c

# Automatically generate object file names corresponding to source files
OBJS         = $(patsubst $(SRC_DIR)/%.c, $(OBJ_DIR)/%.o, $(SRC_FILES))

# Include and library settings
INCLUDES     = -I$(INC_DIR)
LIBFT        = $(LIBFT_DIR)/libft.a
LIBFT_FLAGS  = -L$(LIBFT_DIR) -lft
READLINE_FLAGS = -lreadline

# Stamp file to ensure Libft is built only once
LIBFT_STAMP  = $(OBJ_DIR)/.libft_compiled

all: $(OBJ_DIR) $(NAME)

bonus: all

# Create object directories including subdirectories
$(OBJ_DIR):
	@mkdir -p $(OBJ_DIR)
	@mkdir -p $(OBJ_DIR)/signal
	@mkdir -p $(OBJ_DIR)/exec
	@mkdir -p $(OBJ_DIR)/built-in
	@mkdir -p $(OBJ_DIR)/parsing

# Build Libft only once; no SILENCE_LIBFT_INFO flag here so its info prints once
$(LIBFT_STAMP):
	@$(MAKE) --no-print-directory -C $(LIBFT_DIR)
	@echo "Libft Compiled Successfully ✅"
	@touch $(LIBFT_STAMP)

# Generic rule for compiling a source file into an object file
$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c
	@mkdir -p $(dir $@)
	@$(CC) $(CFLAGS) $(INCLUDES) -I$(LIBFT_DIR) -c $< -o $@

# Link object files to create the executable, ensuring Libft has been built first
$(NAME): $(LIBFT_STAMP) $(OBJS)
	@$(CC) $(OBJS) $(LIBFT_FLAGS) $(READLINE_FLAGS) -o $(NAME) && echo "Minishell Compiled Successfully ✅"

clean:
	@$(MAKE) --no-print-directory SILENCE_LIBFT_INFO=1 -C $(LIBFT_DIR) clean
	@$(RM) -r $(OBJ_DIR)

fclean: clean
	@$(MAKE) --no-print-directory SILENCE_LIBFT_INFO=1 -C $(LIBFT_DIR) fclean
	@$(RM) $(NAME)
	@$(RM) $(LIBFT_STAMP)

re: fclean all

.PHONY: all bonus clean fclean re