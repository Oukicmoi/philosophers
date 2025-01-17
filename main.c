/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gtraiman <gtraiman@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/04 17:41:58 by gtraiman          #+#    #+#             */
/*   Updated: 2025/01/17 15:25:34 by gtraiman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	parse(char **av)
{
	int	i;

	i = 0;
	while (av[++i])
	{
		if (ft_atoi(av[i]) < 0 || ft_atoi(av[1]) > 200 || ft_atoi(av[2]) < 60)
			return (1);
	}
	return (0);
}

int	create_philos(t_data *data)
{
	int	i;

	i = 1;
	pthread_create(&data->moni, NULL, moniroutine, data);
	while (i < data->philon)
	{
		if (pthread_create(&data->philo[i].thread, NULL,
				philo_routine, &data->philo[i]) != 0)
			return (1);
		i = i + 2;
	}
	usleep(25);
	i = 0;
	while (i < data->philon)
	{
		if (pthread_create(&data->philo[i].thread, NULL,
				philo_routine, &data->philo[i]) != 0)
			return (1);
		i = i + 2;
	}
	return (0);
}

void	print_action(t_philo *philo, char *str)
{
	t_data	*data;

	data = philo->data;
	if (testdeath(philo))
		return ;
	pthread_mutex_lock(&data->mxdead);
	pthread_mutex_lock(&data->mxwrite);
	if (!data->isdead)
		printf("%ld %d %s", getime() - data->start, philo->id, str);
	pthread_mutex_unlock(&data->mxwrite);
	pthread_mutex_unlock(&data->mxdead);
}

int	go_to_sleep_and_think(t_philo *philo)
{
	t_data	*data;

	data = philo->data;
	if (testdeath(philo))
		return (1);
	print_action(philo, "is sleeping\n");
	ft_usleep(data->ttsleep, philo);
	if (testdeath(philo))
		return (1);
	print_action(philo, "is thinking\n");
	if ((data->tteat * 0.9 + data->tteat + data->ttsleep) < data->ttdie)
		ft_usleep(data->tteat * 0.9, philo);
	if (testdeath(philo))
		return (1);
	return (0);
}

int	main(int ac, char **av)
{
	t_data	data;
	int		i;

	if (ac < 5 || ac > 6 || parse(av) != 0)
		return (printf("Error\n"), 1);
	if (init_data(&data, ac, av) != 0 || init_philo(&data) != 0)
		return (printf("Error\n"), 1);
	if (create_philos(&data) != 0)
		return (printf("Error\n"), cleanup(&data), 1);
	i = 0;
	while (i < data.philon)
	{
		pthread_join(data.philo[i].thread, NULL);
		i++;
	}
	pthread_join(data.moni, NULL);
	cleanup(&data);
	return (0);
}
