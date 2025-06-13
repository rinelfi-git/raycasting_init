/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: erijania <erijania@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/02 14:29:47 by tramanan          #+#    #+#             */
/*   Updated: 2025/06/05 15:28:27 by erijania         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <math.h>
#include "check_error.h"
#include "tools.h"
#include "raycast.h"
#include "cub3d.h"
#include "mlx.h"

static void	init_data(t_data *data)
{
	data->north = NULL;
	data->south = NULL;
	data->weast = NULL;
	data->east = NULL;
	data->f = -1;
	data->c = -1;
	data->map = NULL;
}

static int	gameloop(void *arg)
{
	t_cub3d	*cub;

	cub = (t_cub3d *)arg;
	if (!cub->key_events->move)
		return (0);
	if (cub->key_events->w && !player_will_hurt_wall(cub, MOVE_UP))
		move_forward(cub->player);
	if (cub->key_events->s && !player_will_hurt_wall(cub, MOVE_DOWN))
		move_backward(cub->player);
	if (cub->key_events->a && !player_will_hurt_wall(cub, MOVE_LEFT))
		move_left(cub->player);
	if (cub->key_events->d && !player_will_hurt_wall(cub, MOVE_RIGHT))
		move_right(cub->player);
	if (cub->key_events->arrow_left)
		turn_left(cub->player);
	if (cub->key_events->arrow_right)
		turn_right(cub->player);
	cub->player->delta_x = cosf(cub->player->angle);
	cub->player->delta_y = sinf(cub->player->angle);
	draw_background(cub);
	cast_rays(cub);
	mlx_put_image_to_window(cub->mlx, cub->win, cub->pix.img, 0, 0);
	return (0);
}

int	run(t_data *data)
{
	t_cub3d		cub;
	t_player	player;
	t_key_event	keydown;

	cub.player = &player;
	cub.key_events = &keydown;
	program_init(&cub, data);
	init_player(&cub);
	init_key_event(&keydown);
	gameloop(&cub);
	keydown.move = 0;
	mlx_hook(cub.win, 3, 1L << 1, handle_keyup, &cub);
	mlx_hook(cub.win, 2, 1L << 0, handle_keydown, &cub);
	mlx_hook(cub.win, 17, 0L, program_clear, &cub);
	mlx_loop_hook(cub.mlx, gameloop, &cub);
	mlx_loop(cub.mlx);
	program_clear(&cub);
	return (0);
}

int	main(int ac, char **av)
{
	t_data	data;

	init_data(&data);
	if (ac != 2 || !valid_name(av[1]))
		arg_error(ac, av);
	if (valid_file(av[1], &data))
		run(&data);
	free_data(&data);
	return (0);
}
