/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_utils2.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gtraiman <gtraiman@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/13 09:43:55 by gtraiman          #+#    #+#             */
/*   Updated: 2025/01/17 17:55:35 by gtraiman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

long	getime(void)
{
	struct timeval	tv;

	gettimeofday(&tv, NULL);
	return ((tv.tv_sec * 1000) + (tv.tv_usec / 1000));
}

void	ft_unlock(t_philo *philo, t_data *data, int i)
{
	if (i == 1)
		pthread_mutex_unlock(&data->forks[philo->rfork]);
	if (i == 2)
		pthread_mutex_unlock(&data->forks[philo->lfork]);
	if (i == 3)
	{
		pthread_mutex_unlock(&data->forks[philo->rfork]);
		pthread_mutex_unlock(&data->forks[philo->lfork]);
	}
	if (i == 4)
	{
		pthread_mutex_unlock(&data->forks[philo->lfork]);
		pthread_mutex_unlock(&data->forks[philo->rfork]);
	}	
}

void	*moniroutine(void *arg)
{
	t_data	*data;
	int		i;
	int		cpt;

	data = (t_data *)arg;
	while (1)
	{
		cpt = 0;
		i = 0;
		while (i < data->philon)
		{
			if (testdeath(&data->philo[i]))
				return (NULL);
			pthread_mutex_lock(&data->mxmeal);
			if (data->philo->emealn >= data->must_eat_count && data->argc == 6)
				cpt++;
			pthread_mutex_unlock(&data->mxmeal);
			i++;
		}
		if (cpt == data->philon + 1)
			ft_isdead(data->philo);
		usleep(1000);
	}
	return (NULL);
}

void	*ft_isdead(t_philo *philo)
{
	pthread_mutex_lock(&philo->data->mxdead);
	philo->data->isdead = 1;
	pthread_mutex_unlock(&philo->data->mxdead);
	return (NULL);
}
