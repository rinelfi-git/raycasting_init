/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_wall.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: erijania <erijania@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/15 23:10:24 by erijania          #+#    #+#             */
/*   Updated: 2025/05/28 15:36:45 by erijania         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <math.h>
#include "raycast.h"

void	draw_background(t_cub3d *cub)
{
	t_minirect	roof;
	t_minirect	floor;

	roof.x = 0;
	roof.y = 0;
	roof.width = W_WIDTH;
	roof.height = W_HEIGHT;
	roof.bg_color = cub->c;
	draw_rectangle(cub, &roof);
	floor.x = 0;
	floor.y = W_HEIGHT / 2;
	floor.width = W_WIDTH;
	floor.height = W_HEIGHT - floor.y;
	floor.bg_color = cub->f;
	draw_rectangle(cub, &floor);
}

static void	init_draw_wall_var(t_draw_wall_var *var, t_cub3d *pro,
		t_ray_info *info)
{
	var->correct_distance = info->length * cosf(pro->player->angle
			- info->angle);
	var->line_height = (BLOCK_SIZE * W_HEIGHT) / var->correct_distance;
	var->texture_y_offset = 0;
	var->texture_step = TEXTURE_SIZE / var->line_height;
	if (var->line_height > W_HEIGHT)
	{
		var->texture_y_offset = (var->line_height - W_HEIGHT) / 2;
		var->line_height = W_HEIGHT;
	}
	var->line0 = (int)(W_HEIGHT / 2.0 - var->line_height / 2.0);
	var->texture_y = var->texture_y_offset * var->texture_step;
	var->y = 0;
}

static void	compute_texture_x(t_draw_wall_var *var, t_ray_info *info)
{
	if (info->direction == NORTH || info->direction == SOUTH)
	{
		var->texture_x = (int)(info->hit_x / (BLOCK_SIZE / TEXTURE_SIZE))
			% TEXTURE_SIZE;
		if (info->angle > PI)
			var->texture_x = TEXTURE_SIZE - 1 - (int)var->texture_x;
	}
	else
	{
		var->texture_x = (int)(info->hit_y / (BLOCK_SIZE / TEXTURE_SIZE))
			% TEXTURE_SIZE;
		if (info->angle < (PI / 2) || info->angle > (3.0 * PI / 2.0))
			var->texture_x = TEXTURE_SIZE - 1 - (int)var->texture_x;
	}
}

void	draw_wall(t_cub3d *pro, int ray, t_ray_info *info)
{
	t_draw_wall_var	var;

	init_draw_wall_var(&var, pro, info);
	compute_texture_x(&var, info);
	while (var.y < (int)var.line_height)
	{
		put_pixel_at(pro, ray, var.y + var.line0,
			get_texture_color(pro->textures[info->direction],
				(int)var.texture_x, (int)var.texture_y));
		var.y++;
		var.texture_y += var.texture_step;
	}
}
