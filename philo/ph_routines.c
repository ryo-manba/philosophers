/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ph_routines.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmatsuka < rmatsuka@student.42tokyo.jp>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/16 14:57:24 by rmatsuka          #+#    #+#             */
/*   Updated: 2021/07/23 16:42:43 by rmatsuka         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

bool	start_dining(t_info *info)
{
	int	i;

	i = 0;
	while (i < info->nb_philo)
	{
		if (pthread_create(&info->philo[i].thread,
				NULL, main_routine, &info->philo[i]))
			return (false);
		i++;
	}
	i = 0;
	while (i < info->nb_philo)
	{
		if (pthread_join(info->philo[i].thread, NULL))
			return (false);
		i++;
	}
	pthread_mutex_lock(&info->check);
	if (!info->err_check)
	{
		pthread_mutex_unlock(&info->check);
		return (false);
	}
	pthread_mutex_unlock(&info->check);
	return (true);
}

void	*monitor(void *p)
{
	t_philo	*philo;
	long	now;

	philo = (t_philo *)p;
	while (1)
	{
		pthread_mutex_lock(&philo->info->check);
		if (philo->info->alive == false)
			break ;
		now = get_time();
		if (now == -1)
		{
			philo->info->err_check = false;
			break ;
		}
		if (now - philo->eat_last >= philo->info->time_die)
		{
			put_action_and_check_cnt(philo, TYPE_DIE);
			break ;
		}
		pthread_mutex_unlock(&philo->info->check);
		usleep(200);
	}
	pthread_mutex_unlock(&philo->info->check);
	return (NULL);
}

void	*main_routine(void *p)
{
	t_philo		*philo;
	pthread_t	checker;

	philo = (t_philo *)p;
	pthread_mutex_lock(&philo->info->check);
	philo->eat_last = get_time();
	if (philo->eat_last == -1)
	{
		philo->info->err_check = false;
		pthread_mutex_unlock(&philo->info->check);
		return (NULL);
	}
	pthread_mutex_unlock(&philo->info->check);
	if (pthread_create(&checker, NULL, monitor, philo))
	{
		pthread_mutex_lock(&philo->info->check);
		philo->info->err_check = false;
		pthread_mutex_unlock(&philo->info->check);
		return (NULL);
	}
	pthread_detach(checker);
	sub_routine(philo);
	return (NULL);
}

void	sub_routine(t_philo *p)
{
	if (p->id % 2 == 0)
		usleep(500);
	while (1)
	{
		pthread_mutex_lock(&p->info->check);
		if (p->info->alive == false)
			break ;
		pthread_mutex_unlock(&p->info->check);
		if (!actions(p))
		{
			pthread_mutex_lock(&p->info->check);
			p->info->err_check = false;
			break ;
		}
	}
	pthread_mutex_unlock(&p->info->check);
}

void	one_philo(t_info *info)
{
	long	start;
	long	end;

	start = get_time();
	if (start == -1)
	{
		info->err_check = false;
		return ;
	}
	printf("%ld %d has taken a fork\n", start, info->philo->id);
	if (!do_sleep(info->time_die))
	{
		info->err_check = false;
		return ;
	}
	end = get_time();
	if (end == -1)
	{
		info->err_check = false;
		return ;
	}
	printf("%ld %d died\n", end, info->philo->id);
}
