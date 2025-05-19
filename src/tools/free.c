/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: erijania <erijania@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/30 11:03:37 by tramanan          #+#    #+#             */
/*   Updated: 2025/05/19 21:32:40 by erijania         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "tools.h"

void	free_tab(char	**tab, int i)
{
	if (!tab)
		return ;
	while (i >= 0)
	{
		free (tab[i]);
		i--;
	}
	free (tab);
}

void	free_list(t_map *lst)
{
	t_map	*tmp;

	while (lst)
	{
		tmp = lst->next;
		free(lst->line);
		free(lst);
		lst = tmp;
	}
}

void	free_data(t_data *data)
{
	if (data->north)
		free(data->north);
	if (data->south)
		free(data->south);
	if (data->west)
		free(data->west);
	if (data->east)
		free(data->east);
	if (data->map)
		free_tab(data->map, ft_tabsize(data->map));
}
