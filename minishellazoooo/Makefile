NAME = minishell
CC = cc
READLINE_PATH = /opt/homebrew/opt/readline

SRC_DIR = src
LIBFT_DIR = $(SRC_DIR)/libft
LIBFT = $(LIBFT_DIR)/libft.a

#-g -fsanitize=address
CFLAGS = -Wall -Wextra -Werror \
	-I$(READLINE_PATH)/include \
	-I$(SRC_DIR) \
	-I$(LIBFT_DIR)

LDFLAGS = -L$(READLINE_PATH)/lib -lreadline

BUILTINS_DIR = $(SRC_DIR)/builtins
PARSING_DIR = $(SRC_DIR)/parsing
EXECUTOR_DIR = $(SRC_DIR)/executor
SRCS = main.c \
	$(SRC_DIR)/readline.c \
	$(SRC_DIR)/freeing.c \
	$(BUILTINS_DIR)/builtins.c \
	$(BUILTINS_DIR)/echo.c \
	$(BUILTINS_DIR)/pwd.c \
	$(BUILTINS_DIR)/env.c \
	$(BUILTINS_DIR)/export.c \
	$(BUILTINS_DIR)/unset.c \
	$(BUILTINS_DIR)/cd.c \
	$(BUILTINS_DIR)/exit.c \
	$(PARSING_DIR)/parsing.c \
	$(PARSING_DIR)/tokeniser.c \
	$(EXECUTOR_DIR)/executor.c \
	$(EXECUTOR_DIR)/exec2.c \
	$(EXECUTOR_DIR)/exec3.c



OBJS = $(SRCS:.c=.o)

GREEN    = \033[0;32m
RESET    = \033[0m

all: $(LIBFT) $(NAME)

$(NAME): $(OBJS)
	$(CC) $(CFLAGS) -o $(NAME) $(OBJS) $(LIBFT) $(LDFLAGS)
	@echo "$(GREEN)Build complete: $(NAME)$(RESET)"

$(LIBFT):
	$(MAKE) -C $(LIBFT_DIR)
	@echo "$(GREEN)Libft Build Complete$(RESET)"

%.o: %.c ./minishell.h
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	$(MAKE) -C $(LIBFT_DIR) clean
	rm -f $(OBJS)

fclean: clean
	$(MAKE) -C $(LIBFT_DIR) fclean
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re libft
