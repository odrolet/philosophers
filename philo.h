/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oldrolet <oldrolet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/07 15:39:53 by oldrolet          #+#    #+#             */
/*   Updated: 2024/01/04 20:25:07 by oldrolet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <unistd.h>
# include <stdlib.h>
# include <limits.h>
# include <string.h>
# include <sys/time.h>
# include <pthread.h>
# include <stdio.h>
# include <stdbool.h>

typedef struct s_philo	t_philo;

typedef struct s_data
{
	int				philo_nbr;
	int				death_time;
	int				eat_time;
	int				sleep_time;
	int				eat_philo_nbr;
	int				start_time;
	int				think_time;
	bool			end_simulation;
	pthread_t		supervisor;
	pthread_mutex_t	*forks;
	pthread_mutex_t	print;
	pthread_mutex_t	end;
	t_philo			*philo;
}	t_data;

typedef struct s_philo
{
	int					philo_id;
	pthread_t			thread_id;
	int					eat_count;
	int					last_time_ate;
	bool				finished_eating;
	pthread_mutex_t		*right_fork;
	pthread_mutex_t		*left_fork;
	pthread_mutex_t		philo_mutex;
	t_data				*data;
}	t_philo;

int			ft_parsing(char **src);
int			ft_conversion(t_data *data, char **argv);
int			create_philos(t_data *data);
int			free_shit(t_data *data);
void		destroy_forks(pthread_mutex_t *forks, int fork_id);
void		destroy_philo_mutex(t_data *data, int mutex_id);
int			clear(t_data *data);
void		*supervisor(void *philo_arg);
void		*death(t_philo *philo);
int			start_threads(t_data *data);
long long	get_time(void);
void		p_mess(t_philo *philo, char *str);
void		*routine(void *philo_arg);
int			life(t_philo *philo);
void		ft_usleep(long milliseconds);
int			sim_is_finish(t_philo *philo);
int			eat(t_philo *philo);
int			sleep_philo(t_philo *philo);
int			think(t_philo *philo);
void		*one_case(t_philo *philo);
void		drop_forks(t_philo *philo);
void		take_forks(t_philo *philo);

#endif