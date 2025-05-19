/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tramanan <tramanan@student.42antananarivo> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/19 17:32:49 by tramanan          #+#    #+#             */
/*   Updated: 2024/08/21 17:16:37 by tramanan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 42
# endif

# include <unistd.h>
# include <stdlib.h>
# include <fcntl.h>

void	set_zeros(char *s, size_t n);
void	takerest(char *buff, char *rest);
int		ft_strchr(char *s);
size_t	ft_strlen(char *s);
char	*ft_strdup(char *s);
char	*get_next_line(int fd);
char	*ft_strjoin(char *s1, char *s2);
char	*the_next_line(char *s1, char *s2);
char	*ft_calloc(size_t nmemb, size_t size);

#endif
