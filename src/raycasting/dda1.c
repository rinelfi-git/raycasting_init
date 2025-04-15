/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dda1.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: erijania <erijania@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/15 23:00:10 by erijania          #+#    #+#             */
/*   Updated: 2025/04/15 23:08:12 by erijania         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "raycast.h"

void	init_get_ray_info_var(t_ray_info_var *var, t_program *pro,
		double angle)
{
	var->ray_x = pro->player->x;
	var->ray_y = pro->player->y;
	var->map_x = (int)floor(var->ray_x / BLOCK_SIZE);
	var->map_y = (int)floor(var->ray_y / BLOCK_SIZE);
	var->delta_x = -cos(angle);
	var->delta_y = -sin(angle);
	var->delta_dist_x = fabs(1.0 / var->delta_x);
	var->delta_dist_y = fabs(1.0 / var->delta_y);
	var->step_x = var->delta_x < 0 ? -1 : 1;
	var->step_y = var->delta_y < 0 ? -1 : 1;
	if (var->delta_x < 0)
		var->next_dist_x = (var->ray_x - var->map_x * BLOCK_SIZE)
			/ fabs(var->delta_x);
	else
		var->next_dist_x = ((var->map_x + 1) * BLOCK_SIZE - var->ray_x)
			/ fabs(var->delta_x);
	if (var->delta_y < 0)
		var->next_dist_y = (var->ray_y - var->map_y * BLOCK_SIZE)
			/ fabs(var->delta_y);
	else
		var->next_dist_y = ((var->map_y + 1) * BLOCK_SIZE - var->ray_y)
			/ fabs(var->delta_y);
	var->info = NULL;
	var->hit = 0;
}

t_ray_info	*create_ray_info(double angle)
{
	t_ray_info	*out;

	out = malloc(sizeof(t_ray_info));
	out->angle = angle;
	out->length = 0.0;
	out->hit_x = 0;
	out->hit_y = 0;
	return (out);
}

void	update_ray_hit_horizontal(t_ray_info_var *var)
{
	var->ray_x += var->next_dist_x * var->delta_x;
	var->ray_y += var->next_dist_x * var->delta_y;
	var->next_dist_y -= var->next_dist_x;
	var->next_dist_x = var->delta_dist_x * BLOCK_SIZE;
	var->map_x += var->step_x;
	var->info->direction = var->step_x < 0 ? WEST : EAST;
}

void	update_ray_hit_vertical(t_ray_info_var *var)
{
	var->ray_x += var->next_dist_y * var->delta_x;
	var->ray_y += var->next_dist_y * var->delta_y;
	var->next_dist_x -= var->next_dist_y;
	var->next_dist_y = var->delta_dist_y * BLOCK_SIZE;
	var->map_y += var->step_y;
	var->info->direction = var->step_y < 0 ? NORTH : SOUTH;
}
