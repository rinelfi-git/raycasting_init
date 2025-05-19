/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub_types.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: erijania <erijania@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/19 20:39:30 by erijania          #+#    #+#             */
/*   Updated: 2025/05/19 20:53:59 by erijania         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB_TYPES_H
# define CUB_TYPES_H

typedef struct s_cub3d			t_cub3d;
typedef struct s_pix			t_pix;
typedef struct s_miniline		t_miniline;
typedef struct s_minirect		t_minirect;
typedef struct s_player			t_player;
typedef struct s_ray_info		t_ray_info;
typedef enum e_direction		t_dir;
typedef struct s_key_event		t_key_event;
typedef struct s_texture		t_texture;
typedef struct s_data			t_data;

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
	unsigned int				f;
	unsigned int				c;
	int							map_width;
	int							map_height;
	void						*mlx;
	void						*win;
	t_pix						pix;
	t_key_event					*key_events;
	t_player					*player;
	char						**map;
	t_texture					*textures[4];
	t_data						*tmp_data;
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

struct s_data
{
	char	*north;
	char	*south;
	char	*west;
	char	*east;
	int		f;
	int		c;
	char	**map;
};
#endif