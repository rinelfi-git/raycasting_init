/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tramanan <tramanan@student.42antananarivo> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/06 16:12:53 by tramanan          #+#    #+#             */
/*   Updated: 2025/02/26 15:56:59 by tramanan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "tools.h"

char	*cpy_word(char *s, char c)
{
	char	*res;
	int		i;
	int		j;
	int		k;

	i = 0;
	j = 0;
	k = 0;
	while (s[i] && (s[i] == c))
		i++;
	while (s[i + j] && s[i + j] != c)
		j++;
	res = (char *) malloc (sizeof(char) * (j + 1));
	if (!res)
		return (NULL);
	while (k < j)
	{
		res[k] = s[i + k];
		k++;
	}
	res[k] = '\0';
	return (res);
}

int	count_words(char *s, char c)
{
	int	word;

	word = 0;
	while (*s)
	{
		if (*s != c)
		{
			word++;
			while (*s && *s != c)
				s++;
		}
		else if (*s == c)
			s++;
	}
	return (word);
}

char	**ft_split(char *s, char c)
{
	char	**res;
	int		i;
	int		j;

	i = 0;
	j = 0;
	res = (char **) malloc(sizeof(char *) * (count_words(s, c) + 1));
	if (!res)
		return (NULL);
	while (i < count_words(s, c))
	{
		while (s[j] == c)
			j++;
		res[i] = cpy_word(s + j, c);
		if (!res[i])
		{
			free_tab(res, i);
			return (NULL);
		}
		while (s[j] && s[j] != c)
			j++;
		i++;
	}
	res[i] = NULL;
	return (res);
}
