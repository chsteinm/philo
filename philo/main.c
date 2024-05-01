#include "philo.h"

void	free_and_destroy(t_data *data, t_list **philo)
{
	while (data->nb_of_philo--)
		pthread_join(data->th[data->nb_of_philo], NULL);
	free(data->th);
	ft_lstclear(philo);
	while (data->i--)
		pthread_mutex_destroy(&data->m_forks[data->i]);
	free(data->m_forks);
	free(data->forks);
	if (data->m_dead_to_destroy == true)
		pthread_mutex_destroy(&data->m_dead);
	if (data->m_print_to_destroy == true)
		pthread_mutex_destroy(&data->m_print);
}

void	*routine(void *arg)
{
	t_list	*philo;

	philo = (t_list *)arg;
	philo->die_at = get_time(philo->data->time) + philo->data->time_to_die;
	while (!is_finish(philo))
	{
		philo->think = false;
		if (philo->philo_nb % 2)
		{
			take_left_fork_or_think(philo);
			take_right_fork_or_think(philo);
		}
		else
		{
			take_right_fork_or_think(philo);
			take_left_fork_or_think(philo);
		}
		if (is_finish(philo))
			return (NULL);
		print_and_eat(philo);
		philo->die_at = get_time(philo->data->time) + philo->data->time_to_die;
		print_and_sleep(philo);
	}
	return (NULL);
}

int	main(int argc, char **argv)
{
	t_data		data;
	t_list		*philo;
	t_list		*philo_ptr;
	long		i;

	if (argc < 5 || argc > 6)
		return (EXIT_FAILURE);
	if (init_data(&data, argv) != EXIT_SUCCESS)
		return (EXIT_FAILURE);
	//printf("nb philo = %ld\ntime to die = %ld\ntime to eat = %ld\ntime to sleep = %ld\nnb time must eat = %ld\n", data.nb_of_philo, data.time_to_die, data.time_to_eat, data.time_to_sleep, data.nb_of_time_philo_eat);
	if (init_mutex(&data) || init_philo(&data, &philo) != EXIT_SUCCESS)
		return (free_and_destroy(&data, &philo), EXIT_FAILURE);
	data.th = malloc(data.nb_of_philo * sizeof(pthread_t));
	if (!data.th)
		return (free_and_destroy(&data, &philo), EXIT_FAILURE);
	i = -1;
	philo_ptr = philo;
	while (++i < data.nb_of_philo)
	{
		if (pthread_create(data.th + i, NULL, &routine, philo_ptr))
				return (free_and_destroy(&data, &philo), EXIT_FAILURE);
		philo_ptr = philo_ptr->next;
	}
	free_and_destroy(&data, &philo);
	return (EXIT_SUCCESS);
}
