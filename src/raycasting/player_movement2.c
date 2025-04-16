/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player_movement2.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: erijania <erijania@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/15 23:14:28 by erijania          #+#    #+#             */
/*   Updated: 2025/04/16 11:14:01 by erijania         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "raycast.h"

void	turn_left(t_player *player)
{
	player->angle -= TURN_STEP;
	if (player->angle < 0)
		player->angle += PI * 2;
}

void	turn_right(t_player *player)
{
	player->angle += TURN_STEP;
	if (player->angle > PI * 2)
		player->angle -= PI * 2;
}
