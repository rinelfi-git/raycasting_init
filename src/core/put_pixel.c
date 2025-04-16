/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   put_pixel.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: erijania <erijania@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/03 10:21:27 by erijania          #+#    #+#             */
/*   Updated: 2025/04/16 11:08:54 by erijania         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "raycast.h"

void	put_pixel_at(t_cub3d *prog, int x, int y, int color)
{
	char	*addr;
	t_pix	*pix;

	pix = &(prog->pix);
	addr = pix->addr + (y * pix->line_length + x * (pix->bits_per_pixel / 8));
	*((unsigned int *) addr) = color;
}
