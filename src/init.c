/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oldrolet <oldrolet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/11 18:48:35 by oldrolet          #+#    #+#             */
/*   Updated: 2024/01/05 16:19:07 by oldrolet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"

int	sim_is_finish(t_philo *philo)
{
	pthread_mutex_lock(&philo->data->end);
	if (philo->data->end_simulation == true)
	{
		pthread_mutex_unlock(&philo->data->end);
		return (true);
	}
	pthread_mutex_unlock(&philo->data->end);
	return (false);
}

static int	init(t_data *data)
{
	int	i;

	i = 0;
	while (i < data->philo_nbr)
	{
		if (pthread_mutex_init(&data->forks[i], NULL) != 0)
		{
			destroy_forks(data->forks, i - 1);
			return (free_shit(data));
		}
		i++;
	}
	i = 0;
	while (i < data->philo_nbr)
	{
		if (pthread_mutex_init(&data->philo[i].philo_mutex, NULL))
		{
			destroy_philo_mutex(data, i - 1);
			destroy_forks(data->forks, data->philo_nbr - 1);
			return (free_shit(data));
		}
		i++;
	}
	return (0);
}

static int	init_two(t_data *data)
{
	if (pthread_mutex_init(&data->print, NULL) != 0)
	{
		destroy_forks(data->forks, data->philo_nbr - 1);
		destroy_philo_mutex(data, data->philo_nbr - 1);
		return (free_shit(data));
	}
	if (pthread_mutex_init(&data->end, NULL) != 0)
	{
		pthread_mutex_destroy(&data->print);
		destroy_forks(data->forks, data->philo_nbr - 1);
		destroy_philo_mutex(data, data->philo_nbr - 1);
		return (free_shit(data));
	}
	return (0);
}

static int	allocation(t_data *data)
{
	int	i;

	i = 0;
	data->forks = NULL;
	data->philo = (t_philo *)calloc(sizeof(t_philo), data->philo_nbr);
	if (!data->philo)
		return (free_shit(data));
	data->forks = (pthread_mutex_t *)calloc(sizeof(pthread_mutex_t), 
			data->philo_nbr);
	if (!data->forks)
		return (free_shit(data));
	if (init(data) == -1)
		return (-1);
	if (init_two(data) == -1)
		return (-1);
	return (0);
}

int	create_philos(t_data *data)
{
	int	i;

	i = 0;
	if (allocation(data) == -1)
		return (-1);
	while (i < data->philo_nbr)
	{
		data->philo[i].data = data;
		data->philo[i].philo_id = i + 1;
		data->philo[i].eat_count = 0;
		data->philo[i].right_fork = &data->forks[(i) % data->philo_nbr];
		data->philo[i].left_fork = &data->forks[(i + data->philo_nbr - 1) 
			% data->philo_nbr];
		data->philo[i].finished_eating = false;
		data->end_simulation = false;
		i++;
	}
	return (0);
}
