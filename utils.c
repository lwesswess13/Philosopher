/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbouchib <sbouchib@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/13 09:21:24 by sbouchib          #+#    #+#             */
/*   Updated: 2026/05/13 09:21:25 by sbouchib         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

long long	get_time_in_ms(void)
{
	struct timeval	tv;

	gettimeofday(&tv, NULL);
	return ((tv.tv_sec * 1000) + (tv.tv_usec / 1000));
}

void	ft_usleep(long long time_in_ms, t_data *data)
{
	long long	start;

	start = get_time_in_ms();
	while ((get_time_in_ms() - start) < time_in_ms)
	{
		pthread_mutex_lock(&data->dead_mutex);
		if (data->dead)
		{
			pthread_mutex_unlock(&data->dead_mutex);
			break ;
		}
		pthread_mutex_unlock(&data->dead_mutex);
		usleep(500);
	}
}

void	print_action(t_philo *philo, char *str)
{
	long long	time;

	pthread_mutex_lock(&philo->data->dead_mutex);
	if (!philo->data->dead)
	{
		pthread_mutex_lock(&philo->data->print_mutex);
		time = get_time_in_ms() - philo->data->start_time;
		printf("%lld %d %s\n", time, philo->id, str);
		pthread_mutex_unlock(&philo->data->print_mutex);
	}
	pthread_mutex_unlock(&philo->data->dead_mutex);
}

int	ft_atoi(const char *str)
{
	long	res;

	res = 0;
	while (*str == ' ' || (*str >= 9 && *str <= 13))
		str++;
	if (*str == '-')
		return (-1);
	if (*str == '+')
		str++;
	while (*str >= '0' && *str <= '9')
	{
		res = res * 10 + (*str - '0');
		str++;
	}
	if (*str != '\0' || res > INT_MAX)
		return (-1);
	return ((int)res);
}
