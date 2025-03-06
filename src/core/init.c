/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: erijania <erijania@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/03 10:05:15 by erijania          #+#    #+#             */
/*   Updated: 2025/03/06 21:39:55 by erijania         ###   ########.fr       */
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
	printf("OPENING %s\n", path);
	if (!out->img || out->width != TEXTURE_SIZE || out->height != TEXTURE_SIZE)
	{
		printf("ERROR\n");
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
	int		i;
	int		j;
	int		color;

	mlx = mlx_init();
	pix = &(prog->pix);
	prog->mlx = mlx;
	prog->win = mlx_new_window(mlx, W_WIDTH, W_HEIGHT, "Ray casting");
	pix->img = mlx_new_image(mlx, W_WIDTH, W_HEIGHT);
	pix->addr = mlx_get_data_addr(pix->img, &pix->bits_per_pixel,
			&pix->line_length, &pix->endian);
	prog->textures[NORTH] = new_texture(mlx, "./bookshelf.xpm");
	prog->textures[EAST] = new_texture(mlx, "./bookshelf_01.xpm");
	prog->textures[SOUTH] = new_texture(mlx, "./bookshelf_02.xpm");
	prog->textures[WEST] = new_texture(mlx, "./bookshelf_03.xpm");
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
	if (prog->textures)
	{
		i = 0;
		while (i < 4)
			texture_destroy(prog->mlx, prog->textures[i++]);
	}
	if (prog->win)
		mlx_destroy_window(prog->mlx, prog->win);
	mlx_destroy_display(prog->mlx);
	free(prog->mlx);
	exit(0);
	return (0);
}
