/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycast.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: erijania <erijania@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/03 10:02:47 by erijania          #+#    #+#             */
/*   Updated: 2025/03/05 00:42:42 by erijania         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RAYCAST_H
# define RAYCAST_H
# include "mlx.h"
# define W_HEIGHT 720
# define W_WIDTH 1280
# define BLOCK_SIZE 600
# define STEP 10
# define WALL_NORTH 0x12d012
# define WALL_SOUTH 0x0e810e
# define WALL_EAST 0x347aeb
# define WALL_WEST 0x0341a3
# define FLOOR 0x926829
# define ROOF 0x20a7db
# define PI 3.141592653589793
# include <stdio.h>

typedef struct s_program	t_program;
typedef struct s_pix		t_pix;
typedef struct s_miniline	t_miniline;
typedef struct s_minirect	t_minirect;
typedef struct s_player		t_player;
typedef struct s_ray_info	t_ray_info;
typedef enum e_direction	t_dir;
typedef struct s_key_event	t_key_event;

enum e_direction
{
	NORTH,
	EAST,
	SOUTH,
	WEST,
};

struct s_key_event
{
	int	w;
	int	d;
	int	s;
	int	q;
	int	arrow_left;
	int	arrow_right;
	int	move;
};

struct s_pix
{
	void	*img;
	char	*addr;
	int		bits_per_pixel;
	int		line_length;
	int		endian;
};

struct s_program
{
	void		*mlx;
	void		*win;
	t_pix		pix;
	t_key_event	*key_events;
	t_player	*player;
	int			**map;
};

struct s_miniline
{
	int	start_x;
	int	start_y;
	int	end_x;
	int	end_y;
	int	color;
};

struct s_minirect
{
	int	x;
	int	y;
	int	height;
	int	width;
	int	bg_color;
};

struct s_player
{
	int		x;
	int		y;
	float	angle;
	float	delta_x;
	float	delta_y;
	float	fov;
};

struct s_ray_info
{
	t_dir	direction;
	float	length;
	float	hit_x;
	float	hit_y;
	float	angle;
};

void	program_init(t_program *prog);
int		program_clear(t_program *prog);
void	put_pixel_at(t_program *prog, int x, int y, int color);

void	draw_rectangle(t_program *prog, t_minirect *form);
void	draw_square(t_program *prog, int x, int y, int size, int out, int bg);
void	draw_line(t_program *prog, t_miniline *line);
void	screen_clean(t_program *prog);
#endif