/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ph_actions.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmatsuka < rmatsuka@student.42tokyo.jp>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/14 17:46:58 by rmatsuka          #+#    #+#             */
/*   Updated: 2021/07/23 13:49:45 by rmatsuka         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

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

bool	do_take_fork(t_philo *p)
{
	pthread_mutex_lock(&p->info->forks[p->right]);
	if (!put_action_and_check_cnt(p, TYPE_FORK))
		return (false);
	pthread_mutex_lock(&p->info->forks[p->left]);
	if (!put_action_and_check_cnt(p, TYPE_FORK))
		return (false);
	return (true);
}

bool	do_eat(t_philo *p)
{
	put_action_and_check_cnt(p, TYPE_EAT);
	if (!do_sleep(p->info->time_eat))
		return (false);
	pthread_mutex_unlock(&p->info->forks[p->right]);
	pthread_mutex_unlock(&p->info->forks[p->left]);
	return (true);
}

bool	do_sleep_and_think(t_philo *p)
{
	if (!put_action_and_check_cnt(p, TYPE_SLEEP))
		return (false);
	if (!do_sleep(p->info->time_sleep))
		return (false);
	if (!put_action_and_check_cnt(p, TYPE_THINK))
		return (false);
	return (true);
}

bool	actions(t_philo *p)
{
	if (!do_take_fork(p))
		return (false);
	if (!do_eat(p))
		return (false);
	if (!do_sleep_and_think(p))
		return (false);
	return (true);
}
