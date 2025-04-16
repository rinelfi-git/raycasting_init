/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycast.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: erijania <erijania@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/03 10:02:47 by erijania          #+#    #+#             */
/*   Updated: 2025/04/16 11:22:30 by erijania         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RAYCAST_H
# define RAYCAST_H
# define W_HEIGHT 768
# define W_WIDTH 1024
# define BLOCK_SIZE 256
# define TEXTURE_SIZE 64
# define MOVE_STEP 3
# define TURN_STEP 0.015
# define FLOOR 0x926829
# define ROOF 0x20a7db
# define PI 3.141592653589793
# define MOVE_UP 'w'
# define MOVE_DOWN 's'
# define MOVE_LEFT 'a'
# define MOVE_RIGHT 'd'
# define MAP_LENGTH 21
# define MAP_ITEM_LENGTH 23
# define TEXTURE_NORTH "./textures/wolfenstein/blue_stone.xpm"
# define TEXTURE_SOUTH "./textures/wolfenstein/grey_stone.xpm"
# define TEXTURE_EAST "./textures/wolfenstein/mossy.xpm"
# define TEXTURE_WEST "./textures/wolfenstein/blue_stone.xpm"
# include "mlx.h"
# include <stdio.h>
# include <fcntl.h>
# include <float.h>
# include <math.h>
# include <stdlib.h>
# include <unistd.h>

typedef struct s_cub3d			t_cub3d;
typedef struct s_pix			t_pix;
typedef struct s_miniline		t_miniline;
typedef struct s_minirect		t_minirect;
typedef struct s_player			t_player;
typedef struct s_ray_info		t_ray_info;
typedef enum e_direction		t_dir;
typedef struct s_key_event		t_key_event;
typedef struct s_texture		t_texture;

typedef struct s_will_hurt_var	t_will_hurt_var;
typedef struct s_draw_wall_var	t_draw_wall_var;
typedef struct s_ray_info_var	t_ray_info_var;

struct							s_ray_info_var
{
	t_ray_info					*info;
	double						rx;
	double						ry;
	double						dx;
	double						dy;
	double						delta_dist_x;
	double						delta_dist_y;
	double						next_x;
	double						next_y;
	int							mx;
	int							my;
	int							step_x;
	int							step_y;
	int							hit;
};
struct							s_will_hurt_var
{
	int							map_x;
	int							map_y;
	double						dx;
	double						dy;
};

struct							s_draw_wall_var
{
	int							line0;
	int							y;
	double						texture_y_offset;
	double						texture_step;
	double						texture_y;
	double						texture_x;
	double						correct_distance;
	double						line_height;
};

enum							e_direction
{
	NORTH,
	EAST,
	SOUTH,
	WEST,
};

struct							s_key_event
{
	int							w;
	int							d;
	int							s;
	int							a;
	int							arrow_left;
	int							arrow_right;
	int							move;
};

struct							s_pix
{
	void						*img;
	char						*addr;
	int							bits_per_pixel;
	int							line_length;
	int							endian;
};

struct							s_texture
{
	void						*img;
	int							width;
	int							height;
};

struct							s_cub3d
{
	void						*mlx;
	void						*win;
	t_pix						pix;
	t_key_event					*key_events;
	t_player					*player;
	char						**map;
	t_texture					*textures[4];
};

struct							s_miniline
{
	int							start_x;
	int							start_y;
	int							end_x;
	int							end_y;
	int							color;
};

struct							s_minirect
{
	int							x;
	int							y;
	int							height;
	int							width;
	int							bg_color;
};

struct							s_player
{
	int							x;
	int							y;
	double						angle;
	double						delta_x;
	double						delta_y;
	float						fov;
};

struct							s_ray_info
{
	t_dir						direction;
	float						length;
	float						hit_x;
	float						hit_y;
	float						angle;
};

void	program_init(t_cub3d *pro);
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
#endif