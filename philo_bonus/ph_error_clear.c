/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ph_error_clear.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmatsuka < rmatsuka@student.42tokyo.jp>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/16 14:18:03 by rmatsuka          #+#    #+#             */
/*   Updated: 2021/07/23 10:21:52 by rmatsuka         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

void	put_error_exit(t_info *info, int type)
{
	if (type == ERROR_MALLOC)
		printf("Malloc error\n");
	if (type == ERROR_FORK)
		printf("Fork error\n");
	if (type == ERROR_FATAL)
		printf("Fatal error\n");
	all_clear(info);
	exit(1);
}

void	all_clear(t_info *info)
{
	int	i;

	i = 0;
	while (i < info->nb_philo)
	{
		if (info->is_child)
			kill(info->philo[i].pid, SIGKILL);
		sem_unlink(info->philo[i].sem_name);
		sem_close(info->philo[i].sem);
		free(info->philo[i].sem_name);
		i++;
	}
	if (info->eat_max != -1)
		kill(info->pid_check, SIGKILL);
	free(info->philo);
	sem_unlink("/eat");
	sem_unlink("/forks");
	sem_unlink("/print");
	sem_close(info->eat);
	sem_close(info->forks);
	sem_close(info->print);
}
