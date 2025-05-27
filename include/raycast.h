/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycast.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: erijania <erijania@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/03 10:02:47 by erijania          #+#    #+#             */
/*   Updated: 2025/05/27 19:59:54 by erijania         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RAYCAST_H
# define RAYCAST_H
# define W_HEIGHT 480
# define W_WIDTH 640
# define BLOCK_SIZE 800
# define TEXTURE_SIZE 64
# define MOVE_STEP 3
# define TURN_STEP 0.005
# define PI 3.141592653589793
# define MOVE_UP 'w'
# define MOVE_DOWN 's'
# define MOVE_LEFT 'a'
# define MOVE_RIGHT 'd'
# include "mlx.h"
# include "cub_types.h"
# include <stdio.h>
# include <fcntl.h>
# include <float.h>
# include <math.h>
# include <stdlib.h>
# include <unistd.h>

void	program_init(t_cub3d *pro, t_data *data);
void 	init_player(t_cub3d *cub);
int		program_clear(t_cub3d *pro);
void	put_pixel_at(t_cub3d *pro, int x, int y, int color);
int		get_texture_color(t_texture *texture, int x, int y);
void	texture_destroy(void *mlx, t_texture *texture);

void	draw_rectangle(t_cub3d *pro, t_minirect *rect);
void	draw_line(t_cub3d *pro, t_miniline *line);
void	screen_clean(t_cub3d *pro);

void	init_key_event(t_key_event *event);
int		handle_keyup(int code, void *event);
int		handle_keydown(int code, void *event);

void	move_forward(t_player *player);
void	move_backward(t_player *player);
void	move_left(t_player *player);
void	move_right(t_player *player);
void	turn_right(t_player *player);
void	turn_left(t_player *player);

int		player_will_hurt_wall(t_cub3d *pro, char direction);

void	draw_background(t_cub3d *pro);
void	cast_rays(t_cub3d *pro);
void	draw_wall(t_cub3d *pro, int ray_index, t_ray_info *info);

int		run(t_data *data);
#endif