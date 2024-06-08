/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wait_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chrstein <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/08 05:23:54 by chrstein          #+#    #+#             */
/*   Updated: 2024/06/08 05:23:56 by chrstein         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

void	*wait_dead(void *arg)
{
	t_list	*philo;

	philo = (t_list *)arg;
	sem_wait(philo->data->s_dead);
	sem_post(philo->data->s_dead);
	sem_wait(philo->s_is_dead);
	philo->is_dead = true;
	sem_post(philo->s_is_dead);
	return (NULL);
}

void	*wait_finish(void *arg)
{
	long	i;
	t_data	*data;

	data = (t_data *)arg;
	i = -1;
	while (++i < data->nb_of_philo)
	{
		sem_wait(data->s_finish);
	}
	i = -1;
	while (++i < data->nb_of_philo)
		sem_post(data->s_dead);
	return (NULL);
}
