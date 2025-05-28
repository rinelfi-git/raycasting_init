/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   texture.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: erijania <erijania@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/06 21:00:35 by erijania          #+#    #+#             */
/*   Updated: 2025/05/28 15:37:37 by erijania         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <math.h>
#include <stdlib.h>
#include "raycast.h"
#include "mlx.h"

static void	coordinate_from_texture(t_texture *texture, int *x, int *y)
{
	*x = (int)(*x * texture->width / TEXTURE_SIZE);
	*y = (int)(*y * texture->height / TEXTURE_SIZE);
}

int	get_texture_color(t_texture *texture, int x, int y)
{
	int		bit;
	int		length;
	int		endian;
	char	*address;

	coordinate_from_texture(texture, &x, &y);
	address = mlx_get_data_addr(texture->img, &bit, &length, &endian);
	return (*(unsigned int *)(address + (y * length + x * (bit / 8))));
}

void	texture_destroy(void *mlx, t_texture *texture)
{
	if (texture)
	{
		free(texture->path);
		if (texture->img)
			mlx_destroy_image(mlx, texture->img);
		free(texture);
	}
}
