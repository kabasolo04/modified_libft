/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printfd.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kabasolo <kabasolo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/24 11:30:58 by kabasolo          #+#    #+#             */
/*   Updated: 2024/04/24 18:43:03 by kabasolo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

#define NUM "0123456789"
#define HEX1 "0123456789abcdef"
#define HEX2 "0123456789ABCDEF"

static int	ft_dec(long int nbr, char *base)
{
	int	fd;

	fd = (int)data_base("fd", NULL, 0)[0];
	if (nbr < 0)
		return (write(1, "-", 1) + ft_dec(nbr * (-1), base));
	if (nbr > 9)
		return (ft_dec(nbr / 10, base) + write(fd, &base[nbr % 10], 1));
	return (write(fd, &base[nbr % 10], 1));
}

static int	ft_hex(unsigned long nbr, char *base)
{
	int	fd;

	fd = (int)data_base("fd", NULL, 0)[0];
	if (nbr > 15)
		return (ft_hex(nbr / 16, base) + write(fd, &base[nbr % 16], 1));
	return (write(fd, &base[nbr % 16], 1));
}

static int	ft_str(char *str)
{
	int	i;
	int	fd;

	fd = (int)data_base("fd", NULL, 0)[0];
	i = 0;
	if (!str)
		return (ft_str("(null)"));
	while (str[i])
		write(fd, &str[i++], 1);
	return (i);
}

static int	ft_conversor(char c, va_list va)
{
	int	fd;

	fd = (int)data_base("fd", NULL, 0)[0];
	if (c == 'c')
		return (write(fd, &(char){va_arg(va, int)}, 1));
	if (c == 's')
		return (ft_str(va_arg(va, char *)));
	if (c == 'p')
		return (write(fd, "0x", 2) + ft_hex(va_arg(va, unsigned long), HEX1));
	if (c == 'd' || c == 'i')
		return (ft_dec(va_arg(va, int), NUM));
	if (c == 'u')
		return (ft_dec(va_arg(va, unsigned int), NUM));
	if (c == 'x')
		return (ft_hex(va_arg(va, unsigned int), HEX1));
	if (c == 'X')
		return (ft_hex(va_arg(va, unsigned int), HEX2));
	return (write(fd, &c, 1));
}

int	ft_printfd(int fd, char const *s, ...)
{
	int		n;
	va_list	va;

	if (!data_base("fd", &fd, 0)[1])
		return (data_base(NULL, 0, 3), -1);
	n = 0;
	va_start(va, s);
	while (*s)
	{
		if (*s == '%')
			n += ft_conversor(*++s, va);
		else
			n += write(fd, s, 1);
		s += !(!*s);
	}
	va_end(va);
	return (data_base(NULL, 0, 3), n);
}
