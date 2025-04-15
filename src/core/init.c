/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: erijania <erijania@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/03 10:05:15 by erijania          #+#    #+#             */
/*   Updated: 2025/04/04 09:06:57 by erijania         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "raycast.h"
#include <stdlib.h>

t_texture	*new_texture(void *mlx, char *path)
{
	t_texture *out;
	
	out = malloc(sizeof(t_texture));
	if (!out)
		exit(EXIT_FAILURE);
	out->img = mlx_xpm_file_to_image(mlx, path, &(out->width), &(out->height));
	if (!out->img || out->width != TEXTURE_SIZE || out->height != TEXTURE_SIZE)
	{
		mlx_destroy_image(mlx, out->img);
		free(out);
		return (NULL);
	}
	return (out);
}

void	program_init(t_program *prog)
{
	void	*mlx;
	t_pix	*pix;

	mlx = mlx_init();
	pix = &(prog->pix);
	prog->mlx = mlx;
	prog->win = mlx_new_window(mlx, W_WIDTH, W_HEIGHT, "Ray casting");
	pix->img = mlx_new_image(mlx, W_WIDTH, W_HEIGHT);
	pix->addr = mlx_get_data_addr(pix->img, &pix->bits_per_pixel,
			&pix->line_length, &pix->endian);
	prog->textures[NORTH] = new_texture(mlx, "./textures/wolfenstein/blue_stone.xpm");
	prog->textures[EAST] = new_texture(mlx, "./textures/wolfenstein/color_stone.xpm");
	prog->textures[SOUTH] = new_texture(mlx, "./textures/wolfenstein/grey_stone.xpm");
	prog->textures[WEST] = new_texture(mlx, "./textures/wolfenstein/mossy.xpm");
	prog->map = NULL;
	prog->key_events = NULL;
	prog->player = NULL;
}

int	program_clear(t_program *prog)
{
	int	i;

	if (prog->map)
	{
		i = 0;
		while (prog->map[i])
			free(prog->map[i++]);
		free(prog->map);
	}
	i = 0;
	while (i < 4)
		texture_destroy(prog->mlx, prog->textures[i++]);
	if (prog->win)
		mlx_destroy_window(prog->mlx, prog->win);
	mlx_destroy_image(prog->mlx, prog->pix.img);
	mlx_destroy_display(prog->mlx);
	free(prog->mlx);
	exit(0);
	return (0);
}
