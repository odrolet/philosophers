/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   supervisor.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oldrolet <oldrolet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/18 19:06:26 by oldrolet          #+#    #+#             */
/*   Updated: 2024/01/05 15:29:31 by oldrolet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"

long long	get_time(void)
{
	struct timeval			current_time;
	static struct timeval	start_time = {-1, -1};

	if (start_time.tv_sec == -1 && start_time.tv_usec == -1)
		gettimeofday(&start_time, NULL);
	gettimeofday(&current_time, NULL);
	return ((current_time.tv_sec * 1000 - start_time.tv_sec * 1000) + 
		(current_time.tv_usec / 1000 - start_time.tv_usec / 1000));
}

bool	check_if_dead(t_philo philo)
{
	pthread_mutex_lock(&philo.data->end);
	if (philo.finished_eating == true)
	{
		pthread_mutex_unlock(&philo.data->end);
		return (false);
	}
	pthread_mutex_unlock(&philo.data->end);
	if ((get_time() - philo.last_time_ate) > philo.data->death_time)
	{
		p_mess(&philo, "died");
		pthread_mutex_lock(&philo.data->end);
		philo.data->end_simulation = true;
		pthread_mutex_unlock(&philo.data->end);
		return (true);
	}
	return (false);
}

int	philo_finish_eating(t_data *data)
{
	int	i;

	i = 0;
	pthread_mutex_lock(&data->end);
	while (i < data->philo_nbr)
	{
		if (data->philo[i].finished_eating == false)
		{
			pthread_mutex_unlock(&data->end);
			return (false);
		}
		i++;
	}
	data->end_simulation = true;
	pthread_mutex_unlock(&data->end);
	return (true);
}

void	*supervisor(void *philo_arg)
{
	t_data	*data;
	int		i;
	int		quit;

	data = (t_data *)philo_arg;
	quit = true;
	while (quit)
	{
		i = 0;
		while (i < data->philo_nbr && quit)
		{
			if (check_if_dead(data->philo[i]) == true)
			{
				quit = false;
			}
			i++;
		}
		if (philo_finish_eating(data) == true)
			quit = false;
	}
	return (NULL);
}

int	start_threads(t_data *data)
{
	int	i;

	i = 0;
	data->start_time = get_time();
	while (i < data->philo_nbr)
	{
		if (pthread_create(&data->philo[i].thread_id, NULL,
				&routine, &data->philo[i]) != 0)
			return (clear(data));
		i++;
	}
	// if (pthread_create(&data->supervisor, NULL, &supervisor, data) != 0)
	// 	return (clear(data));
	supervisor(data);
	i = 0;
	while (i < data->philo_nbr)
	{
		if (pthread_join(data->philo[i].thread_id, NULL) != 0)
			return (clear(data));
		i++;
	}
	// if (pthread_join(data->supervisor, NULL) != 0)
	// 	return (clear(data));
	return (0);
}
