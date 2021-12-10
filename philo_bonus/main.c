/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmatsuka < rmatsuka@student.42tokyo.jp>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/19 09:48:34 by rmatsuka          #+#    #+#             */
/*   Updated: 2021/07/23 09:37:19 by rmatsuka         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

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

int	main(int argc, char **argv)
{
	t_info	info;

	if (!check_args(argc, argv))
	{
		print_usage();
		return (1);
	}
	init_info(argc, argv, &info);
	init_philosophers(&info);
	start_dining(&info);
	all_clear(&info);
	return (0);
}
