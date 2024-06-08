/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   eat_sleep_bonus.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chrstein <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/08 05:22:15 by chrstein          #+#    #+#             */
/*   Updated: 2024/06/08 05:22:19 by chrstein         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

void	print_sleep(t_list *philo)
{
	useconds_t		current_time;

	if (is_finish(philo) == true)
		return ;
	current_time = get_time(philo->data->time);
	sem_wait(philo->data->s_print);
	printf("%u %ld is sleeping\n", \
	current_time, philo->philo_nb);
	sem_post(philo->data->s_print);
	ft_usleep(philo->data->time_to_sleep);
}

void	print_eat(t_list *philo)
{
	useconds_t		current_time;

	if (is_finish(philo) == true)
		return ;
	current_time = get_time(philo->data->time);
	sem_wait(philo->data->s_print);
	printf("%u %ld is eating\n", \
	current_time, philo->philo_nb);
	sem_post(philo->data->s_print);
	ft_usleep(philo->data->time_to_eat);
	sem_post(philo->data->s_forks);
	sem_post(philo->data->s_forks);
}
