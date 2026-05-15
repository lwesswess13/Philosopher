/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbouchib <sbouchib@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/13 09:21:20 by sbouchib          #+#    #+#             */
/*   Updated: 2026/05/15 17:34:17 by sbouchib         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static int	check_death(t_data *data)
{
	int	dead;

	pthread_mutex_lock(&data->dead_mutex);
	dead = (data->dead || data->all_ate);
	pthread_mutex_unlock(&data->dead_mutex);
	return (dead);
}

static void	take_forks(t_philo *philo, pthread_mutex_t **first,
		pthread_mutex_t **second)
{
	if (philo->id % 2)
	{
		*first = philo->left_fork;
		*second = philo->right_fork;
	}
	else
	{
		*first = philo->right_fork;
		*second = philo->left_fork;
	}
}

static void	eat_routine(t_philo *philo, t_data *data)
{
	pthread_mutex_t	*first;
	pthread_mutex_t	*second;

	take_forks(philo, &first, &second);
	pthread_mutex_lock(first);
	print_action(philo, "has taken a fork");
	if (data->nb_philos == 1)
	{
		pthread_mutex_unlock(first);
		return ;
	}
	pthread_mutex_lock(second);
	print_action(philo, "has taken a fork");
	print_action(philo, "is eating");
	pthread_mutex_lock(&data->meal_mutex);
	philo->last_meal_time = get_time_in_ms();
	philo->eat_count++;
	pthread_mutex_unlock(&data->meal_mutex);
	ft_usleep(data->time_to_eat, data);
	pthread_mutex_unlock(second);
	pthread_mutex_unlock(first);
}

void	*philo_routine(void *arg)
{
	t_philo	*philo;
	t_data	*data;

	philo = (t_philo *)arg;
	data = philo->data;
	if (philo->id % 2 == 0)
		ft_usleep(data->time_to_eat / 10, data);
	while (!check_death(data))
	{
		if (data->nb_philos == 1)
		{
			pthread_mutex_lock(philo->left_fork);
			print_action(philo, "has taken a fork");
			ft_usleep(data->time_to_die, data);
			pthread_mutex_unlock(philo->left_fork);
			break ;
		}
		eat_routine(philo, data);
		print_action(philo, "is sleeping");
		ft_usleep(data->time_to_sleep, data);
		print_action(philo, "is thinking");
		usleep(500);
	}
	return (NULL);
}
