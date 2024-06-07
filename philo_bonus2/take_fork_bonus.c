#include "philo_bonus.h"

void	print_fork(t_list *philo)
{
	useconds_t		current_time;

	current_time = get_time(philo->data->time);
	sem_wait(philo->data->s_print);
	printf("%u %ld has taken a fork\n", \
	current_time, philo->philo_nb);
	sem_post(philo->data->s_print);
}

void	print_think(t_list *philo)
{
	useconds_t		current_time;

	current_time = get_time(philo->data->time);
	sem_wait(philo->data->s_print);
	printf("%u %ld is thinking\n", \
	current_time, philo->philo_nb);
	sem_post(philo->data->s_print);
	philo->think = true;
}

// void	*take_fork(void *arg)
// {
// 	t_list *philo;

// 	philo = (t_list *)arg;
// 	sem_wait(philo->data->s_forks);
// 	print_fork(philo);
// 	sem_wait(philo->data->s_forks);
// 	print_fork(philo);
// 	sem_wait(philo->s_fork);
// 	philo->fork_taken = true;
// 	sem_post(philo->s_fork);
// 	return (NULL);
// }

// bool	fork_is_taken(t_list *philo)
// {
// 	bool	ret;

// 	ft_usleep(5);
// 	sem_wait(philo->s_fork);
// 	ret = philo->fork_taken;
// 	sem_post(philo->s_fork);
// 	return (ret);
// }

int	take_forks_or_think(t_list *philo)
{
	// if (is_finish(philo) == true)
	// 	return (0);
	// if (pthread_create(&philo->th_fork, NULL, &take_fork, philo) != 0)
	// 	return (EXIT_FAILURE);
	print_think(philo);
	sem_wait(philo->data->s_forks);
	// printf("HELOO\n");
	print_fork(philo);
	sem_wait(philo->data->s_forks);
	print_fork(philo);
	sem_wait(philo->s_fork);
	philo->fork_taken = false;
	sem_post(philo->s_fork);
	// if (pthread_join(philo->th_fork, NULL) != 0)
	// 	return (EXIT_FAILURE);
	// if (is_finish(philo) == true)
	// 	return (0);
	// if (pthread_create(&philo->th_fork, NULL, &take_fork, philo) != 0)
	// 	return (EXIT_FAILURE);
	// while (fork_is_taken(philo) == false)
	// 	if (philo->think == false)
	// 		print_think(philo);
	// sem_wait(philo->s_fork);
	// philo->fork_taken = false;
	// sem_post(philo->s_fork);
	return (EXIT_SUCCESS);
}
