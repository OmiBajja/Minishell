GREEN_COLOR = \\033[32m
ITALIC = \\033[3m
BOLD = \\033[1m
RESET_COLOR = \\033[0m

BANNER = \
$(GREEN_COLOR)" \
\n\
\n\
███╗   ███╗██╗███╗   ██╗██╗███████╗██╗  ██╗███████╗██╗      ██╗      \n\
████╗ ████║██║████╗  ██║██║██╔════╝██║  ██║██╔════╝██║      ██║      \n\
██╔████╔██║██║██╔██╗ ██║██║███████╗███████║█████╗  ██║      ██║      \n\
██║╚██╔╝██║██║██║╚██╗██║██║╚════██║██╔══██║██╔══╝  ██║      ██║      \n\
██║ ╚═╝ ██║██║██║ ╚████║██║███████║██║  ██║███████╗███████╗ ███████╗\n\
╚═╝     ╚═╝╚═╝╚═╝  ╚═══╝╚═╝╚══════╝╚═╝  ╚═╝╚══════╝╚══════╝ ╚══════╝"$(RESET_COLOR)\
\\n\
		$(ITALIC)$(BOLD)"Our own little shell"$(RESET_COLOR)\\n\
\\n\

ifneq ($(filter clean fclean, $(MAKECMDGOALS)),)
$(info Cleaning Minishell 🚮)
endif

NAME         = minishell
CC           = cc
CFLAGS       = -Wall -Wextra -Werror -g3
RM           = rm -f
MAKEFLAGS   += --no-print-directory

SRC_DIR      = src
OBJ_DIR      = obj
INC_DIR      = include
LIBFT_DIR    = $(INC_DIR)/libft

MAIN_SRC     = minishell.c
EXEC_SRC	 = exec/error_handling.c exec/exec_cmd.c exec/ft_split.c exec/handler.c exec/pipex_helpers.c exec/process.c exec/string_utils.c exec/heredoc_helpers.c exec/setup_redir.c exec/pipex.c exec/cleanup.c exec/handler_helpers.c
LEXER_SRC    = lexing/lexing.c lexing/token_init.c lexing/quote_handler.c lexing/lexing_utils.c
PARSER_SRC   = parsing/parser.c parsing/parsing_init.c parsing/parsing_utils.c parsing/parsing_redirs.c
SIGNAL_SRC   = signal/signal.c
UTILS_SRC    = utils/ft_strndup.c utils/ft_is_whitespace.c utils/ft_extender.c utils/ft_dequoter.c utils/ft_strsjoin.c utils/ft_strscomp.c utils/ft_shllvl.c utils/mini_cleaner.c utils/export_helpers.c utils/export_utils.c
BUILTIN_SRC	 = built-in/cd.c built-in/echo.c built-in/env.c built-in/exit.c built-in/export.c built-in/pwd.c built-in/unset.c

SRC_FILES    = $(addprefix $(SRC_DIR)/, \
			   $(MAIN_SRC) \
			   $(EXEC_SRC) \
			   $(LEXER_SRC) \
			   $(PARSER_SRC) \
			   $(SIGNAL_SRC) \
			   $(UTILS_SRC) \
			   $(BUILTIN_SRC))

OBJS         = $(patsubst $(SRC_DIR)/%.c, $(OBJ_DIR)/%.o, $(SRC_FILES))

INCLUDES     = -I$(INC_DIR)
LIBFT        = $(LIBFT_DIR)/libft.a
LIBFT_FLAGS  = -L$(LIBFT_DIR) -lft
READLINE_FLAGS = -lreadline

LIBFT_STAMP  = $(OBJ_DIR)/.libft_compiled

all: banner_print $(OBJ_DIR) $(NAME) 
	@echo "Compiling Minishell 📟"

banner_print:
	@echo $(BANNER)

$(OBJ_DIR):
	@mkdir -p $(OBJ_DIR)
	@mkdir -p $(OBJ_DIR)/exec
	@mkdir -p $(OBJ_DIR)/lexing
	@mkdir -p $(OBJ_DIR)/parsing
	@mkdir -p $(OBJ_DIR)/signal
	@mkdir -p $(OBJ_DIR)/utils
	@mkdir -p $(OBJ_DIR)/built-in

$(LIBFT_STAMP):
	@$(MAKE) --no-print-directory -C $(LIBFT_DIR)
	@echo "Libft Compiled Successfully ✅"
	@touch $(LIBFT_STAMP)

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c
	@mkdir -p $(dir $@)
	@$(CC) $(CFLAGS) $(INCLUDES) -I$(LIBFT_DIR) -c $< -o $@

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

.PHONY: all clean fclean re