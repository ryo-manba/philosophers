/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_bonus.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmatsuka < rmatsuka@student.42tokyo.jp>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/18 10:38:20 by rmatsuka          #+#    #+#             */
/*   Updated: 2021/07/23 17:00:54 by rmatsuka         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_BONUS_H
# define PHILO_BONUS_H

# include <stdio.h>
# include <stdlib.h>
# include <sys/time.h>
# include <unistd.h>
# include <pthread.h>
# include <limits.h>
# include <stdbool.h>
# include <signal.h>
# include <semaphore.h>
# include <fcntl.h>
# include <sys/wait.h>

typedef enum e_status
{
	TYPE_FORK,
	TYPE_EAT,
	TYPE_SLEEP,
	TYPE_THINK,
	TYPE_DIE,
	TYPE_EAT_MAX,
}	t_status;

typedef enum e_error
{
	ERROR_MALLOC,
	ERROR_FATAL,
	ERROR_FORK
}	t_error;

typedef struct s_info
{
	int				nb_philo;
	int				time_eat;
	int				time_die;
	int				time_sleep;
	int				eat_max;
	bool			is_child;
	sem_t			*forks;
	sem_t			*print;
	sem_t			*eat;
	pid_t			pid_check;
	struct s_philo	*philo;
}	t_info;

typedef struct s_philo
{
	int			id;
	int			eat_cnt;
	long		eat_last;
	char		*sem_name;
	pid_t		pid;
	sem_t		*sem;
	t_info		*info;
	pthread_t	thread;
}	t_philo;

/* actions */
bool	actions(t_philo *philo);
bool	do_sleep(int time);
bool	do_eat(t_philo *philo);
bool	do_take_fork(t_philo *philo);
bool	do_sleep_and_think(t_philo *philo);

/* init */
void	init_philosophers(t_info *info);
void	init_info(int argc, char **argv, t_info *info);

/*error_clear */
void	all_clear(t_info *info);
void	put_error_exit(t_info *info, int type);

/* routine */
void	*monitor(void *p);
void	wait_child(t_info *info);
void	main_routine(t_philo *philo);
void	start_dining(t_info *info);
void	eat_cnt_monitor(t_info *info);

/* utils1 */
int		ft_atoi(char *s);
int		ft_isdigit(char c);
int		ft_isspace(char c);
size_t	ft_strlen(char *s);
char	*ph_itoa(int n);

/* utils2 */
long	get_time(void);
bool	check_number(char *s);
bool	check_cnt_and_update_time(t_philo *philo);
bool	check_args(int argc, char **argv);
bool	put_action_and_check_cnt(t_philo *philo, int type);

#endif
