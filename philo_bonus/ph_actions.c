/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ph_actions.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmatsuka < rmatsuka@student.42tokyo.jp>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/14 17:46:58 by rmatsuka          #+#    #+#             */
/*   Updated: 2021/07/23 15:44:29 by rmatsuka         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

bool	actions(t_philo *philo)
{
	if (!do_take_fork(philo))
		return (false);
	if (!do_eat(philo))
		return (false);
	if (!do_sleep_and_think(philo))
		return (false);
	return (true);
}

bool	do_sleep(int time)
{
	long	end_time;

	end_time = get_time();
	if (end_time == -1)
		return (false);
	end_time += time;
	while (get_time() < end_time)
		usleep(1000);
	return (true);
}

bool	do_take_fork(t_philo *philo)
{
	if (philo->id % 2)
		usleep(200);
	if (sem_wait(philo->info->forks))
		return (false);
	put_action_and_check_cnt(philo, TYPE_FORK);
	if (sem_wait(philo->info->forks))
		return (false);
	put_action_and_check_cnt(philo, TYPE_FORK);
	return (true);
}

bool	do_eat(t_philo *philo)
{
	put_action_and_check_cnt(philo, TYPE_EAT);
	if (!do_sleep(philo->info->time_eat))
		return (false);
	sem_post(philo->info->forks);
	sem_post(philo->info->forks);
	return (true);
}

bool	do_sleep_and_think(t_philo *philo)
{
	if (!put_action_and_check_cnt(philo, TYPE_SLEEP))
		return (false);
	if (!do_sleep(philo->info->time_sleep))
		return (false);
	if (!put_action_and_check_cnt(philo, TYPE_THINK))
		return (false);
	return (true);
}
