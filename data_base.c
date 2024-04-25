/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   data_base.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kabasolo <kabasolo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/24 11:33:57 by kabasolo          #+#    #+#             */
/*   Updated: 2024/04/25 12:17:32 by kabasolo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

typedef struct data_list
{
	va_list			va;
	char			*name;
	char			*var;
	int				i;
}	data_list;

static int	find_by_name(t_list *data, char *name)
{
	int		i;
	t_list	*node;

	i = 1;
	node = data;
	while (node)
	{
		if (!ft_strncmp(node->name, name, 128))
			return (i);
		node = node->next;
		i ++;
	}
	return (0);
}

static void	**make_res(void *cont1, void *cont2)
{
	void	**res;
	void	**temp;

	temp = (void **)malloc(2 * sizeof(void *));
	temp[0] = cont1;
	temp[1] = cont2;
	res = temp;
	free(temp);
	return (res);
}

static int	new_node(t_list	**data, char *name, void *var)
{
	t_list	*node;

	node = (t_list *)malloc(sizeof(t_list));
	if (!node)
		return (0);
	node->name = name;
	node->content = var;
	ft_lstadd_back(data, node);
	return (1);
}

static void	**read_or_edit(t_list	**data, data_list *d, int mode)
{
	t_list			*temp;

	if (d->i == 0)
	{
		if (mode == READ || (int)d->name < 2048)
			return (make_res(NULL, (void *)0));
		if (mode == EDIT && new_node(data, d->name, d->var))
			return (make_res((*data)->content, (void *)1));
	}
	temp = *data;
	while (d->i-- > 1 && temp && temp->next)
		temp = temp->next;
	if (d->i > 0)
		return (make_res(NULL, (void *)0));
	if (mode == EDIT)
		temp->content = d->var;
	return (make_res(temp->content, (void *)1));
}

void	**data_base(int mode, ...) //char *name, void *var
{
	static t_list	*data_base;
	data_list		d;

	if (mode == FREE)
		return (free_list(&data_base), make_res(NULL, (void *)1));
	if (mode == MEM)
		return (make_res(&data_base, (void *)1));
	va_start(d.va, mode);
	d.name = va_arg(d.va, void *);
	d.var = va_arg(d.va, void *);
	va_end(d.va);
	if (!d.name)
		return (make_res(NULL, (void *)0));
	d.i = (int)d.name;
	if ((int)d.name > 2048)
		d.i = find_by_name(data_base, d.name);
	if (mode == REM)
	{
		rem_node(&data_base, d.i);
		return (make_res(NULL, (void *)1));
	}
	if (mode == READ || mode == EDIT)
		return (read_or_edit(&data_base, &d, mode));
	return (make_res(NULL, (void *)0));
}
