/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_data_bonus.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chrstein <chrstein@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/08 05:23:06 by chrstein          #+#    #+#             */
/*   Updated: 2024/06/08 05:28:26 by chrstein         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

useconds_t	init_time(void)
{
	struct timeval	time;

	gettimeofday(&time, NULL);
	return ((time.tv_sec * 1000) + (time.tv_usec / 1000));
}

int	init_pids(t_data *data)
{
	data->pid_philo = malloc(data->nb_of_philo * sizeof(pid_t));
	if (!data->pid_philo)
		return (EXIT_FAILURE);
	memset((void *)data->pid_philo, 0, data->nb_of_philo);
	return (EXIT_SUCCESS);
}

int	init_data(t_data *data, char **argv)
{
	char	*endptr;

	memset((void *)data, 0, sizeof(t_data));
	endptr = NULL;
	data->nb_of_philo = ft_strtol(argv[1], &endptr, 10);
	if (*endptr || data->nb_of_philo < 1)
		return (EXIT_FAILURE);
	data->time_to_die = ft_strtol(argv[2], &endptr, 10);
	if (*endptr || data->time_to_die < 0)
		return (EXIT_FAILURE);
	data->time_to_eat = ft_strtol(argv[3], &endptr, 10);
	if (*endptr || data->time_to_eat < 0)
		return (EXIT_FAILURE);
	data->time_to_sleep = ft_strtol(argv[4], &endptr, 10);
	if (*endptr || data->time_to_sleep < 0)
		return (EXIT_FAILURE);
	if (argv[5])
	{
		data->nb_of_time_philo_eat = ft_strtol(argv[5], &endptr, 10);
		if (*endptr || data->nb_of_time_philo_eat < 0)
			return (EXIT_FAILURE);
	}
	data->time = init_time();
	return (init_pids(data));
}
