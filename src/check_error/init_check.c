/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_check.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: erijania <erijania@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/13 21:31:21 by erijania          #+#    #+#             */
/*   Updated: 2025/05/19 21:39:25 by erijania         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "raycast.h"

int	init_check(t_cub3d *cub)
{
	int	i;

	if (!cub->map)
		return (0);
	i = 0;
	while (i < 4)
	{
		if (!cub->textures[i++])
			return (0);
	}
	return (1);
}
