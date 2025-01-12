/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gtraiman <gtraiman@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/04 18:14:34 by gtraiman          #+#    #+#             */
/*   Updated: 2025/01/12 23:16:25 by gtraiman         ###   ########.fr       */
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
			return(-1);
		++nptr;
	}
	while (*nptr >= '0' && *nptr <= '9')
	{
		nb = nb * 10 + *nptr -48;
		++nptr;
        if(nb < 0)
            return(-1);
	}
	return (nb * signe);
}

void cleanup(t_data *data)
{
    int i;

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

void take_forks_and_eat(t_philo *philo)
{
	t_data *data = philo->data;

	if(testdeath(philo))
		return ;
	if (philo->id % 2 == 0)
	{
		// Philosophe pair -> prend la fourchette de droite d’abord
		pthread_mutex_lock(&data->forks[philo->rfork]);
		print_action(philo, "has taken a fork\n");
		pthread_mutex_lock(&data->forks[philo->lfork]);
		print_action(philo, "has taken a fork\n");
	}
	else
	{
		// Philosophe impair -> prend la fourchette de gauche d’abord
		pthread_mutex_lock(&data->forks[philo->lfork]);
		print_action(philo, "has taken a fork\n");
		pthread_mutex_lock(&data->forks[philo->rfork]);
		print_action(philo, "has taken a fork\n");
	}

	// printf("\nid :%d\n",philo->id);
	// Manger
	print_action(philo, "is eating\n");
	usleep(data->tteat * 1000);
	philo->lmeal = getime();
	philo->emealn++;

	// Reposer les fourchettes
	pthread_mutex_unlock(&data->forks[philo->rfork]);
	pthread_mutex_unlock(&data->forks[philo->lfork]);
}

void print_action(t_philo *philo, char *str)
{
	t_data *data = philo->data;
    
	pthread_mutex_lock(&data->mxwrite);
	printf("%ld %d %s", getime() - data->start, philo->id, str);
	pthread_mutex_unlock(&data->mxwrite);
}

int go_to_sleep_and_think(t_philo *philo)
{
    t_data *data = philo->data;


	print_action(philo, "is sleeping\n");
	usleep(data->ttsleep * 1000);
	if(testdeath(philo))
		return(0);
	print_action(philo, "is thinking\n");
	usleep(data->tteat * 900);

    return(0);
}

int testdeath(t_philo *philo)
{
    t_data *data = philo->data;
    long int now = getime();

    pthread_mutex_lock(&data->mxdead);
    if (data->isdead == 1)
    {
        pthread_mutex_unlock(&data->mxdead);
        return (1);
    }
    if (now - philo->lmeal >= data->ttdie)
    {
        data->isdead = 1;
        pthread_mutex_unlock(&data->mxdead);
        print_action(philo, "is dead\n");
        return (1);
    }
    pthread_mutex_unlock(&data->mxdead);
    return (0);
}


long getime(void)
{
    struct timeval tv;
    gettimeofday(&tv, NULL);
    return ((tv.tv_sec * 1000) + (tv.tv_usec / 1000));
}
