/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tramanan <tramanan@student.42antananarivo  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/03 00:15:42 by tramanan          #+#    #+#             */
/*   Updated: 2025/06/03 00:28:12 by tramanan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "check_error.h"

static void	invalid_map(char ***map, int size)
{
	free_tab((*map), size);
	*map = NULL;
}

static int	check_player(char ***map, int size, int len)
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
		return (4);
	return (0);
}

static int	check_column(char ***map, int size, int len)
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
				return (3);
			while (i < size && !checkchar("10NEWS", (*map)[i][j]))
				i++;
			if (i <= size && checkchar(" 1", (*map)[i - 1][j]))
				return (3);
			i++;
		}
		j++;
	}
	return (0);
}

static int	check_arrow(char ***map, int size, int len)
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
				return (3);
			while (!checkchar("10NEWS", (*map)[i][j]))
				j++;
			if (j <= len && checkchar(" 1", (*map)[i][j - 1]))
				return (3);
		}
		i++;
	}
	return (0);
}

void	check_map(char ***map, int size, int len)
{
	if (check_arrow(map, size, len)
		|| check_column(map, size, len)
		|| check_player(map, size, len))
		invalid_map(map, size);
}
