/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: erijania <erijania@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/03 10:05:15 by erijania          #+#    #+#             */
/*   Updated: 2025/03/05 00:27:07 by erijania         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "raycast.h"

void	program_init(t_program *prog)
{
	void	*mlx;
	t_pix	*pix;

	mlx = mlx_init();
	pix = &(prog->pix);
	prog->mlx = mlx;
	prog->win = mlx_new_window(mlx, W_WIDTH, W_HEIGHT, "Ray casting");
	pix->img = mlx_new_image(mlx, W_WIDTH, W_HEIGHT);
	pix->addr = mlx_get_data_addr(pix->img, &pix->bits_per_pixel,
			&pix->line_length, &pix->endian);
}

int	program_clear(t_program *prog)
{
	int	i;

	if (prog->map)
	{
		i = 0;
		while (prog->map[i])
			free(prog->map[i++]);
		free(prog->map);
	}
	if (prog->win)
		mlx_destroy_window(prog->mlx, prog->win);
	mlx_destroy_display(prog->mlx);
	free(prog->mlx);
	exit(0);
	return (0);
}
