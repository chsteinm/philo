#include "philo.h"

t_list	*ft_lstnew(t_data *data, long philo_nb)
{
	t_list	*new;

	new = malloc(sizeof(t_list) * 1);
	if (!new)
		return (NULL);
	new->philo_nb = philo_nb;
	new->data = data;
	new->nb_of_eat = new->data->nb_of_time_philo_eat;
	new->finish_eating = false;
	new->think = false;
	new->next = NULL;
	new->prev = NULL;
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
	while (*lst)
	{
		tmp = (*lst)->next;
		free(*lst);
		*lst = tmp;
	}
}