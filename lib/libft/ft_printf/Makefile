NAME = libftprintf.a

SRCS = ft_printf.c \
		ft_put_function.c \
		ft_specifier.c \
		ft_numlen.c

CFLAGS = -Wall -Wextra -Werror

BONUS_OBJS = ${BONUS_SRCS:.c=.o}

OBJS = ${SRCS:.c=.o}

LIBFT_NAME = libft.a

all: ${NAME}

%.o: %.c
	cc $(CFLAGS) -c $< -o $@

${NAME}: ${OBJS}
	make -C libft/ bonus
	cp libft/libft.a libftprintf.a
	ar -rcs $(NAME) $(OBJS)

clean:
	rm -f ${OBJS}
	make clean -C libft

fclean: clean
	rm -f ${NAME}
	make fclean -C libft

re: fclean all

.PHONY: all clean fclean re
