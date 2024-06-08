/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_destroy_bonus.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chrstein <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/08 05:22:28 by chrstein          #+#    #+#             */
/*   Updated: 2024/06/08 05:22:32 by chrstein         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

include "philo_bonus.h"

void	close_unset(t_data *data)
{
	if (data->s_dead_to_destroy == true)
	{
		sem_close(data->s_dead);
		sem_unlink(S_DEAD);
	}
	if (data->s_forks_to_destroy == true)
	{
		sem_close(data->s_forks);
		sem_unlink(S_FORKS);
	}
	if (data->s_print_to_destroy == true)
	{
		sem_close(data->s_print);
		sem_unlink(S_PRINT);
	}
	if (data->s_start_to_destroy == true)
	{
		sem_close(data->s_start);
		sem_unlink(S_START);
	}
	if (data->s_finish_to_destroy == true)
	{
		sem_close(data->s_finish);
		sem_unlink(S_FINISH);
	}
}

void	free_and_destroy(t_data *data, t_list **philo)
{
	free(data->pid_philo);
	ft_lstclear(philo);
	close_unset(data);
}
