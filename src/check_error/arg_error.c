/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   arg_error.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: erijania <erijania@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/29 14:58:09 by tramanan          #+#    #+#             */
/*   Updated: 2025/05/13 21:45:36 by erijania         ###   ########.fr       */
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

void	arg_error(int ac, char **av)
{
	if (ac < 2)
		ft_putstr_fd("too few argument🙅", 2);
	else if (ac > 2)
		ft_putstr_fd("too many argument🙅", 2);
	else if (ac == 2)
	{
		ft_putstr_fd(av[1], 2);
		ft_putstr_fd(" is not an allowed file🤕\n", 2);
		ft_putstr_fd("   Enter an *.cub file please🙃\n", 2);
	}
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
