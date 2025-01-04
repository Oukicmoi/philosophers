/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gtraiman <gtraiman@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/04 17:41:58 by gtraiman          #+#    #+#             */
/*   Updated: 2025/01/04 22:29:57 by gtraiman         ###   ########.fr       */
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
        if (pthread_create(&data->philo[i].thread, NULL, philo_routine, &data->philo[i]) != 0)
            return (1);
        i++;
    }
    return (0);
}


int main(int ac, char **av)
{
    t_data data;
    int i;

    if (ac < 5 || ac > 6)
    {
        printf("Error\n");
        return (1);
    }
    fprintf(stderr,"here");
    if (init_data(&data, ac, av) != 0 || init_philo(&data) != 0)
    {
        printf("Error\n");
        return (1);
    }
    if (create_philos(&data) != 0)
    {
        printf("Error\n");
        cleanup(&data);
        return (1);
    }
    i = 0;
    while (i < data.philon)
    {
        pthread_join(data.philo[i].thread, NULL);
        i++;
    }
    cleanup(&data);
    return (0);
}
