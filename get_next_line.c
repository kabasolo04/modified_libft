/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kabasolo <kabasolo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/11 19:35:45 by kabasolo          #+#    #+#             */
/*   Updated: 2024/04/24 12:42:39 by kabasolo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*get_next_line(int fd)
{
	char	*buff;
	char	*line;
	int		i;
	int		ret;

	buff = (char *)malloc(128);
	if (!buff || fd < 0)
		return (NULL);
	i = 0;
	ret = read(fd, &buff[i], 1);
	while (ret > 0 && buff[i] != '\n')
	{
		i ++;
		if (i % 128 == 0)
			buff = (char *)ft_realloc(buff, i + 128);
		ret = read(fd, &buff[i], 1);
	}
	if (ret < 0)
		return (free(buff), NULL);
	buff[i++] = '\n';
	buff[i] = '\0';
	line = buff;
	return (free(buff), line);
}
