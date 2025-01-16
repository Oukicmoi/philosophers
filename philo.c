/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gtraiman <gtraiman@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/04 17:58:26 by gtraiman          #+#    #+#             */
/*   Updated: 2025/01/16 20:48:10 by gtraiman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	init_data(t_data *data, int ac, char **av)
{
	int	i;

	data->philon = ft_atoi(av[1]);
	data->ttdie = ft_atoi(av[2]);
	data->tteat = ft_atoi(av[3]);
	data->ttsleep = ft_atoi(av[4]);
	data->start = getime();
	data->isdead = 0;
	if (ac == 6)
		data->must_eat_count = ft_atoi(av[5]);
	else
		data->must_eat_count = -1;
	data->forks = malloc(sizeof(pthread_mutex_t) * data->philon);
	if (!data->forks)
		return (printf("Failed to allocate memory for forks\n"), 1);
	i = -1;
	while (++i < data->philon)
		pthread_mutex_init(&data->forks[i], NULL);
	pthread_mutex_init(&data->mxwrite, NULL);
	pthread_mutex_init(&data->mxdead, NULL);
	data->philo = malloc(sizeof(t_philo) * data->philon);
	if (!data->philo)
		return (free(data->forks), 1);
	return (0);
}

void	*philo_routine(void *arg)
{
	t_philo	*philo;

	philo = arg;
	while (!testdeath(philo))
	{
		if (philo->data->philon == 1)
			usleep(1);
		else
		{
			if (philo->emealn != philo->data->must_eat_count)
				if (take_forks_and_eat(philo))
					return (NULL);
			if (testdeath(philo))
				return (NULL);
			if (philo->emealn != philo->data->must_eat_count)
			{
				if (go_to_sleep_and_think(philo))
					return (NULL);
			}
			else
				return (NULL);
		}		
	}
	return (NULL);
}

int	init_philo(t_data *data)
{
	int	i;

	i = 0;
	while (i < data->philon)
	{
		data->philo[i].emealn = 0;
		data->philo[i].lmeal = getime();
		data->philo[i].id = i + 1;
		data->philo[i].lfork = i;
		data->philo[i].rfork = (i + 1) % data->philon;
		data->philo[i].data = data;
		i++;
	}
	return (0);
}

int	testdeath(t_philo *philo)
{
	t_data	*data;

	data = philo->data;
	pthread_mutex_lock(&data->mxdead);
	if (data->isdead == 1)
	{
		pthread_mutex_unlock(&data->mxdead);
		return (1);
	}
	if (getime() - philo->lmeal >= data->ttdie)
	{
		data->isdead = 1;
		pthread_mutex_lock(&data->mxwrite);
		printf("%ld %d died\n", getime() - data->start, philo->id);
		pthread_mutex_unlock(&data->mxwrite);
		pthread_mutex_unlock(&data->mxdead);
		return (1);
	}
	pthread_mutex_unlock(&data->mxdead);
	return (0);
}
