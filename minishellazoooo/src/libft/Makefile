# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: lucas <lucas@student.42.fr>                +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/01/16 14:25:09 by luferna3          #+#    #+#              #
#    Updated: 2025/08/28 00:15:58 by lucas            ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CC = cc
CFLAGS = -Wall -Wextra -Werror
NAME = libft.a

SRCS = ft_strlen.c ft_isdigit.c ft_atoi.c ft_isascii.c ft_memchr.c ft_memset.c\
		ft_memcmp.c ft_memcpy.c ft_strncmp.c ft_isalnum.c ft_strlcat.c\
		ft_isalpha.c ft_memmove.c ft_strlcpy.c ft_strnstr.c ft_tolower.c\
		ft_toupper.c ft_strchr.c ft_strrchr.c ft_isprint.c ft_bzero.c\
		ft_strdup.c ft_calloc.c ft_substr.c ft_strjoin.c ft_strtrim.c\
		ft_split.c ft_itoa.c ft_strmapi.c ft_striteri.c ft_putchar_fd.c\
		ft_putstr_fd.c ft_putendl_fd.c ft_putnbr_fd.c ft_printf_utils.c\
		ft_printf.c get_next_line.c get_next_line_utils.c lib_main.c\
		freeing_stuff.c copy_matrix.c ft_isspace.c
		
/*SRCS_BONUS = ft_lstnew_bonus.c ft_lstadd_front_bonus.c ft_lstsize_bonus.c\
			ft_lstlast_bonus.c ft_lstadd_back_bonus.c ft_lstdelone_bonus.c\
			ft_lstclear_bonus.c ft_lstiter_bonus.c ft_lstmap_bonus.c*/
			
OBJ_FILES = $(SRCS:.c=.o)
OBJ_BONUS = $(SRCS_BONUS:.c=.o)
	
$(NAME): $(OBJ_FILES)
	ar -rc $(NAME) $(OBJ_FILES)

%.o: %.c libft.h
	$(CC) $(CFLAGS) -c $< -o $@

bonus: .bonus

.bonus: ${OBJ_FILES} ${OBJ_BONUS}
	ar -rc ${NAME} ${OBJ_FILES} ${OBJ_BONUS}
	touch .bonus
	
clean:
	rm -f $(OBJ_FILES) $(OBJ_BONUS) .bonus

fclean: clean
	rm -f $(NAME)

re: fclean $(NAME)

all: $(NAME)
.PHONY: all clean fclean re bonus