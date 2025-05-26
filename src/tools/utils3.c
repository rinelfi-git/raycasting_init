/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils3.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: erijania <erijania@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/23 21:00:26 by erijania          #+#    #+#             */
/*   Updated: 2025/05/23 21:25:40 by erijania         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "tools.h"

void	config_file_error(int code)
{
	char	*msg[5];

	msg[0] = "Allowed texture config: ID path/to/image.xpm\n";
	msg[1] = "Allowed color config: ID [0-255],[0-255],[0-255]\n";
	msg[2] = "Map configuration error\n";
	msg[3] = "Player configuration error\n";
	msg[4] = "Unknown ID\n";
	ft_putstr_fd("Error\n", 2);
	ft_putstr_fd(msg[code - 1], 2);
}
