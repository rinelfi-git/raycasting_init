/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: erijania <erijania@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/03 10:11:33 by erijania          #+#    #+#             */
/*   Updated: 2025/04/15 23:29:10 by erijania         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "raycast.h"

static void	init_player(t_program *pro)
{
	int		player_offset;
	int		i;
	int		j;
	float	angle;

	i = 0;
	player_offset = (int)(BLOCK_SIZE / 2);
	angle = 0;
	while (i < MAP_LENGTH)
	{
		j = 0;
		while (j < MAP_ITEM_LENGTH)
		{
			if (pro->map[i][j] && pro->map[i][j] != '1'
				&& pro->map[i][j] != '0')
			{
				if (pro->map[i][j] == 'N')
					angle = PI / 2.0;
				else if (pro->map[i][j] == 'E')
					angle = PI;
				else if (pro->map[i][j] == 'S')
					angle = 3.0 * PI / 2.0;
				else if (pro->map[i][j] == 'W')
					angle = 0;
				pro->player->x = j * BLOCK_SIZE + player_offset;
				pro->player->y = i * BLOCK_SIZE + player_offset;
				pro->player->angle = angle;
				pro->player->delta_x = cosf(angle);
				pro->player->delta_y = sinf(angle);
				pro->player->fov = PI / 3.0;
				return ;
			}
			j++;
		}
		i++;
	}
}

static int	gameloop(void *arg)
{
	t_program	*pro;

	pro = (t_program *)arg;
	if (!pro->key_events->move)
		return (0);
	if (pro->key_events->w && !player_will_hurt_wall(pro, MOVE_UP))
		move_forward(pro->player);
	if (pro->key_events->s && !player_will_hurt_wall(pro, MOVE_DOWN))
		move_backward(pro->player);
	if (pro->key_events->a && !player_will_hurt_wall(pro, MOVE_LEFT))
		move_left(pro->player);
	if (pro->key_events->d && !player_will_hurt_wall(pro, MOVE_RIGHT))
		move_right(pro->player);
	if (pro->key_events->arrow_left) // Flèche gauche (LEFT_ARROW)
		turn_left(pro->player);
	if (pro->key_events->arrow_right) // Flèche droite (RIGHT_ARROW)
		turn_right(pro->player);
	pro->player->delta_x = cosf(pro->player->angle);
	pro->player->delta_y = sinf(pro->player->angle);
	draw_background(pro);
	cast_rays(pro);
	mlx_put_image_to_window(pro->mlx, pro->win, pro->pix.img, 0, 0);
	return (0);
}

static void	load_map(t_program *pro)
{
	int		fd;
	char	buff[MAP_ITEM_LENGTH];

	fd = open("map.cub", O_RDONLY);
	pro->map = malloc(sizeof(char *) * (MAP_LENGTH + 1));
	if (!pro->map)
		exit(EXIT_FAILURE);
	int r, i, j;
	i = 0;
	while (i <= MAP_LENGTH)
		pro->map[i++] = NULL;
	i = 0;
	while ((r = read(fd, buff, MAP_ITEM_LENGTH - 1)) > 0)
	{
		pro->map[i] = malloc(sizeof(char) * MAP_ITEM_LENGTH);
		if (!pro->map[i])
			exit(EXIT_FAILURE);
		j = 0;
		while (j < r && buff[j] && buff[j] != '\n')
		{
			pro->map[i][j] = buff[j];
			j++;
		}
		pro->map[i][j] = 0;
		i++;
	}
	pro->map[i] = NULL;
	close(fd);
}

int	main(void)
{
	t_player	player;
	t_program	prog;
	t_key_event	keydown;

	program_init(&prog);
	prog.player = &player;
	prog.key_events = &keydown;
	load_map(&prog);
	init_player(&prog);
	init_key_event(&keydown);
	gameloop(&prog);
	keydown.move = 0;
	mlx_hook(prog.win, 3, 1L << 1, handle_keyup, &prog);
	mlx_hook(prog.win, 2, 1L << 0, handle_keydown, &prog);
	mlx_hook(prog.win, 17, 0L, program_clear, &prog);
	mlx_loop_hook(prog.mlx, gameloop, &prog);
	mlx_loop(prog.mlx);
	program_clear(&prog);
	return (0);
}
