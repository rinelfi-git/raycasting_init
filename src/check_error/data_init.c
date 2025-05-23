/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   data_init.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: erijania <erijania@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/24 15:34:39 by tramanan          #+#    #+#             */
/*   Updated: 2025/05/23 21:28:02 by erijania         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "check_error.h"
#include "tools.h"

void	init_data(t_data *data)
{
	data->north = NULL;
	data->south = NULL;
	data->west = NULL;
	data->east = NULL;
	data->f = -1;
	data->c = -1;
	data->map = NULL;
}

char	**lst_to_tab(t_map *lst)
{
	int		size;
	int		len;
	char	**map;
	t_map	*tmp;

	tmp = lst;
	len = set_len(lst);
	size = ft_lstsize(lst);
	if (size < 3)
		return (NULL);
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
	check_lock(&map, size, count_len(map[0]));
	return (map);
}

int	tk_color(char *line, int *color)
{
	int		red;
	int		green;
	int		blue;
	char	**res;

	if (*line != ' ' || count_words(line, ',') != 3)
		return (2);
	res = ft_split(line, ',');
	red = ft_atoi(res[0]);
	green = ft_atoi(res[1]);
	blue = ft_atoi(res[2]);
	if (red < 0 || green < 0 || blue < 0)
	{
		free_tab(res, 3);
		return (2);
	}
	*color = red << 16 | green << 8 | blue;
	free_tab(res, 3);
	return (0);
}

int	tk_texture(char *texture, char **buffer)
{
	int		i;
	int		j;

	if (*texture != ' ')
	{
		printf("TEXTURE VALUE ID [%s]\n", texture);
		return (1);
	}
	i = skipe(texture, 0);
	j = 0;
	while (checkchar("\t \n", texture[i + j]))
		j++;
	if (j > 0 && ft_strncmp("./", texture + i, 2))
		*buffer = (char *)malloc(sizeof(char) * (j + 1));
	if (!(*buffer))
		return (1);
	(*buffer)[j] = '\0';
	while (--j >= 0)
		(*buffer)[j] = texture[i + j];
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
			if (checkchar("10 NEWS\n", line[i]) || *line == '\n')
				return (map_error(line, &lst));
			i++;
		}
		new = new_line(line);
		if (!new)
			return (3);
		ft_addback(&lst, new);
		free(line);
		line = get_next_line(fd);
	}
	*map = lst_to_tab(lst);
	return (!(*map));
}
