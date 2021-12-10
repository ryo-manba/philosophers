/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ph_routines.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmatsuka < rmatsuka@student.42tokyo.jp>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/16 14:57:24 by rmatsuka          #+#    #+#             */
/*   Updated: 2021/07/23 15:20:11 by rmatsuka         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

void	eat_cnt_monitor(t_info *info)
{
	int	i;

	i = 0;
	while (i < info->nb_philo)
	{
		sem_wait(info->eat);
		i++;
	}
	put_action_and_check_cnt(info->philo, TYPE_EAT_MAX);
}

void	*monitor(void *p)
{
	t_philo	*philo;
	long	now;

	philo = (t_philo *)p;
	while (1)
	{
		now = get_time();
		if (now == -1)
			exit(1);
		sem_wait(philo->sem);
		if (now - philo->eat_last >= philo->info->time_die)
			put_action_and_check_cnt(philo, TYPE_DIE);
		sem_post(philo->sem);
		usleep(200);
	}
	return (NULL);
}

void	wait_child(t_info *info)
{
	int	i;
	int	status;

	while (1)
	{
		waitpid(-1, &status, 0);
		if (WEXITSTATUS(status) == 42)
			break ;
		if (WEXITSTATUS(status) == 1)
			put_error_exit(info, ERROR_FATAL);
	}
	i = 0;
	while (i < info->nb_philo)
	{
		kill(info->philo[i].pid, SIGKILL);
		i++;
	}
	info->is_child = false;
}

void	start_dining(t_info *info)
{
	int		i;

	i = 0;
	while (i < info->nb_philo)
	{
		info->philo[i].pid = fork();
		if (info->philo[i].pid == -1)
			put_error_exit(info, ERROR_FORK);
		if (info->philo[i].pid == 0)
			main_routine(&(info->philo[i]));
		i++;
	}
	if (info->eat_max != -1)
	{
		info->pid_check = fork();
		if (info->pid_check == -1)
			put_error_exit(info, ERROR_FORK);
		if (info->pid_check == 0)
			eat_cnt_monitor(info);
	}
	wait_child(info);
}

void	main_routine(t_philo *philo)
{
	if (philo->id % 2)
		usleep(200);
	philo->eat_last = get_time();
	pthread_create(&philo->thread, NULL, monitor, philo);
	pthread_detach(philo->thread);
	while (1)
	{
		if (!actions(philo))
			exit(1);
	}
}
