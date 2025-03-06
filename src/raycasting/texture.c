/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   texture.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: erijania <erijania@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/06 21:00:35 by erijania          #+#    #+#             */
/*   Updated: 2025/03/06 21:36:22 by erijania         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "raycast.h"
#include <stdlib.h>

int	get_texture_color(t_texture *texture, int x, int y)
{
	int		bit;
	int		length;
	int		endian;
	char	*address;

	address = mlx_get_data_addr(texture->img, &bit, &length, &endian);
	return (*(unsigned int *)(address + (y * length + x * (bit / 8))));
}

void	texture_destroy(void *mlx, t_texture *texture)
{
	mlx_destroy_image(mlx, texture->img);
	free(texture);
}
