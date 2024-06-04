#include "philo.h"

void	free_and_destroy(t_data *data, t_list **philo)
{
	while (data->nb_of_philo--)
		pthread_join(data->th[data->nb_of_philo], NULL); // secu les join ?
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
	if (data->m_start_to_destroy == true)
		pthread_mutex_destroy(&data->m_start);}

void	wait_n_desync(t_list *philo)
{
	pthread_mutex_lock(&philo->data->m_start);
	pthread_mutex_unlock(&philo->data->m_start);
	if (!(philo->philo_nb % 2))
		ft_usleep(10);
}

void	*routine(void *arg)
{
	t_list	*philo;

	philo = (t_list *)arg;
	wait_n_desync(philo);
	philo->die_at = get_time(philo->data->time) + philo->data->time_to_die;
	while (!is_finish(philo))
	{
		philo->think = false;
		if (philo->philo_nb % 2)
		{
			take_right_fork_or_think(philo);
			take_left_fork_or_think(philo);
		}
		else
		{
			take_left_fork_or_think(philo);
			take_right_fork_or_think(philo);
		}
		print_and_eat(philo);
		philo->die_at = get_time(philo->data->time) + philo->data->time_to_die;
		print_and_sleep(philo);
	}
	return (NULL);
}

int	lauch_threads(t_data *data, t_list *philo_ptr)
{
	long		i;

	i = -1;
	pthread_mutex_lock(&data->m_start);
	while (++i < data->nb_of_philo)
	{
		if (pthread_create(data->th + i, NULL, &routine, philo_ptr))
		{
			pthread_mutex_unlock(&data->m_start);
			return (EXIT_FAILURE);
		}
		philo_ptr = philo_ptr->next;
		ft_usleep(10);
	}
	pthread_mutex_unlock(&data->m_start);
	return (EXIT_SUCCESS);
}

int	main(int argc, char **argv)
{
	t_data		data;
	t_list		*philo;

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
	if (lauch_threads(&data, philo) == EXIT_FAILURE)
		return (free_and_destroy(&data, &philo), EXIT_FAILURE);
	free_and_destroy(&data, &philo);
	return (EXIT_SUCCESS);
}
