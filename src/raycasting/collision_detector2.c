/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   collision_detector2.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: erijania <erijania@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/15 23:16:42 by erijania          #+#    #+#             */
/*   Updated: 2025/05/27 20:05:58 by erijania         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "raycast.h"

void	check_hurt_up(t_will_hurt_var *var, t_player *player);
void	check_hurt_down(t_will_hurt_var *var, t_player *player);
void	check_hurt_left(t_will_hurt_var *var, t_player *player);
void	check_hurt_right(t_will_hurt_var *var, t_player *player);

void	init_will_hurt_var(t_will_hurt_var *var, t_player *player)
{
	var->map_x = -1;
	var->map_y = -1;
	var->dx = player->delta_x * MOVE_STEP;
	var->dy = player->delta_y * MOVE_STEP;
}

int	player_will_hurt_wall(t_cub3d *pro, char dir)
{
	t_will_hurt_var	var;

	init_will_hurt_var(&var, pro->player);
	if (dir == MOVE_UP)
		check_hurt_up(&var, pro->player);
	else if (dir == MOVE_DOWN)
		check_hurt_down(&var, pro->player);
	else if (dir == MOVE_LEFT)
		check_hurt_left(&var, pro->player);
	else if (dir == MOVE_RIGHT)
		check_hurt_right(&var, pro->player);
	if (var.map_x >= 0 && var.map_y >= 0)
		return (pro->map[var.map_y / BLOCK_SIZE][var.map_x
			/ BLOCK_SIZE] == '1');
	return (1);
}
