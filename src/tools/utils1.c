/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils1.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: erijania <erijania@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/30 10:28:40 by tramanan          #+#    #+#             */
/*   Updated: 2025/06/05 15:30:37 by erijania         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "tools.h"

int	ft_isdigit(char c)
{
	if (c < 48 || c > 57)
		return (0);
	return (2048);
}

int	skipe(char *str, int i)
{
	if (!str)
		return (i);
	if (str[i] != ' ' && str[i] != '\t')
		return (i);
	while (str[i] && (str[i] == ' ' || str[i] == '\t'))
		i++;
	return (i);
}

int	is_id_valid(char *s1, char *s2, int n)
{
	int	i;

	if (n <= 0 || !s1 || !s2)
		return (0);
	i = 0;
	while (i < n && s1[i] && s2[i])
	{
		if (s1[i] != s2[i])
			return (0);
		i++;
	}
	if (s2[i] == '\0' || s2[i] == '\n')
		return (0);
	if (n == i)
		return (1);
	return (0);
}

void	ft_putstr_fd(char *str, int fd)
{
	int	i;

	i = 0;
	while (str[i])
	{
		(void)!write(fd, &str[i], 1);
		i++;
	}
}

int	ft_atoi(char *str)
{
	int	i;
	int	nb;

	i = 0;
	nb = 0;
	if (!str)
		return (-1);
	if (str[i] == '+' || str[i] == '-')
		return (-1);
	while (ft_isdigit(str[i]))
	{
		nb = nb * 10 + str[i] - '0';
		if (nb > 255)
			return (-1);
		i++;
	}
	return (nb);
}
