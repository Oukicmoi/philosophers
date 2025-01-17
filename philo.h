/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gtraiman <gtraiman@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/04 17:58:40 by gtraiman          #+#    #+#             */
/*   Updated: 2025/01/17 17:28:45 by gtraiman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <pthread.h>
# include <ctype.h>
# include <errno.h>
# include <fcntl.h>
# include <signal.h>
# include <stdio.h>
# include <stdlib.h>
# include <sys/wait.h>
# include <termios.h>
# include <unistd.h>
# include <pthread.h>
# include <stdlib.h>
# include <stdio.h>
# include <unistd.h>
# include <sys/time.h>

typedef struct s_philo
{
	int				id;
	int				lfork;
	int				rfork;
	int				emealn;
	long int		lmeal;
	pthread_t		thread;
	struct s_data	*data;
}	t_philo;

typedef struct s_data
{
	int					argc;
	int					philon;
	int					ttdie;
	int					tteat;
	int					ttsleep;
	int					must_eat_count;
	int					isdead;
	long int			start;
	pthread_mutex_t		*forks;
	pthread_mutex_t		mxwrite;
	pthread_mutex_t		mxmeal;
	pthread_mutex_t		mxdead;
	t_philo				*philo;
	pthread_t			moni;
}	t_data;

int			ft_atoi(const char *nptr);
int			parse(char **av);
int			init_philo(t_data *data);
int			init_data(t_data *data, int ac, char **av);
void		cleanup(t_data *data);
int			take_forks_and_eat(t_philo *philo);
void		*philo_routine(void *arg);
int			go_to_sleep_and_think(t_philo *philo);
long		getime(void);
int			testdeath(t_philo *philo);
void		print_action(t_philo *philo, char *str);
void		ft_unlock(t_philo *philo, t_data *data, int i);
int			aaah(t_philo *philo, t_data *data);
int			ft_usleep(long int ms, t_philo *philo);
void		*moniroutine(void *arg);
void		*ft_isdead(t_philo *philo);

#endif