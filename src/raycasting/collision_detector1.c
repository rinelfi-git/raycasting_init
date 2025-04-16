/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   collision_detector1.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: erijania <erijania@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/15 23:16:42 by erijania          #+#    #+#             */
/*   Updated: 2025/04/16 11:14:34 by erijania         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "raycast.h"

void	check_hurt_up(t_will_hurt_var *var, t_player *player)
{
	var->map_y = (int)roundf(player->y - var->dy);
	var->map_x = (int)roundf(player->x - var->dx);
}

void	check_hurt_down(t_will_hurt_var *var, t_player *player)
{
	var->map_y = (int)roundf(player->y + var->dy);
	var->map_x = (int)roundf(player->x + var->dx);
}

void	check_hurt_left(t_will_hurt_var *var, t_player *player)
{
	var->map_y = (int)roundf(player->y + var->dx);
	var->map_x = (int)roundf(player->x - var->dy);
}

void	check_hurt_right(t_will_hurt_var *var, t_player *player)
{
	var->map_y = (int)roundf(player->y - var->dy);
	var->map_x = (int)roundf(player->x + var->dx);
}
