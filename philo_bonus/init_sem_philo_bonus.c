/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_sem_philo_bonus.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chrstein <chrstein@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/08 05:23:21 by chrstein          #+#    #+#             */
/*   Updated: 2024/06/08 05:28:48 by chrstein         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

void	unlink_for_secure(void)
{
	sem_unlink(S_FORKS);
	sem_unlink(S_DEAD);
	sem_unlink(S_PRINT);
	sem_unlink(S_START);
	sem_unlink(S_FINISH);
}

int	init_sem(t_data *data)
{
	unlink_for_secure();
	data->s_forks = sem_open(S_FORKS, O_CREAT, 0700, data->nb_of_philo);
	if (data->s_forks == SEM_FAILED)
		return (EXIT_FAILURE);
	data->s_forks_to_destroy = true;
	data->s_finish = sem_open(S_FINISH, O_CREAT, 0700, 0);
	if (data->s_finish == SEM_FAILED)
		return (EXIT_FAILURE);
	data->s_finish_to_destroy = true;
	data->s_dead = sem_open(S_DEAD, O_CREAT, 0700, 0);
	if (data->s_dead == SEM_FAILED)
		return (EXIT_FAILURE);
	data->s_dead_to_destroy = true;
	data->s_print = sem_open(S_PRINT, O_CREAT, 0700, 1);
	if (data->s_print == SEM_FAILED)
		return (EXIT_FAILURE);
	data->s_print_to_destroy = true;
	data->s_start = sem_open(S_START, O_CREAT, 0700, 0);
	if (data->s_start == SEM_FAILED)
		return (EXIT_FAILURE);
	data->s_start_to_destroy = true;
	return (EXIT_SUCCESS);
}

int	init_philo(t_data *data, t_list **philo)
{
	long	i;
	t_list	*new;

	*philo = NULL;
	i = 0;
	while (++i <= data->nb_of_philo)
	{
		new = ft_lstnew(data, i);
		if (!new)
			return (EXIT_FAILURE);
		ft_lstadd_back(philo, new);
	}
	return (EXIT_SUCCESS);
}
