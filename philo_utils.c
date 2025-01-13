/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gtraiman <gtraiman@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/04 18:14:34 by gtraiman          #+#    #+#             */
/*   Updated: 2025/01/13 02:41:56 by gtraiman         ###   ########.fr       */
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
	if (*nptr)
		return (-1);
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

int	take_forks_and_eat(t_philo *philo)
{
	t_data	*data;

	data = philo->data;
	if (aaah(philo, data) == 1)
		return (1);
	print_action(philo, "is eating\n");
	usleep(data->tteat * 1000);
	ft_unlock(philo, data);
	if (testdeath(philo))
		return (1);
	philo->lmeal = getime();
	philo->emealn++;
	return (0);
}

void	ft_unlock(t_philo *philo, t_data *data)
{
	pthread_mutex_unlock(&data->forks[philo->rfork]);
	pthread_mutex_unlock(&data->forks[philo->lfork]);
}

int	aaah(t_philo *philo, t_data *data)
{
	if (philo->id % 2 == 0)
	{
		pthread_mutex_lock(&data->forks[philo->rfork]);
		print_action(philo, "has taken a fork\n");
		pthread_mutex_lock(&data->forks[philo->lfork]);
		print_action(philo, "has taken a fork\n");
		if (testdeath(philo))
			return (ft_unlock(philo, data), 1);
	}
	else
	{
		pthread_mutex_lock(&data->forks[philo->lfork]);
		print_action(philo, "has taken a fork\n");
		pthread_mutex_lock(&data->forks[philo->rfork]);
		print_action(philo, "has taken a fork\n");
		if (testdeath(philo))
			return (ft_unlock(philo, data), 1);
	}
	return (0);
}
