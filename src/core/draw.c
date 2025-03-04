/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: erijania <erijania@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/03 10:15:19 by erijania          #+#    #+#             */
/*   Updated: 2025/03/04 22:50:05 by erijania         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "raycast.h"
#include <math.h>

void	draw_rectangle(t_program *pro, t_minirect *form)
{
	int	i;
	int	j;

	j = form->y;
	while (j < (form->y + form->height))
	{
		i = form->x;
		while (i < (form->x + form->width))
			put_pixel_at(pro, i++, j, form->bg_color);
		j++;
	}
}

void	draw_square(t_program *prog, int x, int y, int size, int out, int bg)
{
	int	i;
	int	j;

	j = y;
	while (j <= y + size)
	{
		i = x;
		while (i <= x + size)
			if (i == x || j == y)
				put_pixel_at(prog, i++, j, out);
			else
				put_pixel_at(prog, i++, j, bg);
		j++;
	}
}

void	draw_line(t_program *prog, t_miniline *line)
{
	float	deltas[2];
	float	pixels[2];
	int		pixel;

	if (line->start_x == line->end_x && line->start_y == line->end_y)
		return ;
	deltas[0] = line->end_x - line->start_x;
	deltas[1] = line->end_y - line->start_y;
	pixel = sqrtf((deltas[0] * deltas[0]) + (deltas[1] * deltas[1]));
	deltas[0] /= pixel;
	deltas[1] /= pixel;
	pixels[0] = line->start_x;
	pixels[1] = line->start_y;
	while (pixel)
	{
		put_pixel_at(prog, pixels[0], pixels[1], line->color);
		pixels[0] += deltas[0];
		pixels[1] += deltas[1];
		--pixel;
	}
}

void	screen_clean(t_program *prog)
{
	int	i;
	int	j;

	j = 0;
	while (j <= W_HEIGHT)
	{
		i = 0;
		while (i <= W_WIDTH)
			put_pixel_at(prog, i++, j, 0x000000);
		j++;
	}
}
