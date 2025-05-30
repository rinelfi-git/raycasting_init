/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   arg_error.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: erijania <erijania@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/29 14:58:09 by tramanan          #+#    #+#             */
/*   Updated: 2025/05/31 18:37:39 by erijania         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "check_error.h"
#include "tools.h"
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

int	ft_memcmp(char *s1, char *s2)
{
	int			i;

	i = 0;
	while (s1[i])
	{
		if (s1[i] != s2[i])
			return (1);
		i++;
	}
	return (0);
}

void	arg_error(int ac, int code)
{
	char	*dictionnary[4];

	dictionnary[0] = "Command line should be: "
		"./cub3D [path/to/the/config].cub\n";
	dictionnary[1] = "Extension needed!\n Config file should be [config].cub\n";
	dictionnary[2] = "Config file should be [config].cub\n";
	dictionnary[3] = "Cannot open or missing config file🤕\n";
	ft_putstr_fd("Error\n", 2);
	if (ac < 2)
		ft_putstr_fd("Too few argument🙅\n", 2);
	else if (ac > 2)
		ft_putstr_fd("Too many argument🙅\n", 2);
	ft_putstr_fd(dictionnary[code], 2);
	exit(EXIT_FAILURE);
}

static char	*get_extension(char *path)
{
	int		point;
	int		flag;
	int		start;
	char	*ext;

	point = -1;
	flag = -1;
	start = 0;
	if (!path)
		return (0);
	while (path[++point])
	{
		if (path[point] == '/')
			start = point + 1;
		else if (path[point] == '.')
			flag = point;
	}
	if (flag == -1 || start == flag)
		return (0);
	ext = ft_strdup(path + flag + 1);
	return (ext);
}

int	invalid_config_file(char *name)
{
	char	*ext;
	int		fd;

	ext = get_extension(name);
	if (!ext)
		return (1);
	if (ft_memcmp(ext, "cub"))
	{
		free(ext);
		return (2);
	}
	free(ext);
	fd = open(name, O_RDONLY);
	if (fd < 0)
		return (3);
	close(fd);
	return (0);
}
