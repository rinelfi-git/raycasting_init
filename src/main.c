/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: erijania <erijania@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/03 10:11:33 by erijania          #+#    #+#             */
/*   Updated: 2025/03/07 01:02:16 by erijania         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "raycast.h"
#include <X11/keysym.h>
#include <fcntl.h>
#include <float.h>
#include <math.h>
#include <stdlib.h>
#include <unistd.h>
#define MAP_LENGTH 21
#define MAP_ITEM_LENGTH 23

static t_ray_info	*get_ray_info(t_program *pro, float ray_angle)
{
	t_ray_info	*out;

	float ray_x, ray_y, delta_x, delta_y, delta_dist_x, delta_dist_y,
		next_dist_x, next_dist_y;
	int map_x, map_y, step_x, step_y, hit;
	ray_x = pro->player->x;
	ray_y = pro->player->y;
	map_x = (int)floorf(ray_x / BLOCK_SIZE);
	map_y = (int)floorf(ray_y / BLOCK_SIZE);
	delta_x = -cosf(ray_angle);
	delta_y = -sinf(ray_angle);
	delta_dist_x = fabs(1.0 / delta_x);
	delta_dist_y = fabs(1.0 / delta_y);
	step_x = delta_x < 0 ? -1 : 1;
	step_y = delta_y < 0 ? -1 : 1;
	if (delta_x < 0)
		next_dist_x = (ray_x - map_x * BLOCK_SIZE) / fabsf(delta_x);
	else
		next_dist_x = ((map_x + 1) * BLOCK_SIZE - ray_x) / fabsf(delta_x);
	if (delta_y < 0)
		next_dist_y = (ray_y - map_y * BLOCK_SIZE) / fabsf(delta_y);
	else
		next_dist_y = ((map_y + 1) * BLOCK_SIZE - ray_y) / fabsf(delta_y);
	out = malloc(sizeof(t_ray_info));
	out->angle = ray_angle;
	out->length = 0.0;
	out->hit_x = 0;
	out->hit_y = 0;
	hit = 0;
	while (!hit)
	{
		if (next_dist_x < next_dist_y)
		{
			ray_x += next_dist_x * delta_x;
			ray_y += next_dist_x * delta_y;
			next_dist_y -= next_dist_x;
			next_dist_x = delta_dist_x * BLOCK_SIZE;
			map_x += step_x;
			out->direction = step_x < 0 ? WEST : EAST;
		}
		else
		{
			ray_x += next_dist_y * delta_x;
			ray_y += next_dist_y * delta_y;
			next_dist_x -= next_dist_y;
			next_dist_y = delta_dist_y * BLOCK_SIZE;
			map_y += step_y;
			out->direction = step_y < 0 ? NORTH : SOUTH;
		}
		if (map_y < 0 || map_y > MAP_LENGTH || map_x < 0
			|| map_x >= MAP_ITEM_LENGTH)
		{
			out->length = MAP_LENGTH * MAP_ITEM_LENGTH * BLOCK_SIZE;
			break ;
		}
		if (pro->map[map_y][map_x] == '1')
		{
			hit = 1;
			out->hit_x = ray_x;
			out->hit_y = ray_y;
			out->length = sqrtf(powf(ray_x - pro->player->x, 2) + powf(ray_y
						- pro->player->y, 2));
		}
	}
	return (out);
}

static void	draw_wall(t_program *pro, int ray, t_ray_info *info)
{
	int		line0;
	float	texture_y_offset;
	float	texture_step;
	int		y;
	float	texture_y;
	float	texture_x;

	float correct_distance, line_height;
	correct_distance = info->length * cosf(pro->player->angle - info->angle);
	line_height = (BLOCK_SIZE * W_HEIGHT) / correct_distance;
	texture_y_offset = 0;
	texture_step = TEXTURE_SIZE / line_height;
	if (line_height > W_HEIGHT)
	{
		texture_y_offset = (line_height - W_HEIGHT) / 2;
		line_height = W_HEIGHT;
	}
	line0 = (int)(W_HEIGHT / 2.0 - line_height / 2.0);
	y = 0;
	texture_y = texture_y_offset * texture_step;
	if (info->direction == NORTH || info->direction == SOUTH)
	{
		texture_x = (int)(info->hit_x / (BLOCK_SIZE / TEXTURE_SIZE))
			% TEXTURE_SIZE;
		if (info->angle > PI)
			texture_x = TEXTURE_SIZE - 1 - texture_x;
	}
	else
	{
		texture_x = (int)(info->hit_y / (BLOCK_SIZE / TEXTURE_SIZE))
			% TEXTURE_SIZE;
		if (info->angle < (PI / 2) || info->angle > (3.0 * PI / 2.0))
			texture_x = TEXTURE_SIZE - 1 - texture_x;
	}
	while (y < (int)line_height)
	{
		put_pixel_at(pro, ray, y + line0,
			get_texture_color(pro->textures[info->direction], (int)texture_x,
				(int)texture_y));
		y++;
		texture_y += texture_step;
	}
}

static void	draw_background(t_program *pro)
{
	t_minirect roof, floor;
	roof.x = 0;
	roof.y = 0;
	roof.width = W_WIDTH;
	roof.height = W_HEIGHT;
	roof.bg_color = ROOF;
	draw_rectangle(pro, &roof);
	floor.x = 0;
	floor.y = W_HEIGHT / 2;
	floor.width = W_WIDTH;
	floor.height = W_HEIGHT - floor.y;
	floor.bg_color = FLOOR;
	draw_rectangle(pro, &floor);
}

static void	draw_3d(t_program *pro)
{
	int			ray;
	float		angle_step;
	float		ray_angle;
	float		start_angle;
	t_ray_info	*ray_info;

	ray = 0;
	angle_step = pro->player->fov / W_WIDTH;
	start_angle = pro->player->angle - pro->player->fov / 2.0;
	while (ray <= W_WIDTH)
	{
		ray_angle = start_angle + (ray * angle_step);
		ray_info = get_ray_info(pro, ray_angle);
		draw_wall(pro, ray, ray_info);
		free(ray_info);
		ray++;
	}
}

static int	player_will_hurt_wall(t_program *pro, char dir)
{
	int map_x, map_y;
	float delta_x, delta_y;
	delta_x = pro->player->delta_x * MOVE_STEP * 5;
	delta_y = pro->player->delta_y * MOVE_STEP * 5;
	map_x = -1;
	map_y = -1;
	if (dir == 'w')
	{
		map_y = (int)roundf(pro->player->y - delta_y);
		map_x = (int)roundf(pro->player->x - delta_x);
	}
	if (dir == 's')
	{
		map_y = (int)roundf(pro->player->y + delta_y);
		map_x = (int)roundf(pro->player->x + delta_x);
	}
	if (dir == 'q')
	{
		map_y = (int)roundf(pro->player->y + delta_x);
		map_x = (int)roundf(pro->player->x - delta_y);
	}
	if (dir == 'd')
	{
		map_y = (int)roundf(pro->player->y - delta_x);
		map_x = (int)roundf(pro->player->x + delta_y);
	}
	if (map_x >= 0 && map_y >= 0)
		return (pro->map[map_y / BLOCK_SIZE][map_x / BLOCK_SIZE] == '1');
	return (1);
}

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

static int	need_refresh(t_program *pro)
{
	return (pro->key_events->w || pro->key_events->d || pro->key_events->s
		|| pro->key_events->q || pro->key_events->arrow_left
		|| pro->key_events->arrow_right);
}

static int	handle_keydown(int code, void *arg)
{
	t_program	*pro;

	pro = (t_program *)arg;
	if (code == XK_z)
		pro->key_events->w = 1;
	if (code == XK_d)
		pro->key_events->d = 1;
	if (code == XK_s)
		pro->key_events->s = 1;
	if (code == XK_q)
		pro->key_events->q = 1;
	if (code == XK_Left)
		pro->key_events->arrow_left = 1;
	if (code == XK_Right)
		pro->key_events->arrow_right = 1;
	if (code == XK_Escape)
		return (program_clear(pro));
	pro->key_events->move = need_refresh(pro);
	return (0);
}

static int	handle_keyup(int code, void *arg)
{
	t_program	*pro;

	pro = (t_program *)arg;
	if (code == XK_z)
		pro->key_events->w = 0;
	if (code == XK_d)
		pro->key_events->d = 0;
	if (code == XK_s)
		pro->key_events->s = 0;
	if (code == XK_q)
		pro->key_events->q = 0;
	if (code == XK_Left)
		pro->key_events->arrow_left = 0;
	if (code == XK_Right)
		pro->key_events->arrow_right = 0;
	pro->key_events->move = need_refresh(pro);
	return (0);
}

static int	gameloop(void *arg)
{
	t_program	*pro;

	pro = (t_program *)arg;
	if (!pro->key_events->move)
		return (0);
	if (pro->key_events->w && !player_will_hurt_wall(pro, 'w'))
	{
		pro->player->y -= (int)roundf(pro->player->delta_y * MOVE_STEP);
		pro->player->x -= (int)roundf(pro->player->delta_x * MOVE_STEP);
	}
	if (pro->key_events->s && !player_will_hurt_wall(pro, 's'))
	{
		pro->player->y += (int)roundf(pro->player->delta_y * MOVE_STEP);
		pro->player->x += (int)roundf(pro->player->delta_x * MOVE_STEP);
	}
	if (pro->key_events->q && !player_will_hurt_wall(pro, 'q'))
	{
		pro->player->y += (int)roundf(pro->player->delta_x * MOVE_STEP);
		pro->player->x -= (int)roundf(pro->player->delta_y * MOVE_STEP);
	}
	if (pro->key_events->d && !player_will_hurt_wall(pro, 'd'))
	{
		pro->player->y -= (int)roundf(pro->player->delta_x * MOVE_STEP);
		pro->player->x += (int)roundf(pro->player->delta_y * MOVE_STEP);
	}
	if (pro->key_events->arrow_left) // Flèche gauche (LEFT_ARROW)
	{
		pro->player->angle -= TURN_STEP;
		if (pro->player->angle < 0)
			pro->player->angle += PI * 2;
	}
	if (pro->key_events->arrow_right) // Flèche droite (RIGHT_ARROW)
	{
		pro->player->angle += TURN_STEP;
		if (pro->player->angle > PI * 2)
			pro->player->angle -= PI * 2;
	}
	pro->player->delta_x = cosf(pro->player->angle);
	pro->player->delta_y = sinf(pro->player->angle);
	draw_background(pro);
	draw_3d(pro);
	mlx_put_image_to_window(pro->mlx, pro->win, pro->pix.img, 0, 0);
	return (0);
}

static void	init_key_event(t_key_event *event)
{
	event->w = 0;
	event->d = 0;
	event->s = 0;
	event->q = 0;
	event->arrow_left = 0;
	event->arrow_right = 0;
	event->move = 1;
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
	return (0);
}
