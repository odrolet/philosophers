/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oldrolet <oldrolet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/07 15:38:35 by oldrolet          #+#    #+#             */
/*   Updated: 2024/01/05 15:10:06 by oldrolet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"

void	take_forks(t_philo *philo)
{
	pthread_mutex_lock(philo->right_fork);
	p_mess(philo, "takes right fork");
	pthread_mutex_lock(philo->left_fork);
	p_mess(philo, "takes left fork");
}

void	drop_forks(t_philo *philo)
{
	pthread_mutex_unlock(philo->right_fork);
	//p_mess(philo, "drops right fork");
	pthread_mutex_unlock(philo->left_fork);
	//p_mess(philo, "drops left fork");
}

int	main(int argc, char *argv[])
{
	t_data		data;

	if (argc != 5 && argc != 6)
		return (-1);
	if (ft_parsing(argv + 1) == -1)
		return (-1);
	if (ft_conversion(&data, argv + 1) == -1)
		return (-1);
	if (create_philos(&data) == -1)
		return (-1);
	if (start_threads(&data) == -1)
		return (-1);
	clear(&data);
	return (0);
}
