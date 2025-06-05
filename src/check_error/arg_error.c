/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   arg_error.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: erijania <erijania@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/02 14:39:41 by tramanan          #+#    #+#             */
/*   Updated: 2025/06/05 15:27:32 by erijania         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "check_error.h"

void	arg_error(int ac, char **av)
{
	if (ac < 2)
		ft_putstr_fd("Error\nToo few argument🙅", 2);
	else if (ac > 2)
		ft_putstr_fd("Error\nToo many argument🙅", 2);
	else if (ac == 2)
	{
		ft_putstr_fd("Error\n", 2);
		ft_putstr_fd(av[1], 2);
		ft_putstr_fd(" is not an allowed file🤕\n", 2);
		ft_putstr_fd("   Enter an *.cub file please🙃\n", 2);
	}
	exit(EXIT_FAILURE);
}

int	valid_name(char *name)
{
	int	ext;
	int	i;

	i = 0;
	ext = count_len(name) - 4;
	if (ext < 1)
		return (0);
	while (name[i] && name[i] != '.')
		i++;
	if (!name[i])
		return (0);
	else if (name[ext - 1] == '/')
		return (0);
	else if (ft_memcmp(name + ext, ".cub") != 0)
		return (0);
	return (1);
}
