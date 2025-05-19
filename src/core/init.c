/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: erijania <erijania@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/03 10:05:15 by erijania          #+#    #+#             */
/*   Updated: 2025/05/19 21:38:58 by erijania         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "raycast.h"
#include "check_error.h"
#include "tools.h"
#include "cub3d.h"
#include <stdlib.h>

int	init_check(t_cub3d *cub);

t_texture	*new_texture(void *mlx, char *path)
{
	t_texture	*out;

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

void	program_init(t_cub3d *cub, t_data *data)
{
	void	*mlx;
	t_pix	*pix;

	mlx = mlx_init();
	pix = &(cub->pix);
	cub->mlx = mlx;
	cub->win = mlx_new_window(mlx, W_WIDTH, W_HEIGHT, "Ray casting");
	pix->img = mlx_new_image(mlx, W_WIDTH, W_HEIGHT);
	pix->addr = mlx_get_data_addr(pix->img, &pix->bits_per_pixel,
			&pix->line_length, &pix->endian);
	cub->textures[NORTH] = new_texture(mlx, data->north);
	cub->textures[EAST] = new_texture(mlx, data->east);
	cub->textures[SOUTH] = new_texture(mlx, data->south);
	cub->textures[WEST] = new_texture(mlx, data->west);
	cub->c = data->c;
	cub->f = data->f;
	cub->map = map_dup(data->map);
	cub->map_height = ft_tabsize(data->map);
	cub->map_width = count_len(data->map[0]);
	cub->tmp_data = data;
	if (!init_check(cub))
		program_clear(cub);
}

int	program_clear(t_cub3d *prog)
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
	if (prog->tmp_data)
		free_data(prog->tmp_data);
	exit(0);
	return (0);
}

static	int	player_pos(t_cub3d	*prog)
{
	int	i;
	int	j;
	int	c;
	int		player_offset;

	i = 0;
	player_offset = (int)(BLOCK_SIZE / 2);
	while (i < prog->map_height)
	{
		j = 0;
		while (j < prog->map_width)
		{
			if (!checkchar("NEWS", prog->map[i][j]))
			{
				c = prog->map[i][j];
				prog->player->x = j * BLOCK_SIZE + player_offset;
				prog->player->y = i * BLOCK_SIZE + player_offset;
				return (c);
			}
			j++;
		}
		i++;
	}
	return (0);
}

void init_player(t_cub3d *cub)
{
	int		pos;
	float	angle;

	angle = 0;
	pos = player_pos(cub);
	if (pos == 'N')
		angle = PI / 2.0;
	else if (pos == 'E')
		angle = PI;
	else if (pos == 'S')
		angle = 3.0 * PI / 2.0;
	else if (pos == 'W')
		angle = 0;
	cub->player->angle = angle;
	cub->player->delta_x = cosf(angle);
	cub->player->delta_y = sinf(angle);
	cub->player->fov = PI / 3.0;
}
