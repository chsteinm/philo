#include "philo.h"

useconds_t	init_time()
{
	struct timeval	time;

	gettimeofday(&time, NULL);
	return ((time.tv_sec * 1000) + (time.tv_usec / 1000));
}

int	init_forks(t_data *data)
{
	data->forks = malloc(data->nb_of_philo * sizeof(bool));
	if (!data->forks)
		return (EXIT_FAILURE);
	memset((void *)data->forks, 0, data->nb_of_philo);
	return (EXIT_SUCCESS);
}

int	init_data(t_data *data, char **argv)
{
	char	*endptr;

	memset((void *)data, 0, sizeof(t_data));
	endptr = NULL;
	data->nb_of_philo = ft_strtol(argv[1], &endptr, 10);
	if (*endptr || data->nb_of_philo < 1)
		return (EXIT_FAILURE);
	data->time_to_die = ft_strtol(argv[2], &endptr, 10);
	if (*endptr || data->time_to_die < 0)
		return (EXIT_FAILURE);
	data->time_to_eat = ft_strtol(argv[3], &endptr, 10);
	if (*endptr || data->time_to_eat < 0)
		return (EXIT_FAILURE);
	data->time_to_sleep = ft_strtol(argv[4], &endptr, 10);
	if (*endptr || data->time_to_sleep < 0)
		return (EXIT_FAILURE);
	if (argv[5])
	{
		data->nb_of_time_philo_eat = ft_strtol(argv[5], &endptr, 10);
		if (*endptr || data->nb_of_time_philo_eat < 0)
			return (EXIT_FAILURE);
	}
	data->time = init_time();
	return (init_forks(data));
}

int	init_mutex(t_data *data)
{
	data->m_forks = malloc(data->nb_of_philo * sizeof(pthread_mutex_t));
	if (!data->m_forks)
		return (EXIT_FAILURE);
	data->i = -1;
	while (++data->i < data->nb_of_philo)
	{
		if (pthread_mutex_init(&data->m_forks[data->i], NULL) != 0)
			return (EXIT_FAILURE);
	}
	if (pthread_mutex_init(&data->m_dead, NULL) != 0)
			return (EXIT_FAILURE);
	data->m_dead_to_destroy = true;
	if (pthread_mutex_init(&data->m_print, NULL) != 0)
			return (EXIT_FAILURE);
	data->m_print_to_destroy = true;
	if (pthread_mutex_init(&data->m_start, NULL) != 0)
			return (EXIT_FAILURE);
	data->m_start_to_destroy = true;
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
