/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dda2.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: erijania <erijania@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/15 23:00:10 by erijania          #+#    #+#             */
/*   Updated: 2025/05/28 15:36:36 by erijania         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <math.h>
#include <stdlib.h>
#include "raycast.h"

void		init_local(t_ray_info_var *var, t_cub3d *cub, double angle);
t_ray_info	*create_ray_info(double angle);
void		update_ray_hit_horizontal(t_ray_info_var *var);
void		update_ray_hit_vertical(t_ray_info_var *var);

static void	handle_ray_hit_wall(t_ray_info_var *var, t_cub3d *pro)
{
	var->hit = 1;
	var->info->hit_x = var->rx;
	var->info->hit_y = var->ry;
	var->info->length = sqrt(pow(var->rx - pro->player->x, 2)
			+ pow(var->ry - pro->player->y, 2));
}

static void	handle_ray_overflow(t_ray_info_var *var)
{
	var->info->length = var->cub->map_height * var->cub->map_width
		* BLOCK_SIZE;
	var->hit = 1;
}

t_ray_info	*get_ray_info(t_cub3d *cub, float ray_angle)
{
	t_ray_info_var	var;

	init_local(&var, cub, ray_angle);
	var.info = create_ray_info(ray_angle);
	while (!var.hit)
	{
		if (var.next_x < var.next_y)
			update_ray_hit_horizontal(&var);
		else
			update_ray_hit_vertical(&var);
		if (var.my < 0 || var.my > cub->map_height || var.mx < 0
			|| var.mx >= cub->map_width)
			handle_ray_overflow(&var);
		if (cub->map[var.my][var.mx] == '1')
			handle_ray_hit_wall(&var, cub);
	}
	return (var.info);
}

void	cast_rays(t_cub3d *cub)
{
	int			ray;
	float		angle_step;
	float		ray_angle;
	float		start_angle;
	t_ray_info	*ray_info;

	ray = 0;
	angle_step = cub->player->fov / W_WIDTH;
	start_angle = cub->player->angle - cub->player->fov / 2.0;
	while (ray <= W_WIDTH)
	{
		ray_angle = start_angle + (ray * angle_step);
		ray_info = get_ray_info(cub, ray_angle);
		draw_wall(cub, ray, ray_info);
		free(ray_info);
		ray++;
	}
}
