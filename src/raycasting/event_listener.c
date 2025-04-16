/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   event_listener.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: erijania <erijania@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/15 23:15:02 by erijania          #+#    #+#             */
/*   Updated: 2025/04/16 11:07:54 by erijania         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "raycast.h"
#include <X11/keysym.h>

void	init_key_event(t_key_event *event)
{
	event->w = 0;
	event->d = 0;
	event->s = 0;
	event->a = 0;
	event->arrow_left = 0;
	event->arrow_right = 0;
	event->move = 1;
}

int	need_refresh(t_cub3d *pro)
{
	return (pro->key_events->w || pro->key_events->d || pro->key_events->s
		|| pro->key_events->a || pro->key_events->arrow_left
		|| pro->key_events->arrow_right);
}

int	handle_keydown(int code, void *arg)
{
	t_cub3d	*pro;

	pro = (t_cub3d *)arg;
	if (code == XK_z)
		pro->key_events->w = 1;
	if (code == XK_d)
		pro->key_events->d = 1;
	if (code == XK_s)
		pro->key_events->s = 1;
	if (code == XK_q)
		pro->key_events->a = 1;
	if (code == XK_Left)
		pro->key_events->arrow_left = 1;
	if (code == XK_Right)
		pro->key_events->arrow_right = 1;
	if (code == XK_Escape)
		return (program_clear(pro));
	pro->key_events->move = need_refresh(pro);
	return (0);
}

int	handle_keyup(int code, void *arg)
{
	t_cub3d	*pro;

	pro = (t_cub3d *)arg;
	if (code == XK_z)
		pro->key_events->w = 0;
	if (code == XK_d)
		pro->key_events->d = 0;
	if (code == XK_s)
		pro->key_events->s = 0;
	if (code == XK_q)
		pro->key_events->a = 0;
	if (code == XK_Left)
		pro->key_events->arrow_left = 0;
	if (code == XK_Right)
		pro->key_events->arrow_right = 0;
	pro->key_events->move = need_refresh(pro);
	return (0);
}
