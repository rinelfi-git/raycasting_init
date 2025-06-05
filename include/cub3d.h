/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tramanan <tramanan@student.42antananarivo  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/02 14:34:26 by tramanan          #+#    #+#             */
/*   Updated: 2025/06/03 00:34:06 by tramanan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# include <unistd.h>
# include <stdlib.h>

# include "tools.h"
# include "check_error.h"

typedef struct s_data
{
	char	*north;
	char	*south;
	char	*weast;
	char	*east;
	int		f;
	int		c;
	char	**map;
}			t_data;

void	free_data(t_data *data);

int		valid_file(char *path, t_data *data);
int		check_file(int fd, char *line, t_data *data);
#endif // !CUB3D_H
