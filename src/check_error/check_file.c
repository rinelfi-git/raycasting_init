/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_file.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: erijania <erijania@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/02 15:42:44 by tramanan          #+#    #+#             */
/*   Updated: 2025/06/05 15:29:57 by erijania         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "check_error.h"

static void	invalid_file(int type)
{
	char	*error[7];

	error[0] = "Cannot open or missing config file🤕\n";
	error[1] = "File empty🤧 Information needed!\n";
	error[2] = "Texture configuration invalid\n";
	error[3] = "Color configuration invalid\n";
	error[4] = "Map configuration invalid\n";
	error[5] = "ID invalid🤕\n";
	error[6] = "One or some element configuration missed🤕\n";
	ft_putstr_fd ("Error\n", 2);
	ft_putstr_fd("Invalid file👀\n", 2);
	ft_putstr_fd(error[type], 2);
}

int	info_ok(t_data *data)
{
	if (data->north && data->south && data->weast && data->east
		&& data->f >= 0 && data->c >= 0)
		return (1);
	return (0);
}

int	check_line(char *line, int fd, t_data *data)
{
	int	i;
	int	j;

	j = 0;
	i = skipe(line, 0);
	if (is_id_valid("NO", line + i, 2) && !data->north)
		j = tk_texture(line + i + 2, &data->north);
	else if (is_id_valid("SO", line + i, 2) && !data->south)
		j = tk_texture(line + i + 2, &data->south);
	else if (is_id_valid("WE", line + i, 2) && !data->weast)
		j = tk_texture(line + i + 2, &data->weast);
	else if (is_id_valid("EA", line + i, 2) && !data->east)
		j = tk_texture(line + i + 2, &data->east);
	else if (is_id_valid("F", line + i, 1) && data->f < 0)
		j = tk_color(line + i + 1, &data->f);
	else if (is_id_valid("C", line + i, 1) && data->c < 0)
		j = tk_color(line + i + 1, &data->c);
	else if (line[i] && !checkchar("01", line[i]) && info_ok(data))
		return (tk_map(line, fd, &data->map));
	else
		j = 5;
	free (line);
	return (j);
}

int	check_file(int fd, char *line, t_data *data)
{
	int	type;

	type = 0;
	while (line)
	{
		if (empty_line(line))
			free(line);
		else
		{
			type = check_line(line, fd, data);
			if (type)
			{
				invalid_file(type);
				return (1);
			}
		}
		line = get_next_line(fd);
	}
	if (!info_ok(data) || !data->map)
	{
		invalid_file(6);
		return (1);
	}
	return (0);
}

int	valid_file(char *path, t_data *data)
{
	int		fd;
	int		value;
	char	*line;

	value = 1;
	fd = open(path, O_RDONLY);
	if (fd < 0)
	{
		invalid_file(0);
		return (0);
	}
	line = get_next_line(fd);
	if (!line)
	{
		invalid_file(1);
		value = 0;
	}
	else if (check_file(fd, line, data))
		value = 0;
	close(fd);
	return (value);
}
