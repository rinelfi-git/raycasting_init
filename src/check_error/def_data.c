/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   def_data.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: erijania <erijania@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/02 17:20:11 by tramanan          #+#    #+#             */
/*   Updated: 2025/06/05 15:28:36 by erijania         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "check_error.h"

static char	**lst_to_tab(t_map *lst)
{
	int		size;
	int		len;
	char	**map;
	t_map	*tmp;

	tmp = lst;
	len = set_len(lst);
	size = ft_lstsize(lst);
	if (size < 3)
	{
		free_list(tmp);
		return (NULL);
	}
	map = (char **)malloc(sizeof(char *) * (size + 1));
	size = 0;
	while (lst)
	{
		map[size] = ft_strcpy(lst->line, len);
		size++;
		lst = lst->next;
	}
	map[size] = NULL;
	free_list(tmp);
	check_map(&map, size, count_len(map[0]));
	return (map);
}

int	tk_texture(char *texture, char **buffer)
{
	int		i;
	int		j;

	i = skipe(texture, 0);
	j = 0;
	while (texture[i + j] && checkchar("\t \n", texture[i + j]))
		j++;
	if (j > 2 && is_id_valid("./", texture + i, 2))
		*buffer = (char *)malloc(sizeof(char) * (j + 1));
	if (!(*buffer))
		return (2);
	(*buffer)[j] = '\0';
	while (--j >= 0)
		(*buffer)[j] = texture[i + j];
	return (0);
}

int	tab_ok(char **res, int len)
{
	int	value;

	value = 1;
	if (!res[0] || !res[1] || !res[2])
		value = 0;
	else if (!is_nb_valid(res, len))
		value = 0;
	if (!value)
		free_tab(res, len);
	return (value);
}

int	tk_color(char *line, int *color)
{
	int		start;
	int		red;
	int		green;
	int		blue;
	char	**res;

	start = skipe(line, 0);
	if (count_words(line + start, ',') != 3)
		return (3);
	res = ft_split(line + start, ',');
	if (!tab_ok(res, 3))
		return (3);
	red = ft_atoi(res[0]);
	green = ft_atoi(res[1]);
	blue = ft_atoi(res[2]);
	if (red < 0 || green < 0 || blue < 0)
	{
		free_tab(res, 3);
		return (3);
	}
	*color = red << 16 | green << 8 | blue;
	free_tab(res, 3);
	return (0);
}

int	tk_map(char *line, int fd, char ***map)
{
	int		i;
	t_map	*lst;
	t_map	*new;

	lst = NULL;
	while (line)
	{
		i = 0;
		while (line[i])
		{
			if (checkchar("10 NEWS\n", line[i]) || empty_line(line))
				return (map_error(line, &lst));
			i++;
		}
		new = new_line(line);
		if (!new)
			return (map_error(line, &lst));
		ft_addback(&lst, new);
		free(line);
		line = get_next_line(fd);
	}
	*map = lst_to_tab(lst);
	if (!(*map))
		return (4);
	return (0);
}
