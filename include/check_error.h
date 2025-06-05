/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_error.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: erijania <erijania@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/02 14:40:25 by tramanan          #+#    #+#             */
/*   Updated: 2025/06/05 15:32:13 by erijania         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CHECK_ERROR_H
# define CHECK_ERROR_H

# include "tools.h"
# include "get_next_line.h"

void	arg_error(int ac, char **av);
void	check_map(char ***map, int size, int len);

int		tk_color(char *line, int *color);
int		tk_map(char *line, int fd, char ***map);
int		tk_texture(char *texture, char **buffer);
int		valid_name(char *name);

#endif // !CHECK_ERROR_H
