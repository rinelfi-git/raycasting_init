/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dda2.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: erijania <erijania@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/15 23:00:10 by erijania          #+#    #+#             */
/*   Updated: 2025/04/15 23:32:46 by erijania         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "raycast.h"

void	init_get_ray_info_var(t_ray_info_var *, t_program *, double);
t_ray_info	*create_ray_info(double);
void	update_ray_hit_horizontal(t_ray_info_var *);
void	update_ray_hit_vertical(t_ray_info_var *);

static void	handle_ray_hit_wall(t_ray_info_var *var, t_program *pro)
{
	var->hit = 1;
	var->info->hit_x = var->ray_x;
	var->info->hit_y = var->ray_y;
	var->info->length = sqrt(pow(var->ray_x - pro->player->x, 2)
			+ pow(var->ray_y - pro->player->y, 2));
}

static void	handle_ray_overflow(t_ray_info_var *var)
{
	var->info->length = MAP_LENGTH * MAP_ITEM_LENGTH * BLOCK_SIZE;
	var->hit = 1;
}

t_ray_info	*get_ray_info(t_program *pro, float ray_angle)
{
	t_ray_info_var	var;

	init_get_ray_info_var(&var, pro, ray_angle);
	var.info = create_ray_info(ray_angle);
	while (!var.hit)
	{
		if (var.next_dist_x < var.next_dist_y)
			update_ray_hit_horizontal(&var);
		else
			update_ray_hit_vertical(&var);
		if (var.map_y < 0 || var.map_y > MAP_LENGTH || var.map_x < 0
			|| var.map_x >= MAP_ITEM_LENGTH)
			handle_ray_overflow(&var);
		if (pro->map[var.map_y][var.map_x] == '1')
			handle_ray_hit_wall(&var, pro);
	}
	return (var.info);
}
void	cast_rays(t_program *pro)
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
