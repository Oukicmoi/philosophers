/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gtraiman <gtraiman@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/04 18:14:34 by gtraiman          #+#    #+#             */
/*   Updated: 2025/01/05 00:38:36 by gtraiman         ###   ########.fr       */
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
    free(data->forks);
    free(data->philo);
}
void take_forks_and_eat(t_philo *philo)
{
    t_data *data = philo->data;

    // Prendre la fourchette gauche
    pthread_mutex_lock(&data->forks[philo->lfork]);
    printf("%d has taken a fork\n", philo->id);

    // Prendre la fourchette droite
    pthread_mutex_lock(&data->forks[philo->rfork]);
    printf("%d has taken a fork\n", philo->id);

    printf("%d is eating\n", philo->id);
    // Ici tu peux enregistrer philo->last_meal_time = get_current_time_in_ms();
    usleep(data->tteat * 1000);

    // Reposer les fourchettes
    pthread_mutex_unlock(&data->forks[philo->rfork]);
    pthread_mutex_unlock(&data->forks[philo->lfork]);
}

void go_to_sleep_and_think(t_philo *philo)
{
    t_data *data = philo->data;

    printf("%d is sleeping\n", philo->id);
    usleep(data->ttsleep * 1000);
    printf("%d is thinking\n", philo->id);
    usleep(data->tteat * 900);
}
