/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ph_init.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmatsuka < rmatsuka@student.42tokyo.jp>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/18 11:34:35 by rmatsuka          #+#    #+#             */
/*   Updated: 2021/07/23 15:08:01 by rmatsuka         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

bool	init_philosophers(t_info *info)
{
	int	i;

	i = 0;
	while (i < info->nb_philo)
	{
		info->philo[i].info = info;
		if (pthread_mutex_init(&info->forks[i], NULL))
			return (false);
		info->philo[i].left = i;
		info->philo[i].right = (i - 1 + info->nb_philo) % info->nb_philo;
		info->philo[i].id = i + 1;
		info->philo[i].eat_cnt = 0;
		info->philo[i].eat_last = 0;
		i++;
	}
	return (true);
}

bool	init_info(int argc, char **argv, t_info *info)
{
	info->alive = true;
	info->err_check = true;
	info->eat_total = 0;
	info->nb_philo = ft_atoi(argv[1]);
	info->time_die = ft_atoi(argv[2]);
	info->time_eat = ft_atoi(argv[3]);
	info->time_sleep = ft_atoi(argv[4]);
	if (argc == 6)
		info->eat_max = ft_atoi(argv[5]);
	else
		info->eat_max = -1;
	info->philo = malloc(sizeof(t_philo) * info->nb_philo);
	if (!info->philo)
		return (false);
	info->forks = malloc(sizeof(pthread_mutex_t) * info->nb_philo);
	if (!info->forks)
		return (false);
	if (pthread_mutex_init(&info->print, NULL)
		|| pthread_mutex_init(&info->check, NULL))
		return (false);
	if (!init_philosophers(info))
		return (false);
	return (true);
}
