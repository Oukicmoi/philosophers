/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gtraiman <gtraiman@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/04 17:58:40 by gtraiman          #+#    #+#             */
/*   Updated: 2025/01/05 01:12:03 by gtraiman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <pthread.h>
# include <ctype.h>
# include <errno.h>
# include <fcntl.h>
# include <readline/history.h>
# include <readline/readline.h>
# include <signal.h>
# include <stdio.h>
# include <stdlib.h>
# include <sys/wait.h>
# include <termios.h>
# include <unistd.h>

#include <pthread.h>
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <sys/time.h>

    typedef struct s_philo
    {
        int id;
        int lfork;
        int rfork;
        int lmeal;
        pthread_t thread;
        struct s_data *data;
    }   t_philo;

typedef struct s_data
{
    int philon;
    int ttdie;
    int tteat;
    int ttsleep;

    int must_eat_count;
    int round;
    int isdead;
    pthread_mutex_t *forks;
    pthread_mutex_t wmutex;
    t_philo *philo;
}   t_data;

int	ft_atoi(const char *nptr);
int philo(char **args);
int	parse(char **av);
int init_philo(t_data *data);
int init_data(t_data *data, int ac, char **av);
void cleanup(t_data *data);
void take_forks_and_eat(t_philo *philo);
void *philo_routine(void *arg);
int go_to_sleep_and_think(t_philo *philo);
long get_current_time_in_ms(void);
int testdeath(t_philo *philo);


#endif