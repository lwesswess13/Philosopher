/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbouchib <sbouchib@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/13 09:21:41 by sbouchib          #+#    #+#             */
/*   Updated: 2026/05/13 09:21:42 by sbouchib         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static int	check_args(int argc)
{
	if (argc != 5 && argc != 6)
	{
		printf("Usage: ./philo nb_philos time_to_die time_to_eat ");
		printf("time_to_sleep [nb_meals]\n");
		return (1);
	}
	return (0);
}

static void	start_threads(t_data *data, pthread_t *monitor)
{
	int	i;

	i = 0;
	while (i < data->nb_philos)
	{
		pthread_create(&data->philos[i].thread, NULL,
			philo_routine, &data->philos[i]);
		i++;
	}
	pthread_create(monitor, NULL, monitor_routine, data);
	i = 0;
	while (i < data->nb_philos)
	{
		pthread_join(data->philos[i].thread, NULL);
		i++;
	}
	pthread_join(*monitor, NULL);
}

int	main(int argc, char **argv)
{
	t_data		data;
	pthread_t	monitor;

	if (check_args(argc))
		return (1);
	if (init_data(&data, argc, argv))
	{
		printf("Error: Invalid arguments or malloc failed\n");
		return (1);
	}
	init_philos(&data);
	start_threads(&data, &monitor);
	free_all(&data);
	return (0);
}
