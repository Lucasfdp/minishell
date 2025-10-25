NAME = minishell
CC = cc
READLINE_PATH = /opt/homebrew/opt/readline

SRC_DIR = src
LIBFT_DIR = $(SRC_DIR)/libft
LIBFT = $(LIBFT_DIR)/libft.a
#-g3 -fsanitize=address 
CFLAGS = -Wall -Wextra -Werror \
	-I$(READLINE_PATH)/include \
	-I$(SRC_DIR) \
	-I$(LIBFT_DIR)

LDFLAGS = -L$(READLINE_PATH)/lib -lreadline

BUILTINS_DIR = $(SRC_DIR)/builtins
PARSING_DIR = $(SRC_DIR)/parsing
EXECUTOR_DIR = $(SRC_DIR)/executor
SRCS = main.c \
	$(SRC_DIR)/main_utils.c \
	$(SRC_DIR)/readline.c \
	$(SRC_DIR)/freeing.c \
	$(SRC_DIR)/signals.c \
	$(SRC_DIR)/signals2.c \
	$(BUILTINS_DIR)/builtins.c \
	$(BUILTINS_DIR)/echo.c \
	$(BUILTINS_DIR)/pwd.c \
	$(BUILTINS_DIR)/env.c \
	$(BUILTINS_DIR)/export.c \
	$(BUILTINS_DIR)/unset.c \
	$(BUILTINS_DIR)/cd.c \
	$(BUILTINS_DIR)/exit.c \
	$(PARSING_DIR)/parsing.c \
	$(PARSING_DIR)/parsing_more.c \
	$(PARSING_DIR)/prep_hd.c \
	$(PARSING_DIR)/parsing_extras.c \
	$(PARSING_DIR)/parsing_utils.c \
	$(PARSING_DIR)/struct_fillers.c \
	$(PARSING_DIR)/tokeniser.c \
	$(PARSING_DIR)/tokeniser2.c \
	$(PARSING_DIR)/count_tokens.c \
	$(PARSING_DIR)/expand_vars.c \
	$(PARSING_DIR)/expand_vars_utils.c \
	$(PARSING_DIR)/expander.c \
	$(PARSING_DIR)/validate_tokens.c \
	$(EXECUTOR_DIR)/executor.c \
	$(EXECUTOR_DIR)/exec2.c \
	$(EXECUTOR_DIR)/exec_commands.c \
	$(EXECUTOR_DIR)/exec3.c \
	$(EXECUTOR_DIR)/apply_redirs.c




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
