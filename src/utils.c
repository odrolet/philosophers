/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oldrolet <oldrolet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/18 19:05:56 by oldrolet          #+#    #+#             */
/*   Updated: 2024/01/03 16:38:00 by oldrolet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"

int	free_shit(t_data *data)
{
	if (data->philo)
		free(data->philo);
	if (data->forks)
		free(data->forks);
	return (-1);
}

void	p_mess(t_philo *philo, char *str)
{
	pthread_mutex_lock(&philo->data->end);
	if (!philo->data->end_simulation)
	{
		pthread_mutex_lock(&philo->data->print);
		printf("%lld %d %s\n", get_time() - philo->data->start_time,
			philo->philo_id, str);
		pthread_mutex_unlock(&philo->data->print);
	}
	pthread_mutex_unlock(&philo->data->end);
}

void	destroy_forks(pthread_mutex_t *forks, int fork_id)
{
	while (fork_id >= 0)
	{
		pthread_mutex_destroy(&forks[fork_id]);
		fork_id--;
	}
}

void	destroy_philo_mutex(t_data *data, int mutex_id)
{
	while (mutex_id >= 0)
	{
		pthread_mutex_destroy(&data->philo[mutex_id].philo_mutex);
		mutex_id--;
	}
}

int	clear(t_data *data)
{
	destroy_forks(data->forks, data->philo_nbr - 1);
	destroy_philo_mutex(data, data->philo_nbr - 1);
	pthread_mutex_destroy(&data->print);
	pthread_mutex_destroy(&data->end);
	return (free_shit(data));
}
