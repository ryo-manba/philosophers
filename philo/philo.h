/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmatsuka <rmatsuka@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/07 11:46:25 by rmatsuka          #+#    #+#             */
/*   Updated: 2021/07/24 09:53:40 by rmatsuka         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <pthread.h>
# include <stdbool.h>
# include <limits.h>
# include <sys/time.h>

typedef enum e_status {
	TYPE_FORK,
	TYPE_EAT,
	TYPE_SLEEP,
	TYPE_THINK,
	TYPE_DIE,
	TYPE_EAT_MAX,
}	t_status;

typedef struct s_info
{
	int					nb_philo;
	int					time_sleep;
	int					time_eat;
	int					time_die;
	int					eat_max;
	int					eat_total;
	bool				err_check;
	bool				alive;
	struct s_philo		*philo;
	pthread_mutex_t		*forks;
	pthread_mutex_t		print;
	pthread_mutex_t		check;
}	t_info;

typedef struct s_philo
{
	int					id;
	int					left;
	int					right;
	int					eat_cnt;
	long				eat_last;
	t_info				*info;
	pthread_t			thread;
}	t_philo;

/* actions */
bool	actions(t_philo *p);
bool	do_eat(t_philo *p);
bool	do_take_fork(t_philo *p);
bool	do_sleep_and_think(t_philo *p);
bool	do_sleep(int time);

/* init */
bool	init_info(int argc, char **argv, t_info *info);
bool	init_philosophers(t_info *info);

/* routine */
void	*monitor(void *p);
void	*main_routine(void *p);
void	one_philo(t_info *info);
void	sub_routine(t_philo *p);
bool	start_dining(t_info *info);

/* utils1 */
int		ft_atoi(char *s);
int		ft_isdigit(char c);
int		ft_isspace(char c);
size_t	ft_strlen(char *s);

/* utils2 */
long	get_time(void);
bool	check_args(int argc, char **argv);
bool	check_number(char *s);
bool	check_cnt_and_update_time(t_philo *p);
bool	put_action_and_check_cnt(t_philo *p, int type);

#endif
