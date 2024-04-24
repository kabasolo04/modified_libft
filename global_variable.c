/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   global_variable.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kabasolo <kabasolo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/24 11:33:57 by kabasolo          #+#    #+#             */
/*   Updated: 2024/04/24 11:47:52 by kabasolo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*global_variable(void *var)
{
	static void	*g_var;

	if (var)
		g_var = var;
	if (!g_var)
		g_var = NULL;
	return (g_var);
}
