/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: erijania <erijania@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/03 10:05:15 by erijania          #+#    #+#             */
/*   Updated: 2025/03/06 19:32:12 by erijania         ###   ########.fr       */
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
		mlx_destroy_image(out->img, mlx);
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
	prog->texture = NULL;// new_texture(mlx, "bricks.xpm");
	prog->simple_texture = malloc(sizeof(int *) * TEXTURE_SIZE);
	i = 0;
	while (i < TEXTURE_SIZE)
	{
		j = 0;
		prog->simple_texture[i] = malloc(sizeof(int) * TEXTURE_SIZE);
		color = i % 2;
		while (j < TEXTURE_SIZE)
		{
			prog->simple_texture[i][j++] = (color++) % 2;
		}
		i++;
	}
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
	if (prog->simple_texture)
	{
		i = 0;
		while (i < TEXTURE_SIZE)
			free(prog->simple_texture[i++]);
		free(prog->simple_texture);
	}
	if (prog->texture)
	{
		mlx_destroy_image(prog->texture->img, prog->mlx);
		free(prog->texture);
	}
	if (prog->win)
		mlx_destroy_window(prog->mlx, prog->win);
	mlx_destroy_display(prog->mlx);
	free(prog->mlx);
	exit(0);
	return (0);
}
