/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_check.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: erijania <erijania@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/13 21:31:21 by erijania          #+#    #+#             */
/*   Updated: 2025/06/05 15:30:08 by erijania         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "raycast.h"
#include "tools.h"

int	init_check(t_cub3d *cub)
{
	int	i;

	if (!cub->map)
		return (0);
	i = 0;
	while (i < 4)
	{
		if (!cub->textures[i]->img)
		{
			ft_putstr_fd("Error\n", 2);
			ft_putstr_fd("Cannot load texture: ", 2);
			ft_putstr_fd(cub->textures[i]->path, 2);
			ft_putstr_fd("\n", 2);
			return (0);
		}
		i++;
	}
	return (1);
}
