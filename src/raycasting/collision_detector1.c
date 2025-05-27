/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   collision_detector1.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: erijania <erijania@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/15 23:16:42 by erijania          #+#    #+#             */
/*   Updated: 2025/05/27 19:58:58 by erijania         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "raycast.h"

void	check_hurt_up(t_will_hurt_var *var, t_player *player)
{
	var->map_y = (int)roundf(player->y - var->dy * (MOVE_STEP * + 5));
	var->map_x = (int)roundf(player->x - var->dx * (MOVE_STEP * + 5));
}

void	check_hurt_down(t_will_hurt_var *var, t_player *player)
{
	var->map_y = (int)roundf(player->y + var->dy * (MOVE_STEP * + 5));
	var->map_x = (int)roundf(player->x + var->dx * (MOVE_STEP * + 5));
}

void	check_hurt_left(t_will_hurt_var *var, t_player *player)
{
	var->map_y = (int)roundf(player->y + var->dx * (MOVE_STEP * + 5));
	var->map_x = (int)roundf(player->x - var->dy * (MOVE_STEP * + 5));
}

void	check_hurt_right(t_will_hurt_var *var, t_player *player)
{
	var->map_y = (int)roundf(player->y - var->dy * (MOVE_STEP * + 5));
	var->map_x = (int)roundf(player->x + var->dx * (MOVE_STEP * + 5));
}
