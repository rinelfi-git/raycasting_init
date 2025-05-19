/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tramanan <tramanan@student.42antananarivo> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/19 17:33:04 by tramanan          #+#    #+#             */
/*   Updated: 2024/08/20 16:44:14 by tramanan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

size_t	ft_strlen(char *s)
{
	size_t	i;

	i = 0;
	if (s == NULL)
		return (0);
	while (s[i])
	{
		if (s[i] == '\n')
			return (i + 1);
		i++;
	}
	return (i);
}

void	takerest(char *buff, char *rest)
{
	int		i;
	int		j;
	int		len;

	i = 0;
	j = 0;
	len = ft_strlen(buff);
	while (buff[i])
		i++;
	if ((i - len) == j)
	{
		set_zeros(rest, BUFFER_SIZE);
		return ;
	}
	while ((i - len) > j)
	{
		rest[j] = buff[len + j];
		j++;
	}
	rest[j] = '\0';
}

int	ft_strchr(char *s)
{
	int	i;

	i = 0;
	if (!s)
		return (0);
	while (s[i])
	{
		if (s[i] == '\n')
			return (1);
		i++;
	}
	return (0);
}

char	*ft_strdup(char *s)
{
	char	*dest;
	int		i;
	int		l_src;

	l_src = ft_strlen(s);
	i = 0;
	dest = (char *)malloc (sizeof(char) *(l_src + 1));
	if (!dest)
		return (NULL);
	while (l_src > i)
	{
		dest[i] = s[i];
		i++;
	}
	dest[i] = '\0';
	return (dest);
}

char	*ft_strjoin(char *s1, char *s2)
{
	unsigned int	i;
	unsigned int	l_s1;
	unsigned int	l_s2;
	char			*dest;

	i = 0;
	l_s1 = ft_strlen(s1);
	l_s2 = ft_strlen(s2);
	dest = (char *)malloc(sizeof(char) * (l_s1 + l_s2 + 1));
	if (!dest)
		return (NULL);
	dest[l_s1 + l_s2] = '\0';
	while (s1[i])
	{
		dest[i] = s1[i];
		i++;
	}
	while (l_s2 > 0)
	{
		dest[i + l_s2 - 1] = s2[l_s2 - 1];
		l_s2--;
	}
	return (dest);
}
