/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_utils2.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gtraiman <gtraiman@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/13 09:43:55 by gtraiman          #+#    #+#             */
/*   Updated: 2025/01/17 13:50:25 by gtraiman         ###   ########.fr       */
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
    t_data *data = (t_data *)arg;

    while (1)
    {
        int i = 0;
        while (i < data->philon)
        {
            if (testdeath(&data->philo[i]))
                return (NULL);
            i++;
        }
        usleep(1000);
    }
    return (NULL);
}
