#include "philo.h"

bool	fork_is_taken(t_list *philo, bool left)
{
	bool	ret;
	if (left)
	{
		pthread_mutex_lock(philo->left_fork);
		ret = *philo->left_fork_is_taken;
		pthread_mutex_unlock(philo->left_fork);
	}
	else
	{
		pthread_mutex_lock(philo->right_fork);
		ret = *philo->right_fork_is_taken;
		pthread_mutex_unlock(philo->right_fork);
	}
	return (ret);
}

int	take_left_fork(t_list *philo)
{
	useconds_t		current_time;

	if (fork_is_taken(philo, true) || is_finish(philo))
		return (0);
	pthread_mutex_lock(philo->left_fork);
	*philo->left_fork_is_taken = true;
	pthread_mutex_unlock(philo->left_fork);
	current_time = get_time(philo->data->time);
	pthread_mutex_lock(&philo->data->m_print);
	if (is_dead(philo) == false)
	{
		printf("%u %ld has taken a fork\n", \
		current_time, philo->philo_nb);
	}
	pthread_mutex_unlock(&philo->data->m_print);
	return (1);
}

int	take_right_fork(t_list *philo)
{
	useconds_t		current_time;

	if (fork_is_taken(philo, false) || is_finish(philo))
		return (0);
	pthread_mutex_lock(philo->right_fork);
	*philo->right_fork_is_taken = true;
	pthread_mutex_unlock(philo->right_fork);
	current_time = get_time(philo->data->time);
	pthread_mutex_lock(&philo->data->m_print);
	if (is_dead(philo) == false)
	{
		printf("%u %ld has taken a fork\n", \
		current_time, philo->philo_nb);
	}
	pthread_mutex_unlock(&philo->data->m_print);
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
