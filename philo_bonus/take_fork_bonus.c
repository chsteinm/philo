/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   take_fork_bonus.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chrstein <chrstein@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/08 05:23:41 by chrstein          #+#    #+#             */
/*   Updated: 2024/06/08 05:29:26 by chrstein         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

void	print_fork(t_list *philo)
{
	useconds_t		current_time;

	if (is_finish(philo) == true)
		return ;
	current_time = get_time(philo->data->time);
	sem_wait(philo->data->s_print);
	printf("%u %ld has taken a fork\n", \
	current_time, philo->philo_nb);
	sem_post(philo->data->s_print);
}

void	print_think(t_list *philo)
{
	useconds_t		current_time;

	if (is_finish(philo) == true)
		return ;
	current_time = get_time(philo->data->time);
	sem_wait(philo->data->s_print);
	printf("%u %ld is thinking\n", \
	current_time, philo->philo_nb);
	sem_post(philo->data->s_print);
	philo->think = true;
}

void	*take_fork(void *arg)
{
	t_list	*philo;

	philo = (t_list *)arg;
	sem_wait(philo->data->s_forks);
	sem_wait(philo->s_fork);
	philo->fork_taken = true;
	sem_post(philo->s_fork);
	return (NULL);
}

bool	fork_is_taken(t_list *philo)
{
	bool	ret;

	ft_usleep(1);
	sem_wait(philo->s_fork);
	ret = philo->fork_taken;
	sem_post(philo->s_fork);
	return (ret);
}

void	take_forks_or_think(t_list *philo)
{
	if (pthread_create(&philo->th_fork, NULL, &take_fork, philo) != 0)
		exit(1);
	while (fork_is_taken(philo) == false && is_finish(philo) == false)
		if (philo->think == false)
			print_think(philo);
	if (pthread_join(philo->th_fork, NULL) != 0)
		exit(1);
	print_fork(philo);
	if (pthread_create(&philo->th_fork, NULL, &take_fork, philo) != 0)
		exit(1);
	while (fork_is_taken(philo) == false && is_finish(philo) == false)
		if (philo->think == false)
			print_think(philo);
	if (pthread_join(philo->th_fork, NULL) != 0)
		exit(1);
	philo->fork_taken = false;
}
