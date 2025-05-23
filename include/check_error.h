/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_error.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: erijania <erijania@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/29 15:03:57 by tramanan          #+#    #+#             */
/*   Updated: 2025/05/23 19:52:01 by erijania         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CHECK_ERROR_H
# define CHECK_ERROR_H

# include "cub_types.h"
# include "get_next_line.h"

int		valid_map(char *path);
int		valid_name(char *name);
int		tk_texture(char *texture, char **buffer);
int		checkchar(char *str, char c);
int		tk_map(char *line, int fd, char ***map);

void	arg_error(void);
void	check_lock(char ***map, int size, int len);
int		init_check(t_cub3d *cub);

#endif
