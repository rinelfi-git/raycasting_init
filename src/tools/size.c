/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   size.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: erijania <erijania@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/31 11:18:15 by tramanan          #+#    #+#             */
/*   Updated: 2025/05/19 21:40:48 by erijania         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "tools.h"

int	ft_tabsize(char **src)
{
	int	i;

	if (!src)
		return (0);
	i = 0;
	while (src[i])
		i++;
	return (i);
}

int	count_len(char *str)
{
	int	i;

	i = 0;
	if (!str)
		return (i);
	while (str[i])
		i++;
	return (i);
}

int	set_len(t_map *lst)
{
	int		i;
	int		len;
	t_map	*tmp;

	i = 0;
	len = 0;
	tmp = lst;
	while (tmp)
	{
		len = count_len(tmp->line);
		if (len > i)
			i = len;
		tmp = tmp->next;
	}
	return (i);
}

int	ft_lstsize(t_map *line)
{
	int	i;

	i = 0;
	while (line)
	{
		i++;
		line = line->next;
	}
	return (i);
}
