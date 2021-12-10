/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ph_utils2.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmatsuka <rmatsuka@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/16 15:01:44 by rmatsuka          #+#    #+#             */
/*   Updated: 2021/10/31 01:17:45 by rmatsuka         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

long	get_time(void)
{
	struct timeval	tp;
	long			milliseconds;

	if (gettimeofday(&tp, NULL) == -1)
		return (-1);
	milliseconds = tp.tv_sec * 1000;
	milliseconds += tp.tv_usec / 1000;
	return (milliseconds);
}

bool	check_args(int argc, char **argv)
{
	int		i;

	if (argc != 5 && argc != 6)
		return (false);
	i = 1;
	while (i < argc)
	{
		if (!check_number(argv[i]))
			return (false);
		i++;
	}
	return (true);
}

bool	check_number(char *s)
{
	long	n;
	char	*tmp;

	n = 0;
	tmp = s;
	while (ft_isspace(*tmp))
		tmp++;
	if (*tmp == '+')
		tmp++;
	if (*tmp == '-' || ft_strlen(tmp) == 0)
		return (false);
	while (ft_isdigit(*tmp))
	{
		n = n * 10 + *tmp - '0';
		if (n > INT_MAX)
			return (false);
		tmp++;
	}
	if (ft_strlen(tmp) || n == 0)
		return (false);
	return (true);
}

bool	check_cnt_and_update_time(t_philo *p)
{
	pthread_mutex_lock(&p->info->check);
	p->eat_last = get_time();
	if (p->eat_last == -1)
		return (false);
	p->eat_cnt++;
	if (p->eat_cnt == p->info->eat_max)
	{
		p->info->eat_total += 1;
		if (p->info->eat_total == p->info->nb_philo)
		{
			printf("%ld Everyone ate %d times!\n", get_time(), p->info->eat_max);
			p->info->alive = false;
		}
	}
	pthread_mutex_unlock(&p->info->check);
	return (true);
}

bool	put_action_and_check_cnt(t_philo *p, int type)
{
	pthread_mutex_lock(&p->info->print);
	if (p->info->alive)
	{
		if (type == TYPE_FORK)
			printf("%ld %d has taken a fork\n", get_time(), p->id);
		if (type == TYPE_EAT)
		{
			printf("%ld %d is eating\n", get_time(), p->id);
			if (!check_cnt_and_update_time(p))
				return (false);
		}
		if (type == TYPE_SLEEP)
			printf("%ld %d is sleeping\n", get_time(), p->id);
		if (type == TYPE_THINK)
			printf("%ld %d is thinking\n", get_time(), p->id);
		if (type == TYPE_DIE)
		{
			printf("%ld %d died\n", get_time(), p->id);
			p->info->alive = false;
		}
	}
	pthread_mutex_unlock(&p->info->print);
	return (true);
}
