ifndef SILENCE_LIBFT_INFO
$(info Compiling Libft 📖)
endif

MAKEFLAGS += --no-print-directory

CC = cc

CFLAGS = -Werror -Wextra -Wall

OBJ_DIR = obj/

LIB = ft_calloc.c ft_isascii.c ft_itoa.c ft_memset.c ft_putnbr_fd.c ft_putnbr.c ft_strchr.c ft_strjoin.c ft_strlen.c ft_strnstr.c ft_substr.c ft_atoi.c ft_isalnum.c ft_isdigit.c ft_memcpy.c ft_memcmp.c ft_memchr.c\
ft_putchar_fd.c ft_putstr_fd.c ft_putchar.c ft_putstr.c ft_strdup.c ft_strlcat.c ft_strmapi.c ft_strrchr.c ft_tolower.c ft_bzero.c ft_isalpha.c ft_isprint.c ft_memmove.c ft_putendl_fd.c ft_split.c\
ft_striteri.c ft_strlcpy.c ft_strncmp.c ft_strtrim.c ft_toupper.c ft_putchar.c ft_strsndup.c ft_printf.c ft_putchar_pf.c ft_putstr_pf.c ft_printadress.c ft_putnbr_pf.c ft_putnbr_upf.c ft_putnbrhexalow.c ft_putnbrhexaupp.c ft_strslen.c\
ft_strstr.c ft_split_str.c ft_strcmp.c

BONUS = ft_lstnew_bonus.c ft_lstadd_front_bonus.c ft_lstsize_bonus.c ft_lstlast_bonus.c ft_lstadd_back_bonus.c ft_lstdelone_bonus.c ft_lstclear_bonus.c ft_lstiter_bonus.c ft_lstmap_bonus.c 

NAME = libft.a

SRCS = ${LIB}

SRCSBNS = ${LIB} ${BONUS}

OBJS = $(addprefix $(OBJ_DIR), $(SRCS:.c=.o))

OBJSALL = $(addprefix $(OBJ_DIR), $(SRCSBNS:.c=.o))

$(NAME): $(OBJ_DIR) ${OBJS}
	@ar -rsc ${NAME} ${OBJS}

$(OBJ_DIR)%.o: %.c
	@${CC} ${CFLAGS} -c $< -o $@

$(OBJ_DIR):
	@mkdir -p $(OBJ_DIR)

all: ${NAME}

bonus: $(OBJ_DIR) ${OBJSALL}
	@ar -rsc ${NAME} ${OBJSALL}

clean:
	@rm -rf ${OBJ_DIR}

fclean: clean
	@rm -f ${NAME}

re: fclean all

.PHONY: all clean fclean re
