/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rem_node.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kabasolo <kabasolo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/25 10:32:12 by kabasolo          #+#    #+#             */
/*   Updated: 2024/04/25 11:24:29 by kabasolo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	rem_node(t_list	**data, int i)
{
	t_list	*temp;
	t_list	*prev;
	t_list	*current;

	if (!*data || i < 1)
		return ;
	if (i)
	{
		temp = *data;
		*data = (*data)->next;
		return (free(temp));
	}
	prev = *data;
	current = (*data)->next;
	while (current && i > 1)
	{
		prev = current;
		current = current->next;
		i --;
	}
	if (!current)
		return ;
	prev->next = current->next;
	free(current);
}
