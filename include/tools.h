/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tools.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: erijania <erijania@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/30 10:29:09 by tramanan          #+#    #+#             */
/*   Updated: 2025/06/05 14:36:19 by erijania         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TOOLS_H
# define TOOLS_H

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

int		checkchar(char *str, char c);
int		count_len(char *s);
int		count_words(char *s, char c);
int		empty_line(char *line);
int		ft_atoi(char *str);
int		ft_isdigit(char c);
int		ft_lstsize(t_map *line);
int		ft_memcmp(char *s1, char *s2);
int		ft_tabsize(char **src);
int		is_id_valid(char *s1, char *s2, int n);
int		is_nb_valid(char **res, int len);
int		map_error(char *line, t_map **lst);
int		set_len(t_map *lst);
int		skipe(char *str, int i);

char	*cpy_word(char *s, char c);
char	*ft_strcpy(char *s, int l_src);
char	**ft_split(char *s, char c);
char	**map_dup(char **map);

t_map	*new_line(char *line);
#endif
