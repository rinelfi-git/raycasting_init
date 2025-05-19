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

void	check_player(char ***map, int size, int len)
{
	int	i;
	int	j;
	int	p;

	i = 0;
	p = 0;
	while (i < size)
	{
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
		open_wall(map, size);
}

void	check_column(char ***map, int size, int len)
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
				return (open_wall(map, size));
			while (i < size && !checkchar("10NEWS", (*map)[i][j]))
				i++;
			if (i <= size && checkchar(" 1", (*map)[i - 1][j]))
				return (open_wall(map, size));
			i++;
		}
		j++;
	}
}

void	check_arrow(char ***map, int size, int len)
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
				return (open_wall(map, size));
			while (!checkchar("10NEWS", (*map)[i][j]))
				j++;
			if (j <= len && checkchar(" 1", (*map)[i][j - 1]))
				return (open_wall(map, size));
		}
		i++;
	}
}

void	check_lock(char ***map, int size, int len)
{
	check_arrow(map, size, len);
	check_column(map, size, len);
	check_player(map, size, len);
}
