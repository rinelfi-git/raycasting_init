/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_lock.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: erijania <erijania@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/03 13:56:19 by tramanan          #+#    #+#             */
/*   Updated: 2025/05/13 21:48:27 by erijania         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "check_error.h"
#include "tools.h"

static void	open_wall(char ***map, int size)
{
	free_tab((*map), size);
	*map = NULL;
}

int	check_player(char ***map, int size, int len)
{
	int	i;
	int	j;
	int	p;

	i = 0;
	p = 0;
	while (i < size)
	{
		ft_putstr_fd((*map)[i], 1);
		ft_putstr_fd("\n", 1);
		j = 0;
		while (j < len)
		{
			if (!checkchar("NEWS", (*map)[i][j]))
				p++;
			j++;
		}
		i++;
	}
	if (p != 1)
		return (1);
	return (0);
}

int	check_column(char ***map, int size, int len)
{
	int	i;
	int	j;

	j = 0;
	while (j < len)
	{
		i = 0;
		while (i < size)
		{
			while (i < size && (*map)[i][j] == ' ')
				i++;
			if ((i < size && (*map)[i][j] != '1'))
				return (1);
			while (i < size && !checkchar("10NEWS", (*map)[i][j]))
				i++;
			if (i <= size && checkchar(" 1", (*map)[i - 1][j]))
				return (1);
			i++;
		}
		j++;
	}
	return (0);
}

int	check_arrow(char ***map, int size, int len)
{
	int	i;
	int	j;

	i = 0;
	while (i < size)
	{
		j = 0;
		while (j < len)
		{
			while (j < len && (*map)[i][j] == ' ')
				j++;
			if ((*map)[i][j] && (*map)[i][j] != '1')
				return (1);
			while (!checkchar("10NEWS", (*map)[i][j]))
				j++;
			if (j <= len && checkchar(" 1", (*map)[i][j - 1]))
				return (1);
		}
		i++;
	}
	return (0);
}

void	check_lock(char ***map, int size, int len)
{
	if (check_arrow(map, size, len)
		|| check_column(map, size, len)
		|| check_player(map, size, len))
		open_wall(map, size);
}
