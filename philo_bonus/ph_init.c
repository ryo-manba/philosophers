/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ph_init.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmatsuka < rmatsuka@student.42tokyo.jp>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/23 09:28:32 by rmatsuka          #+#    #+#             */
/*   Updated: 2021/07/23 15:21:45 by rmatsuka         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

void	init_philosophers(t_info *info)
{
	int	i;

	i = 0;
	while (i < info->nb_philo)
	{
		info->philo[i].info = info;
		info->philo[i].id = i + 1;
		info->philo[i].eat_cnt = 0;
		info->philo[i].eat_last = 0;
		info->philo[i].sem_name = ph_itoa(i);
		if (!info->philo[i].sem_name)
			put_error_exit(info, ERROR_MALLOC);
		sem_unlink(info->philo[i].sem_name);
		info->philo[i].sem = sem_open(info->philo[i].sem_name,
				O_CREAT, S_IRWXU, 1);
		i++;
	}
}

void	init_info(int argc, char **argv, t_info *info)
{
	info->is_child = true;
	info->pid_check = 0;
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
		put_error_exit(info, ERROR_MALLOC);
	sem_unlink("/eat");
	sem_unlink("/forks");
	sem_unlink("/print");
	info->eat = sem_open("/eat", O_CREAT, S_IRWXU, 0);
	info->forks = sem_open("/forks", O_CREAT, S_IRWXU, info->nb_philo);
	info->print = sem_open("/print", O_CREAT, S_IRWXU, 1);
}
