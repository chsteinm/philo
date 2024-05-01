#include "philo.h"

int	take_left_fork(t_list *philo)
{
	if (*philo->left_fork_is_taken || is_finish(philo))
		return (0);
	pthread_mutex_lock(philo->left_fork);
	*philo->left_fork_is_taken = true;
	pthread_mutex_unlock(philo->left_fork);
	printf("%u %ld has taken a fork\n", \
	get_time(philo->data->time), philo->philo_nb);
	return (1);
}

int	take_right_fork(t_list *philo)
{
	if (*philo->right_fork_is_taken || is_finish(philo))
		return (0);
	pthread_mutex_lock(philo->right_fork);
	*philo->right_fork_is_taken = true;
	pthread_mutex_unlock(philo->right_fork);
	printf("%u %ld has taken a fork\n", \
	get_time(philo->data->time), philo->philo_nb);
	return (1);
}

void	take_right_fork_or_think(t_list *philo)
{
	if (!is_finish(philo) && take_right_fork(philo) == 0)
	{
		if (philo->think == false)
			print_and_think(philo);
		while (!is_finish(philo) && take_right_fork(philo) == 0)
			usleep(5);
	}
}

void	take_left_fork_or_think(t_list *philo)
{
	if (!is_finish(philo) && take_left_fork(philo) == 0)
	{
		if (philo->think == false)
			print_and_think(philo);
		while (!is_finish(philo) && take_left_fork(philo) == 0)
			usleep(5);
	}
}
