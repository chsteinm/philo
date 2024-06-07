#include "philo_bonus.h"

void	ft_usleep(useconds_t to_sleep)
{
	useconds_t	start;

	start = init_time();
	usleep(42);
	while (init_time() - start < to_sleep)
		usleep(42);
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

	current_time = get_time(philo->data->time);
	if (current_time >= philo->die_at)
	{
		sem_wait(philo->data->s_print);
		printf("%u %ld died\n", current_time, philo->philo_nb);
		sem_post(philo->data->s_dead);
		return (true);
	}
	return (false);
}
