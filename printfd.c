/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   printfd.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kabasolo <kabasolo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/03 12:44:11 by kabasolo          #+#    #+#             */
/*   Updated: 2024/04/25 16:42:04 by kabasolo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

#define NUM "0123456789"
#define HEX1 "0123456789abcdef"
#define HEX2 "0123456789ABCDEF"

static int	ft_dec(long int nbr, char *base)
{
	if (nbr < 0)
		return (write_fd(-1, '-') + ft_dec(nbr * (-1), base));
	if (nbr > 9)
		return (ft_dec(nbr / 10, base) + write_fd(-1, base[nbr % 10]));
	return (write_fd(-1, base[nbr % 10]));
}

static int	ft_hex(unsigned long nbr, char *base)
{
	if (nbr > 15)
		return (ft_hex(nbr / 16, base) + write_fd(-1, base[nbr % 16]));
	return (write_fd(-1, base[nbr % 16]));
}

static int	ft_str(char *str)
{
	int	i;

	i = 0;
	if (!str)
		return (ft_str("(null)"));
	while (str[i])
		write_fd(-1, str[i++]);
	return (i);
}

static int	ft_conversor(char c, va_list va)
{
	if (c == 'c')
		return (write_fd(-1, (char){va_arg(va, int)}));
	if (c == 's')
		return (ft_str(va_arg(va, char *)));
	if (c == 'p')
		return (ft_str("0x") + ft_hex(va_arg(va, unsigned long), HEX1));
	if (c == 'd' || c == 'i')
		return (ft_dec(va_arg(va, int), NUM));
	if (c == 'u')
		return (ft_dec(va_arg(va, unsigned int), NUM));
	if (c == 'x')
		return (ft_hex(va_arg(va, unsigned int), HEX1));
	if (c == 'X')
		return (ft_hex(va_arg(va, unsigned int), HEX2));
	return (write_fd(-1, c));
}

int	printfd(int fd, char const *s, ...)
{
	int		n;
	va_list	va;

	n = 0;
	va_start(va, s);
    write_fd(fd, 0);
	while (*s)
	{
		if (*s == '%')
			n += ft_conversor(*++s, va);
		else
			n += write_fd(-1, *s);
		s += !(!*s);
	}
	va_end(va);
	return (n);
}
