/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player_movement1.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: erijania <erijania@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/15 23:14:28 by erijania          #+#    #+#             */
/*   Updated: 2025/05/27 20:04:10 by erijania         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "raycast.h"

void	move_forward(t_player *player)
{
	player->y -= (int)roundf(player->delta_y * MOVE_STEP);
	player->x -= (int)roundf(player->delta_x * MOVE_STEP);
}

void	move_backward(t_player *player)
{
	player->y += (int)roundf(player->delta_y * MOVE_STEP);
	player->x += (int)roundf(player->delta_x * MOVE_STEP);
}

void	move_left(t_player *player)
{
	player->y += (int)roundf(player->delta_x * MOVE_STEP);
	player->x -= (int)roundf(player->delta_y * MOVE_STEP);
}

void	move_right(t_player *player)
{
	player->y -= (int)roundf(player->delta_x * MOVE_STEP);
	player->x += (int)roundf(player->delta_y * MOVE_STEP);
}
