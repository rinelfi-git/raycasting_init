/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tools.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: erijania <erijania@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/30 10:29:09 by tramanan          #+#    #+#             */
/*   Updated: 2025/05/31 21:27:54 by erijania         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TOOLS_H
# define TOOLS_H

# include "raycast.h"
# include "cub_types.h"
# include "check_error.h"
# include "cub3d.h"

typedef struct s_map
{
	char			*line;
	int				count;
	struct s_map	*next;
}					t_map;

void	free_list(t_map *lst);
void	free_tab(char	**tab, int i);
void	ft_putstr_fd(char *str, int fd);
void	ft_addback(t_map **map, t_map *line);

int		data_ok(t_data *data);
int		set_len(t_map *lst);
int		map_error(char *line, t_map **lst);
int		ft_lstsize(t_map *line);
int		ft_atoi(char *str);
int		tk_color(char *line, int *color);
int		skipe(char *str, int i);
int		ft_tabsize(char **src);
int		ft_isdigit(char c);
int		count_len(char *s);
int		ft_strncmp(char *s1, char *s2, int n);
int		count_words(char *s, char c);

char	*cpy_word(char *s, char c);
char	**ft_split(char *s, char c);
char	*ft_strcpy(char *s, int l_src);

t_map	*new_line(char *line);
char	**map_dup(char **map);
void	config_file_error(int code);
#endif
