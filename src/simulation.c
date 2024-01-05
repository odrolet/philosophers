/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   simulation.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oldrolet <oldrolet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/18 19:07:13 by oldrolet          #+#    #+#             */
/*   Updated: 2024/01/05 15:43:43 by oldrolet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"

int	think(t_philo *philo)
{
	if (sim_is_finish(philo) == true)
		return (false);
	p_mess(philo, "is thinking");
	take_forks(philo);
	if (sim_is_finish(philo) == true)
		return (drop_forks(philo), false);
	return (true);
}

int	eat(t_philo *philo)
{
	if (sim_is_finish(philo) == true)
		return (drop_forks(philo), false);
	pthread_mutex_lock(&philo->philo_mutex);
	philo->last_time_ate = get_time();
	philo->eat_count++;
	pthread_mutex_unlock(&philo->philo_mutex);
	p_mess(philo, "is eating");
	ft_usleep(philo->data->eat_time);
	drop_forks(philo);
	if (sim_is_finish(philo) == true)
		return (false);
	return (true);
}

int	sleep_philo(t_philo *philo)
{
	if (sim_is_finish(philo) == true)
		return (false);
	p_mess(philo, "is sleeping");
	ft_usleep(philo->data->sleep_time);
	if (sim_is_finish(philo) == true)
		return (false);
	return (true);
}

int	life(t_philo *philo)
{
	if (think(philo) == false)
		return (false);
	if (eat(philo) == false)
		return (false);
	if (sleep_philo(philo) == false)
		return (false);
	return (true);
}

void	*routine(void *philo_arg)
{
	t_philo	*philo;

	philo = (t_philo *)philo_arg;
	philo->last_time_ate = philo->data->start_time;
	if (philo->data->philo_nbr == 1)
		return (one_case(philo));
	if (philo->philo_id % 2 == 1)
		ft_usleep (100);
	while (philo->eat_count != philo->data->eat_philo_nbr)
	{
		if (life(philo) == false)
			break ;
	}
	pthread_mutex_lock(&philo->data->end);
	philo->finished_eating = true;
	pthread_mutex_unlock(&philo->data->end);
	return (NULL);
}
