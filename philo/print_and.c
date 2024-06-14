/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_and.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chrstein <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/14 12:29:08 by chrstein          #+#    #+#             */
/*   Updated: 2024/06/14 12:29:09 by chrstein         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	print_and_eat(t_list *philo)
{
	useconds_t	current_time;

	if (is_finish(philo))
		return ;
	current_time = get_time(philo->data->time);
	pthread_mutex_lock(&philo->data->m_print);
	if (is_dead(philo) == false)
	{
		printf("%u %ld is eating\n", \
		current_time, philo->philo_nb);
	}
	pthread_mutex_unlock(&philo->data->m_print);
	ft_usleep(philo->data->time_to_eat);
	if (philo->data->nb_of_time_philo_eat && --philo->nb_of_eat == 0)
		philo->finish_eating = true;
	pthread_mutex_lock(philo->right_fork);
	*philo->right_fork_is_taken = false;
	pthread_mutex_unlock(philo->right_fork);
	pthread_mutex_lock(philo->left_fork);
	*philo->left_fork_is_taken = false;
	pthread_mutex_unlock(philo->left_fork);
}

void	print_and_think(t_list *philo)
{
	useconds_t	current_time;

	if (is_finish(philo))
		return ;
	current_time = get_time(philo->data->time);
	pthread_mutex_lock(&philo->data->m_print);
	if (is_dead(philo) == false)
	{
		printf("%u %ld is thinking\n", \
		current_time, philo->philo_nb);
	}
	pthread_mutex_unlock(&philo->data->m_print);
	philo->think = true;
}

void	print_and_sleep(t_list *philo)
{
	useconds_t	current_time;

	if (is_finish(philo))
		return ;
	current_time = get_time(philo->data->time);
	pthread_mutex_lock(&philo->data->m_print);
	if (is_dead(philo) == false)
	{
		printf("%u %ld is sleeping\n", \
		current_time, philo->philo_nb);
	}
	pthread_mutex_unlock(&philo->data->m_print);
	ft_usleep(philo->data->time_to_sleep);
}
