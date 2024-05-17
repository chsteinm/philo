#include "philo_bonus.h"

useconds_t	init_time()
{
	struct timeval	time;

	gettimeofday(&time, NULL);
	return ((time.tv_sec * 1000) + (time.tv_usec / 1000));
}

int	init_pids_and_forks(t_data *data)
{
	data->pid_philo = malloc(data->nb_of_philo * sizeof(pid_t));
	if (!data->pid_philo)
		return (EXIT_FAILURE);
	memset((void *)data->pid_philo, 0, data->nb_of_philo);
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
	return (init_pids_and_forks(data));
}

int	init_sem(t_data *data)
{
	data->s_forks = sem_open(S_FORKS, O_CREAT, 0666, data->nb_of_philo);
	if (data->s_forks == SEM_FAILED)
		return (EXIT_FAILURE);
	data->s_forks_to_destroy = true;
	data->s_dead = sem_open(S_DEAD, O_CREAT, 0666, 0);
	if (data->s_dead == SEM_FAILED)
		return (EXIT_FAILURE);
	data->s_dead_to_destroy = true;
	data->s_print = sem_open(S_PRINT, O_CREAT, 0666, 1);
	if (data->s_print == SEM_FAILED)
		return (EXIT_FAILURE);
	data->s_print_to_destroy = true;
	data->s_start = sem_open(S_START, O_CREAT, 0666, 0);
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
