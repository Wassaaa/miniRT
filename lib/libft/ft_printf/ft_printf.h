/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jtu <jtu@student.hive.fi>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/16 13:46:21 by jtu               #+#    #+#             */
/*   Updated: 2024/03/05 12:59:55 by jtu              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_H
# define FT_PRINTF_H

# include <stdarg.h>
# include <unistd.h>
# include "../libft.h"

typedef struct s_printf
{
	va_list	args;
	int		len;
}	t_printf;

# define HEXALOW	"0123456789abcdef"
# define HEXAUPP	"0123456789ABCDEF"
# define DECIMAL	"0123456789"

int		ft_printf(const char *fmt, ...);
void	initialise_list(t_printf *print);
int		ft_putnbr_base(long nbr, char *base, char type);
int		ft_putchar(char c);
int		ft_putstr(char *s);
int		ft_numlen_base(long nbr, char *base, char type);
int		convert_spec(t_printf *print, const char *fmt);
int		print_char(t_printf *print);
int		print_str(t_printf *print);
int		print_num(t_printf *print, char *base, char type);
int		print_ads(t_printf *print);
int		ft_putnbr_base_ul(unsigned long nbr, char *base);
int		ft_numlen_base_ul(unsigned long nbr, char *base);

#endif
