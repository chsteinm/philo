/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lst_funcs_bonus.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chrstein <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/08 05:22:39 by chrstein          #+#    #+#             */
/*   Updated: 2024/06/08 05:22:41 by chrstein         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

t_list	*ft_lstnew(t_data *data, long philo_nb)
{
	t_list	*new;

	new = malloc(sizeof(t_list) * 1);
	if (!new)
		return (NULL);
	memset((void *)new, 0, sizeof(t_list));
	new->s_is_dead = sem_open(S_IS_DEAD, O_CREAT, 0700, 1);
	if (new->s_is_dead == SEM_FAILED)
		return (NULL);
	new->s_is_dead_to_destroy = true;
	new->s_fork = sem_open(S_FORK, O_CREAT, 0700, 1);
	if (new->s_fork == SEM_FAILED)
		return (NULL);
	new->s_fork_to_destroy = true;
	new->philo_nb = philo_nb;
	new->data = data;
	new->nb_of_eat = new->data->nb_of_time_philo_eat;
	return (new);
}

void	ft_lstadd_back(t_list **lst, t_list *new)
{
	t_list	*ptr;

	ptr = *lst;
	while (ptr && ptr->next)
		ptr = ptr->next;
	if (ptr)
	{
		ptr->next = new;
		new->prev = ptr;
	}
	else
		*lst = new;
}

void	ft_lstclear(t_list **lst)
{
	t_list	*tmp;

	if (!lst)
		return ;
	tmp = *lst;
	while (tmp->prev)
		tmp = tmp->prev;
	*lst = tmp;
	while (*lst)
	{
		tmp = (*lst)->next;
		if ((*lst)->s_is_dead_to_destroy)
		{
			sem_close((*lst)->s_is_dead);
			sem_unlink(S_IS_DEAD);
		}
		if ((*lst)->s_fork_to_destroy)
		{
			sem_close((*lst)->s_fork);
			sem_unlink(S_FORK);
		}
		free(*lst);
		*lst = tmp;
	}
}
