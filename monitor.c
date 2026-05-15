/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitor.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbouchib <sbouchib@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/13 09:21:30 by sbouchib          #+#    #+#             */
/*   Updated: 2026/05/13 09:21:31 by sbouchib         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static int	check_philo_death(t_data *data, int i)
{
	pthread_mutex_lock(&data->meal_mutex);
	if (get_time_in_ms() - data->philos[i].last_meal_time >= data->time_to_die)
	{
		pthread_mutex_unlock(&data->meal_mutex);
		print_action(&data->philos[i], "died");
		pthread_mutex_lock(&data->dead_mutex);
		data->dead = true;
		pthread_mutex_unlock(&data->dead_mutex);
		return (1);
	}
	pthread_mutex_unlock(&data->meal_mutex);
	return (0);
}

static int	check_all_ate(t_data *data)
{
	int	i;
	int	all_ate;

	if (data->nb_meals == -1)
		return (0);
	all_ate = 1;
	i = 0;
	while (i < data->nb_philos)
	{
		pthread_mutex_lock(&data->meal_mutex);
		if (data->philos[i].eat_count < data->nb_meals)
			all_ate = 0;
		pthread_mutex_unlock(&data->meal_mutex);
		i++;
	}
	if (all_ate)
	{
		pthread_mutex_lock(&data->dead_mutex);
		data->all_ate = true;
		pthread_mutex_unlock(&data->dead_mutex);
		return (1);
	}
	return (0);
}

void	*monitor_routine(void *arg)
{
	t_data	*data;
	int		i;

	data = (t_data *)arg;
	while (1)
	{
		i = 0;
		while (i < data->nb_philos)
		{
			if (check_philo_death(data, i))
				return (NULL);
			i++;
		}
		if (check_all_ate(data))
			return (NULL);
		usleep(1000);
	}
	return (NULL);
}
