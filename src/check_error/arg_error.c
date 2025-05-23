/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   arg_error.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: erijania <erijania@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/29 14:58:09 by tramanan          #+#    #+#             */
/*   Updated: 2025/05/23 19:52:02 by erijania         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "check_error.h"
#include "tools.h"

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

void	arg_error(void)
{
	ft_putstr_fd("Error\nCommand line should be: "
		"cub3D path/to/the/config.cub\n", 2);
	exit(EXIT_FAILURE);
}

int	valid_name(char *name)
{
	int	len;
	int	i;

	i = 0;
	len = ft_strlen(name) - 4;
	if (len < 1)
		return (0);
	while (name[i] && name[i] != '.')
		i++;
	if (name[i] == '.')
	{
		if (name[i - 1] == '/')
		{
			while (name[i++] != '.')
				if (name[i] == '\0')
					return (0);
		}
		while ((name[i] && name[i] != '.') && i <= len)
			i++;
		if (ft_memcmp(name + i, ".cub") != 0)
			return (0);
	}
	if (ft_memcmp(name + len, ".cub") != 0)
		return (0);
	return (1);
}
