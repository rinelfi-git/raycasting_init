/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   collision_detector1.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: erijania <erijania@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/15 23:16:42 by erijania          #+#    #+#             */
/*   Updated: 2025/05/28 15:02:27 by erijania         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "raycast.h"

void	check_hurt_up(t_will_hurt_var *var, t_player *player)
{
	var->map_y = player->y - (int)roundf(var->dy * (MOVE_STEP * 2));
	var->map_x = player->x - (int)roundf(var->dx * (MOVE_STEP * 2));
}

void	check_hurt_down(t_will_hurt_var *var, t_player *player)
{
	var->map_y = player->y + (int)roundf(var->dy * (MOVE_STEP * 2));
	var->map_x = player->x + (int)roundf(var->dx * (MOVE_STEP * 2));
}

void	check_hurt_left(t_will_hurt_var *var, t_player *player)
{
	var->map_y = player->y + (int)roundf(var->dx * (MOVE_STEP * 2));
	var->map_x = player->x - (int)roundf(var->dy * (MOVE_STEP * 2));
}

void	check_hurt_right(t_will_hurt_var *var, t_player *player)
{
	var->map_y = player->y - (int)roundf(var->dx * (MOVE_STEP * 2));
	var->map_x = player->x + (int)roundf(var->dy * (MOVE_STEP * 2));
}
