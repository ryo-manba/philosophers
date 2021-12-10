/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ph_utils1.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmatsuka <rmatsuka@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/09 10:47:48 by rmatsuka          #+#    #+#             */
/*   Updated: 2021/07/19 09:51:02 by rmatsuka         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	ft_atoi(char *s)
{
	long	n;
	int		sign;

	n = 0;
	sign = 1;
	while (ft_isspace(*s))
		s++;
	if (*s == '+' || *s == '-')
	{
		if (*s++ == '-')
			sign = -1;
	}
	while (ft_isdigit(*s))
	{
		n = n * 10 + (*s - '0');
		s++;
	}
	return (n * sign);
}

int	ft_isdigit(char c)
{
	return ('0' <= c && c <= '9');
}

int	ft_isspace(char c)
{
	if (c == ' ')
		return (1);
	if (c == '\n')
		return (1);
	if (c == '\t')
		return (1);
	if (c == '\r')
		return (1);
	if (c == '\v')
		return (1);
	if (c == '\f')
		return (1);
	return (0);
}

size_t	ft_strlen(char *s)
{
	size_t	i;

	i = 0;
	while (s[i])
		i++;
	return (i);
}
