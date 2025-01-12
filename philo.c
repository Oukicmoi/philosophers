/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gtraiman <gtraiman@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/04 17:58:26 by gtraiman          #+#    #+#             */
/*   Updated: 2025/01/12 22:01:24 by gtraiman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int init_data(t_data *data, int ac, char **av)
{
	int	i;
	fprintf(stderr, "Entering init_data\n");
	data->philon = atoi(av[1]);
	data->ttdie = atoi(av[2]);
	data->tteat = atoi(av[3]);
	data->ttsleep = atoi(av[4]);
	data->start = getime();
	data->isdead = 0;

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
	i = 0;
	while (i < data->philon)
	{
		pthread_mutex_init(&data->forks[i], NULL);
		i++;
	}
	pthread_mutex_init(&data->mxwrite, NULL);
	pthread_mutex_init(&data->mxdead, NULL);

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
    t_philo *philo = arg;

    while (!testdeath(philo))
    {
		if(philo->data->philon == 1)
			usleep(1);
		else
		{
			if(philo->emealn != philo->data->must_eat_count)
				take_forks_and_eat(philo);
			if(testdeath(philo))
				return(NULL);
			if(philo->emealn != philo->data->must_eat_count)
				go_to_sleep_and_think(philo);
    	}		
	}
    return (NULL);
}

int init_philo(t_data *data)
{
	int	i;

	i = 0;
	while (i < data->philon)
	{
		data->philo[i].emealn = 0;
        data->philo[i].lmeal = getime();
		// printf("\n%d\n", data->philo[i].lmeal);
		data->philo[i].id = i + 1;
		data->philo[i].lfork = i;
		data->philo[i].rfork = (i + 1) % data->philon;
		data->philo[i].data = data;
		i++;
	}
	return (0);
}


