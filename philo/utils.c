#include "philo.h"

void	ft_usleep(useconds_t to_sleep)
{
	useconds_t	start;

	start = init_time();
	usleep(42);
	while (init_time() - start < to_sleep)
		usleep(42);
}

bool	is_dead(t_list *philo)
{
	bool	ret;

	pthread_mutex_lock(&philo->data->m_dead);
	ret = philo->data->dead;
	pthread_mutex_unlock(&philo->data->m_dead);
	return (ret);
}

useconds_t	get_time(useconds_t start)
{
	struct timeval	time;

	gettimeofday(&time, NULL);
	return ((time.tv_sec * 1000) + (time.tv_usec / 1000) - start);
}

bool	is_finish(t_list *philo)
{
	useconds_t		current_time;

	if (is_dead(philo) || philo->finish_eating)
		return (true);
	current_time = get_time(philo->data->time);
	if (current_time >= philo->die_at)
	{
		if (is_dead(philo) == false)
		{
			pthread_mutex_lock(&philo->data->m_dead);
			philo->data->dead = true;
			pthread_mutex_unlock(&philo->data->m_dead);
			pthread_mutex_lock(&philo->data->m_print);
			printf("%u %ld died\n", current_time, philo->philo_nb);
			pthread_mutex_unlock(&philo->data->m_print);
		}
		return (true);
	}
	return (false);
}
