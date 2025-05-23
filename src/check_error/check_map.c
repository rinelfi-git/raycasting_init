/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: erijania <erijania@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/30 12:07:52 by tramanan          #+#    #+#             */
/*   Updated: 2025/05/23 21:17:50 by erijania         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "check_error.h"
#include "tools.h"
#include "cub3d.h"

int	checkchar(char *str, char c)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (c == str[i])
			return (0);
		i++;
	}
	return (1);
}

int	empty_line(char *line)
{
	int	i;

	i = 0;
	if (!line)
		return (0);
	while (!checkchar("\t\n ", line[i]))
		i++;
	if (line[i] != '\0')
		return (0);
	return (1);
}

int	check_line(char *line, int fd, t_data *data)
{
	int	i;
	int	j;

	j = 0;
	i = skipe(line, 0);
	if (ft_strncmp("NO", line + i, 2) && !data->north)
		j = tk_texture(line + i + 2, &data->north);
	else if (ft_strncmp("SO", line + i, 2) && !data->south)
		j = tk_texture(line + i + 2, &data->south);
	else if (ft_strncmp("WE", line + i, 2) && !data->west)
		j = tk_texture(line + i + 2, &data->west);
	else if (ft_strncmp("EA", line + i, 2) && !data->east)
		j = tk_texture(line + i + 2, &data->east);
	else if (ft_strncmp("F", line + i, 1) && data->f < 0)
		j = tk_color(line + i + 1, &data->f);
	else if (ft_strncmp("C", line + i, 1) && data->c < 0)
		j = tk_color(line + i + 1, &data->c);
	else if (info_ok(data) && !checkchar("01", *line))
		return (tk_map(line, fd, &data->map));
	else
		j = 1;
	free (line);
	return (j);
}

int	check_map(int fd, char *line)
{
	t_data	data;
	int		code;

	init_data(&data);
	while (line)
	{
		while (empty_line(line))
		{
			free(line);
			line = get_next_line(fd);
		}
		code = check_line(line, fd, &data);
		if (code)
		{
			printf("CODE IS %d\n", code);
			config_file_error(code);
			free_data(&data);
			return (1);
		}
		line = get_next_line(fd);
	}
	run(&data);
	free_data(&data);
	return (0);
}

int	valid_map(char *path)
{
	int		fd;
	char	*line;

	fd = open(path, O_RDONLY);
	if (fd < 0)
		return (0);
	line = get_next_line(fd);
	if (!line)
		return (0);
	else if (check_map(fd, line))
		return (0);
	return (1);
}
