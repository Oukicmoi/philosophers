/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gtraiman <gtraiman@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/04 18:14:34 by gtraiman          #+#    #+#             */
/*   Updated: 2025/01/17 19:35:51 by gtraiman         ###   ########.fr       */
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
		if (data->philo[i].thread)
			pthread_join(data->philo[i].thread, NULL);
		i++;
	}
	if (data->moni)
		pthread_join(data->moni, NULL);
	i = 0;
	ft_isdead(data->philo);
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

int	ft_usleep(long int ms, t_philo *philo)
{
	long int	start;

	start = getime();
	while (getime() - start < ms)
	{
		usleep(1000);
		if (testdeath(philo))
			return (1);
	}
	return (0);
}

int	take_forks_and_eat(t_philo *philo)
{
	t_data	*data;
	int		i;

	data = philo->data;
	if (aaah(philo, data) == 1)
		return (1);
	if (philo->id % 2 == 0)
		i = 3;
	else
		i = 4;
	if (testdeath(philo))
		return (ft_unlock(philo, data, i), 1);
	print_action(philo, "is eating\n");
	pthread_mutex_lock(&data->mxmeal);
	philo->lmeal = getime();
	philo->emealn++;
	pthread_mutex_unlock(&data->mxmeal);
	if (ft_usleep(data->tteat, philo))
	{
		if (testdeath(philo))
			return (ft_unlock(philo, data, i), 1);
	}
	ft_unlock(philo, data, i);
	return (0);
}

int	aaah(t_philo *philo, t_data *data)
{
	if (philo->id % 2 == 0)
	{
		pthread_mutex_lock(&data->forks[philo->rfork]);
		if (testdeath(philo))
			return (ft_unlock(philo, data, 1), 1);
		print_action(philo, "has taken a fork\n");
		pthread_mutex_lock(&data->forks[philo->lfork]);
		if (testdeath(philo))
			return (ft_unlock(philo, data, 3), 1);
		print_action(philo, "has taken a fork\n");
	}
	else
	{
		pthread_mutex_lock(&data->forks[philo->lfork]);
		if (testdeath(philo))
			return (ft_unlock(philo, data, 2), 1);
		print_action(philo, "has taken a fork\n");
		pthread_mutex_lock(&data->forks[philo->rfork]);
		if (testdeath(philo))
			return (ft_unlock(philo, data, 4), 1);
		print_action(philo, "has taken a fork\n");
	}
	return (0);
}
