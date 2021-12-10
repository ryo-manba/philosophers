/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmatsuka < rmatsuka@student.42tokyo.jp>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/19 09:59:04 by rmatsuka          #+#    #+#             */
/*   Updated: 2021/07/23 14:43:20 by rmatsuka         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static void	print_usage(void)
{
	printf(""
		"Usage: ./philo 1 2 3 4 [5]\n"
		"  1 - number of philosophers\n"
		"  2 - time to die\n"
		"  3 - time to eat\n"
		"  4 - time to sleep\n"
		"  5 - number of times each philosopher must eat\n");
}

static bool	all_clear(t_info *info)
{
	bool	check;

	check = info->err_check;
	if (pthread_mutex_destroy(info->forks))
		check = false;
	if (pthread_mutex_destroy(&info->print))
		check = false;
	if (pthread_mutex_destroy(&info->check))
		check = false;
	free(info->forks);
	free(info->philo);
	return (check);
}

int	main(int argc, char **argv)
{
	t_info	info;

	if (!check_args(argc, argv))
	{
		print_usage();
		return (1);
	}
	if (!init_info(argc, argv, &info))
	{
		printf("Init error\n");
		return (1);
	}
	if (info.nb_philo == 1)
		one_philo(&info);
	else
		start_dining(&info);
	if (!all_clear(&info))
	{
		printf("Fatal error\n");
		return (1);
	}
	return (0);
}
