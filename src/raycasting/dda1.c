/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dda1.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: erijania <erijania@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/15 23:00:10 by erijania          #+#    #+#             */
/*   Updated: 2025/05/19 21:47:23 by erijania         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "raycast.h"

void	init_local(t_ray_info_var *var, t_cub3d *cub, double angle)
{
	var->rx = cub->player->x;
	var->ry = cub->player->y;
	var->mx = (int)floor(var->rx / BLOCK_SIZE);
	var->my = (int)floor(var->ry / BLOCK_SIZE);
	var->dx = -cos(angle);
	var->dy = -sin(angle);
	var->delta_dist_x = fabs(1.0 / var->dx);
	var->delta_dist_y = fabs(1.0 / var->dy);
	var->step_x = 1 - 2 * (var->dx < 0);
	var->step_y = 1 - 2 * (var->dy < 0);
	if (var->dx < 0)
		var->next_x = (var->rx - var->mx * BLOCK_SIZE) / fabs(var->dx);
	else
		var->next_x = ((var->mx + 1) * BLOCK_SIZE - var->rx) / fabs(var->dx);
	if (var->dy < 0)
		var->next_y = (var->ry - var->my * BLOCK_SIZE) / fabs(var->dy);
	else
		var->next_y = ((var->my + 1) * BLOCK_SIZE - var->ry) / fabs(var->dy);
	var->info = NULL;
	var->hit = 0;
	var->cub = cub;
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
	var->rx += var->next_x * var->dx;
	var->ry += var->next_x * var->dy;
	var->next_y -= var->next_x;
	var->next_x = var->delta_dist_x * BLOCK_SIZE;
	var->mx += var->step_x;
	var->info->direction = EAST;
	if (var->step_x < 0)
		var->info->direction = WEST;
}

void	update_ray_hit_vertical(t_ray_info_var *var)
{
	var->rx += var->next_y * var->dx;
	var->ry += var->next_y * var->dy;
	var->next_x -= var->next_y;
	var->next_y = var->delta_dist_y * BLOCK_SIZE;
	var->my += var->step_y;
	var->info->direction = SOUTH;
	if (var->step_y < 0)
		var->info->direction = NORTH;
}
