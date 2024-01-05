/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_parsing.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oldrolet <oldrolet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/07 16:27:04 by oldrolet          #+#    #+#             */
/*   Updated: 2024/01/04 12:56:52 by oldrolet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"

void	*one_case(t_philo *philo)
{
	pthread_mutex_lock(philo->right_fork);
	p_mess(philo, "takes right fork"); 
	ft_usleep(philo->data->death_time);
	return (NULL);
}

void	ft_usleep(long milliseconds)
{
	long long	start;

	start = get_time();
	usleep(milliseconds * 1000 * 0.9);
	while ((get_time() < milliseconds + start))
	{
		usleep(150);
	}
}

static long	ft_atoi(const char *str)
{
	int		i;
	long	result;

	i = 0;
	result = 0;
	while (str[i])
	{
		result = result * 10 + str[i] - 48;
		i++;
	}
	return (result);
}

int	ft_conversion(t_data *data, char **argv)
{
	long	n;
	int		nbr[5];
	int		i;

	i = 0;
	nbr[4] = -1;
	while (argv[i])
	{
		n = ft_atoi(argv[i]);
		if (n > INT_MAX)
			return (-1);
		if (n == 0 && i != 4)
			return (-1);
		nbr[i] = (int)n;
		i++;
	}
	data->philo_nbr = nbr[0];
	data->death_time = nbr[1];
	data->eat_time = nbr[2];
	data->sleep_time = nbr[3];
	data->eat_philo_nbr = nbr[4];
	return (0);
}

int	ft_parsing(char **src)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (src[i])
	{
		j = 0;
		while (src[i][j])
		{
			if (src[i][j] < 48 || src[i][j] > 57)
				return (-1);
			j++;
		}
		i++;
	}
	return (0);
}
