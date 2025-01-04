/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gtraiman <gtraiman@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/04 17:58:26 by gtraiman          #+#    #+#             */
/*   Updated: 2025/01/05 00:36:25 by gtraiman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int init_data(t_data *data, int ac, char **av)
{
    fprintf(stderr, "Entering init_data\n");
    data->philon = atoi(av[1]);
    data->ttdie = atoi(av[2]);
    data->tteat = atoi(av[3]);
    data->ttsleep = atoi(av[4]);

    if (ac == 6)
        data->must_eat_count = atoi(av[5]);
    else
        data->must_eat_count = -1;

    data->forks = malloc(sizeof(pthread_mutex_t) * data->philon);
    if (!data->forks)
    {
        fprintf(stderr, "Failed to allocate memory for forks\n");
        return (1);
    }
    fprintf(stderr, "Memory allocated for forks\n");
    data->philo = malloc(sizeof(t_philo) * data->philon);
    if (!data->philo)
    {
        fprintf(stderr, "Failed to allocate memory for philosophers\n");
        free(data->forks);
        return (1);
    }
    fprintf(stderr, "Memory allocated for philosophers\n");
    return (0);
}

void *philo_routine(void *arg)
{
    t_philo *philo = (t_philo *)arg;
    t_data  *data = philo->data;
	data->round = 1;
    while (1)
    {
        if (data->round == 1)
        {
            if ((philo->id % 2 == 1) && (philo->id != data->philon))
                take_forks_and_eat(philo);
            else
                usleep(1000);
        }
        else if (data->round == 2)
        {
            if (philo->id % 2 == 0)
                take_forks_and_eat(philo);
            else
                usleep(1000);
        }
        else if (data->round == 3)
        {
            if ((philo->id % 2 == 1) && (philo->id != 1))
                take_forks_and_eat(philo);
            else
                usleep(1000);
        }
        go_to_sleep_and_think(philo);
	data->round++;
    }
    return (NULL);
}


int init_philo(t_data *data)
{
	int	i;

	i = 0;
	while (i < data->philon)
	{
		data->philo[i].id = i + 1;
		data->philo[i].lfork = i;
		data->philo[i].rfork = (i + 1) % data->philon;
		data->philo[i].data = data;
		i++;
	}
	return (0);
}


