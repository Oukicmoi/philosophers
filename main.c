/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gtraiman <gtraiman@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/04 17:41:58 by gtraiman          #+#    #+#             */
/*   Updated: 2025/01/12 23:13:45 by gtraiman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int philo(char **args)
{
	(void)args;
	printf("here");
	return(0);
}

int	parse(char **av)
{
	int	i;

	i = 0;
	while(av[++i])
            if(ft_atoi(av[i]) < 0 || ft_atoi(av[1]) > 200)
                return(1);
        return(0);
}

int create_philos(t_data *data)
{
    int i;

    i = 0;
    while (i < data->philon)
    {
        if (pthread_create(&data->philo[i].thread, NULL,
                philo_routine, &data->philo[i]) != 0)
            return (1);
        // printf("\nallez %d\n", data->philo[i].id);
        i = i + 2;
    }
    // fprintf(stderr,"here");
    i = 1;
    while (i < data->philon)
    {
        if (pthread_create(&data->philo[i].thread, NULL,
                philo_routine, &data->philo[i]) != 0)
            return (1);
        // printf("\nallez %d\n", data->philo[i].id);
        i = i + 2;
    }
    return (0);
}




int main(int ac, char **av)
{
    t_data data;
    int i;

    if (ac < 5 || ac > 6 || parse(av) != 0)
        return (printf("Error\n"), 1);
    if (init_data(&data, ac, av) != 0 || init_philo(&data) != 0)
        return (printf("Error\n"), 1);
    if (create_philos(&data) != 0)
        return (printf("Error\n"), cleanup(&data), 1);
    // printf("nombre de meals manges par le dernier : %d", data.philo[data.philon].emealn);
    i = 0;
    while (i < data.philon)
    {
        pthread_join(data.philo[i].thread, NULL);
        i++;
    }
    cleanup(&data);
    return (0);
}
