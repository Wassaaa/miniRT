# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: jtu <jtu@student.hive.fi>                  +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/04/05 11:18:34 by jtu               #+#    #+#              #
#    Updated: 2024/04/09 12:54:47 by jtu              ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

GREEN = \033[0;92m

NAME = libft.a

SRCS = ft_isalpha.c \
	ft_isdigit.c \
	ft_isalnum.c \
	ft_isascii.c \
	ft_isprint.c \
	ft_strlen.c \
	ft_memset.c \
	ft_bzero.c \
	ft_memcpy.c \
	ft_memmove.c \
	ft_strlcpy.c \
	ft_strlcat.c \
	ft_toupper.c \
	ft_tolower.c \
	ft_strchr.c \
	ft_strrchr.c \
	ft_strncmp.c \
	ft_memchr.c \
	ft_memcmp.c \
	ft_strnstr.c \
	ft_atoi.c \
	ft_calloc.c \
	ft_strdup.c \
	ft_substr.c \
	ft_strjoin.c \
	ft_strtrim.c \
	ft_split.c \
	ft_itoa.c \
	ft_strmapi.c \
	ft_striteri.c \
	ft_putchar_fd.c \
	ft_putstr_fd.c \
	ft_putendl_fd.c \
	ft_putnbr_fd.c \
	get_next_line/get_next_line_bonus.c \
	ft_printf/ft_printf.c \
	ft_printf/ft_put_function.c \
	ft_printf/ft_specifier.c \
	ft_printf/ft_numlen.c

CFLAGS = -Wall -Wextra -Werror -fsanitize=address -g -static-libsan

OBJS = ${SRCS:.c=.o}

all: ${NAME}

%.o: %.c
	@cc $(CFLAGS) -c $< -o $@

${NAME}: ${OBJS}
	@ar rcs $@ $^
	@echo "$(GREEN)Libft Compiled!$(DEF_COLOR)"

clean:
	@rm -f ${OBJS}

fclean: clean
	@rm -f ${NAME}

re: fclean all

.PHONY: all clean fclean re
