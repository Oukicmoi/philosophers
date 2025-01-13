/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gtraiman <gtraiman@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/04 18:14:34 by gtraiman          #+#    #+#             */
/*   Updated: 2025/01/13 01:14:27 by gtraiman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	ft_atoi(const char *nptr)
{
	int	nb;
	int	signe;

	nb = 0;
	signe = 1;
	while ((*nptr >= 9 && *nptr <= 13) || *nptr == 32)
	{
		++nptr;
	}
	if (*nptr == '+' || *nptr == '-')
	{
		if (*nptr == '-')
			return (-1);
		++nptr;
	}
	while (*nptr >= '0' && *nptr <= '9')
	{
		nb = nb * 10 + *nptr -48;
		++nptr;
		if (nb < 0)
			return (-1);
	}
	return (nb * signe);
}

void	cleanup(t_data *data)
{
	int	i;

	i = 0;
	while (i < data->philon)
	{
		pthread_mutex_destroy(&data->forks[i]);
		i++;
	}
	pthread_mutex_destroy(&data->mxwrite);
	pthread_mutex_destroy(&data->mxdead);
	free(data->forks);
	free(data->philo);
}

void	take_forks_and_eat(t_philo *philo)
{
	t_data	*data;

	data = philo->data;
	if (testdeath(philo))
		return ;
	if (philo->id % 2 == 0)
	{
		pthread_mutex_lock(&data->forks[philo->rfork]);
		print_action(philo, "has taken a fork\n");
		pthread_mutex_lock(&data->forks[philo->lfork]);
		print_action(philo, "has taken a fork\n");
	}
	else
	{
		pthread_mutex_lock(&data->forks[philo->lfork]);
		print_action(philo, "has taken a fork\n");
		pthread_mutex_lock(&data->forks[philo->rfork]);
		print_action(philo, "has taken a fork\n");
	}
	print_action(philo, "is eating\n");
	usleep(data->tteat * 1000);
	philo->lmeal = getime();
	philo->emealn++;
	pthread_mutex_unlock(&data->forks[philo->rfork]);
	pthread_mutex_unlock(&data->forks[philo->lfork]);
}

void	print_action(t_philo *philo, char *str)
{
	t_data	*data;

	data = philo->data;
	pthread_mutex_lock(&data->mxwrite);
	printf("%ld %d %s", getime() - data->start, philo->id, str);
	pthread_mutex_unlock(&data->mxwrite);
}

int	go_to_sleep_and_think(t_philo *philo)
{
	t_data	*data;

	data = philo->data;
	print_action(philo, "is sleeping\n");
	usleep(data->ttsleep * 1000);
	print_action(philo, "done sleeping\n");
	if (testdeath(philo))
		return (0);
	print_action(philo, "is thinking\n");
	usleep(data->tteat * 1000);
	if (testdeath(philo))
		return (0);
	return (0);
}
