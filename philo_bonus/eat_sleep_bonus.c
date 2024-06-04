#include "philo_bonus.h"

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
	if (philo->data->nb_of_time_philo_eat && --philo->nb_of_eat == 0)
		philo->finish_eating = true;
}

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

void	eat_n_sleep(t_list *philo)
{
	if (is_finish(philo) == true)
		return ;
	print_eat(philo);
	if (is_finish(philo) == true)
		return ;
	print_sleep(philo);
}