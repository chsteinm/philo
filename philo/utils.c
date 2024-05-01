#include "philo.h"

useconds_t	get_time(useconds_t start)
{
	struct timeval	time;

	gettimeofday(&time, NULL);
	return ((time.tv_sec * 1000) + (time.tv_usec / 1000) - start);
}

bool	is_finish(t_list *philo)
{
	useconds_t		current_time;

	if (philo->data->dead || philo->data->finish_eating)
		return (true);
	current_time = get_time(philo->data->time);
	if (current_time >= philo->die_at)
	{
		if (philo->data->dead == false)
		{
			pthread_mutex_lock(&philo->data->m_dead);
			philo->data->dead = true;
			printf("%u %ld died\n", current_time, philo->philo_nb);
			pthread_mutex_unlock(&philo->data->m_dead);
		}
		return (true);
	}
	return (false);
}
