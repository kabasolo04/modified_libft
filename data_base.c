/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   data_base.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kabasolo <kabasolo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/24 11:33:57 by kabasolo          #+#    #+#             */
/*   Updated: 2024/04/24 19:47:39 by kabasolo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	find_by_name(t_list *data, char *name)
{
	int		i;
	t_list	*node;

	i = 1;
	node = data;
	while(node)
	{
		if (!ft_strncmp(node->name, name, 128))
			return (i);
		node = node->next;
		i ++;
	}
	return (0);
}

static void	**make_res(void *cont1, int cont2)
{
	void	**res;
	void	**temp;
	
	temp = (void **)malloc(2 * sizeof(void *));
	temp[0] = cont1;
	temp[1] = &cont2;
	res = temp;
	free(temp);
	return(res);
}

static int	new_var(t_list	**data, char *name, void *var)
{
	t_list	*node;
	
	node = (t_list *)malloc(sizeof(t_list));
	if (!node)
		return (0);
	node->name = name;
	node->content = var;
	ft_lstadd_front(data, node);
	return (1);
}

static void	rem_node(t_list	**data, int i)
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

void	**data_base(char *name, void *var, int b)
{
	static t_list	*data;
	t_list			*temp;
	int				i;

	if (b == 3)
		return (free_list(&data), make_res(NULL, 1));
	if (b == 4)
		return (make_res(&data, 1));
	if (!name)
		return(make_res(NULL, 0));
	i = find_by_name(data, name);
	if (b == 2)
		return (rem_node(&data, i), make_res(NULL, 1));
	if (!i)
	{
		if (!(b && new_var(&data, name, var)))
			return (make_res(NULL, 0));
		return (make_res(data->content, 1));
	}
	temp = data;
	while (i-- > 1 && temp && temp->next)
		temp = temp->next;
	if (b)
		temp->content = var;
	return (make_res(temp->content, 1));
}
