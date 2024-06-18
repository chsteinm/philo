/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_and.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chrstein <chrstein@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/14 12:29:08 by chrstein          #+#    #+#             */
/*   Updated: 2024/06/18 15:32:52 by chrstein         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

bool	finish_to_eat(t_list *philo)
{
	bool	ret;

	pthread_mutex_lock(&philo->data->m_finish);
	ret = philo->finish_eating;
	pthread_mutex_unlock(&philo->data->m_finish);
	return (ret);
}

void	all_finish(t_list *philo)
{
	t_list	*cpy;

	cpy = philo;
	while (philo->prev)
		philo = philo->prev;
	while (philo)
	{
		if (finish_to_eat(philo) == false)
			return ;
		philo = philo->next;
	}
	pthread_mutex_lock(&cpy->data->m_dead);
	cpy->data->dead = true;
	pthread_mutex_unlock(&cpy->data->m_dead);
}

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
	pthread_mutex_lock(philo->right_fork);
	*philo->right_fork_is_taken = false;
	pthread_mutex_unlock(philo->right_fork);
	pthread_mutex_lock(philo->left_fork);
	*philo->left_fork_is_taken = false;
	pthread_mutex_unlock(philo->left_fork);
	if (philo->data->nb_of_time_philo_eat && --philo->nb_of_eat == 0)
		philo->finish_eating = true;
	all_finish(philo);
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
