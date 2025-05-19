/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: erijania <erijania@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/19 21:33:35 by erijania          #+#    #+#             */
/*   Updated: 2025/05/19 21:38:34 by erijania         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "tools.h"
#include "get_next_line.h"
#include <stdlib.h>

char	**map_dup(char **map)
{
	int		size;
	char	**out;
	int		i;

	size = ft_tabsize(map);
	out = (char **)malloc(sizeof(char *) * (size + 1));
	if (!out)
		return (NULL);
	i = 0;
	while (i < size)
	{
		out[i] = ft_strcpy(map[i], ft_strlen(map[i]));
		i++;
	}
	out[i] = NULL;
	return (out);
}
