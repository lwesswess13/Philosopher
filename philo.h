/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbouchib <sbouchib@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/13 09:21:27 by sbouchib          #+#    #+#             */
/*   Updated: 2026/05/13 09:21:28 by sbouchib         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <pthread.h>
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <sys/time.h>
# include <stdbool.h>
# include <limits.h>

struct	s_data;

typedef struct s_philo
{
	int				id;
	int				eat_count;
	long long		last_meal_time;
	pthread_t		thread;
	pthread_mutex_t	*left_fork;
	pthread_mutex_t	*right_fork;
	struct s_data	*data;
}	t_philo;

typedef struct s_data
{
	int				nb_philos;
	long long		time_to_die;
	long long		time_to_eat;
	long long		time_to_sleep;
	int				nb_meals;
	long long		start_time;
	bool			dead;
	bool			all_ate;
	pthread_mutex_t	*forks;
	pthread_mutex_t	print_mutex;
	pthread_mutex_t	dead_mutex;
	pthread_mutex_t	meal_mutex;
	t_philo			*philos;
}	t_data;

// utils.c
long long	get_time_in_ms(void);
void		ft_usleep(long long time_in_ms, t_data *data);
void		print_action(t_philo *philo, char *str);
int			ft_atoi(const char *str);

// init.c
int			init_data(t_data *data, int argc, char **argv);
int			init_philos(t_data *data);
void		free_all(t_data *data);

// routine.c
void		*philo_routine(void *arg);

// monitor.c
void		*monitor_routine(void *arg);

#endif
