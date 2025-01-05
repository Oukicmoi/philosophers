/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gtraiman <gtraiman@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/04 18:14:34 by gtraiman          #+#    #+#             */
/*   Updated: 2025/01/05 23:58:56 by gtraiman         ###   ########.fr       */
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
    pthread_mutex_destroy(&data->wmutex);
    pthread_mutex_destroy(&data->round);
    pthread_mutex_destroy(&data->dead_mutex);
    free(data->forks);
    free(data->philo);
}
void take_forks_and_eat(t_philo *philo)
{
    t_data *data = philo->data;

    // Prendre la fourchette gauche
    pthread_mutex_lock(&data->forks[philo->lfork]);
    pthread_mutex_lock(&data->wmutex);
    printf("%ld %d has taken a fork\n", getime() - data->start, philo->id);
    pthread_mutex_unlock(&data->wmutex);

    // Prendre la fourchette droite
    pthread_mutex_lock(&data->forks[philo->rfork]);
    pthread_mutex_lock(&data->wmutex);
    printf("%ld %d has taken a fork\n", getime() - data->start, philo->id);
    pthread_mutex_unlock(&data->wmutex);


    pthread_mutex_lock(&data->wmutex);
    printf("%ld %d is eating\n", getime() - data->start, philo->id);
    pthread_mutex_unlock(&data->wmutex);
    // Ici tu peux enregistrer philo->last_meal_time = get_current_time_in_ms();
    usleep(data->tteat * 1000);
    philo->lmeal = getime();
    // Reposer les fourchettes
    pthread_mutex_unlock(&data->forks[philo->rfork]);
    pthread_mutex_unlock(&data->forks[philo->lfork]);
}

int go_to_sleep_and_think(t_philo *philo)
{
    t_data *data = philo->data;

    if(testdeath(philo) == 1)
        return(1);
    pthread_mutex_lock(&data->wmutex);
    printf("%ld %d is sleeping\n", getime() - data->start, philo->id);
    pthread_mutex_unlock(&data->wmutex);
    usleep(data->ttsleep * 1000);
    if(testdeath(philo) == 1)
        return(1);
    pthread_mutex_lock(&data->wmutex);
    printf("%ld %d is thinking\n", getime() - data->start, philo->id);
    pthread_mutex_unlock(&data->wmutex);
    usleep(data->tteat * 900);
    if(testdeath(philo) == 1)
        return(1);
    return(0);
}

int testdeath(t_philo *philo)
{
    t_data *data = philo->data;
    long now = getime();

    // 1) On lock
    pthread_mutex_lock(&data->dead_mutex);

    // 2) On check si isdead est déjà mis
    if (data->isdead == 1)
    {
        pthread_mutex_unlock(&data->dead_mutex);
        return (1);
    }
    // 3) On check si ce philo doit mourir
    if (now - philo->lmeal >= data->ttdie)
    {
        data->isdead = 1;
        pthread_mutex_unlock(&data->dead_mutex);

        printf("%ld %d is dead\n", now - data->start, philo->id);
        return (1);
    }

    // 4) On unlock
    pthread_mutex_unlock(&data->dead_mutex);
    return (0);
}


long getime(void)
{
    struct timeval tv;
    gettimeofday(&tv, NULL);
    return ((tv.tv_sec * 1000) + (tv.tv_usec / 1000));
}
