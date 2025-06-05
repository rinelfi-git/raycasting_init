/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: erijania <erijania@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/26 14:52:28 by tramanan          #+#    #+#             */
/*   Updated: 2025/06/05 14:59:20 by erijania         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "tools.h"

void	ft_addback(t_map **map, t_map *line)
{
	t_map	*newmap;

	if (!*map)
		*map = line;
	else
	{
		newmap = *map;
		while (newmap->next)
			newmap = newmap->next;
		newmap->next = line;
	}
}

int	map_error(char *line, t_map **lst)
{
	free_list(*lst);
	free(line);
	return (4);
}

int	is_nb_valid(char **res, int len)
{
	int	i;
	int	j;

	i = 0;
	while (i < len)
	{
		j = 0;
		if (!empty_line(res[i]))
		{
			while (res[i][j])
			{
				if (!ft_isdigit(res[i][j]) && res[i][j] != '\n')
					return (0);
				j++;
			}
		}
		else
			return (0);
		i++;
	}
	return (1);
}

char	*ft_strcpy(char *s, int l_src)
{
	char	*dest;
	int		i;

	i = 0;
	dest = (char *)malloc (sizeof(char) * (l_src + 1));
	if (!dest)
		return (NULL);
	while (s[i] != '\0' && s[i] != '\n')
	{
		dest[i] = s[i];
		i++;
	}
	while (l_src > i)
	{
		dest[i] = ' ';
		i++;
	}
	dest[l_src] = '\0';
	return (dest);
}

t_map	*new_line(char *line)
{
	static int	count = 0;
	int			i;
	t_map		*new;

	count++;
	i = 0;
	if (count == 1)
	{
		while (line[i])
		{
			if (checkchar(" 1\n", line[i]))
				return (NULL);
			i++;
		}
	}
	new = (t_map *)malloc(sizeof(t_map));
	if (!new)
		return (NULL);
	new->line = cpy_word(line, '\n');
	new->count = count;
	new->next = NULL;
	return (new);
}
