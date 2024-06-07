#include "philo_bonus.h"

void	print_sleep(t_list *philo)
{
	useconds_t		current_time;

	current_time = get_time(philo->data->time);
	sem_wait(philo->data->s_print);
	printf("%u %ld is sleeping\n", \
	current_time, philo->philo_nb);
	sem_post(philo->data->s_print);
	ft_usleep(philo->data->time_to_sleep);
}

void	print_eat(t_list *philo)
{
	useconds_t		current_time;

	current_time = get_time(philo->data->time);
	sem_wait(philo->data->s_print);
	printf("%u %ld is eating\n", \
	current_time, philo->philo_nb);
	sem_post(philo->data->s_print);
	ft_usleep(philo->data->time_to_eat);
	sem_post(philo->data->s_forks);
	sem_post(philo->data->s_forks);
}