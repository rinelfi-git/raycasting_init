/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: erijania <erijania@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/26 14:52:28 by tramanan          #+#    #+#             */
/*   Updated: 2025/05/23 21:28:25 by erijania         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "tools.h"
#include "check_error.h"

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

int	info_ok(t_data *data)
{
	if (!data->north || !data->south || !data->east || !data->west
		|| data->f < 0 || data->c < 0)
		return (0);
	return (1);
}

int	map_error(char *line, t_map **lst)
{
	free_list(*lst);
	free(line);
	return (3);
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
