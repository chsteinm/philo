#include "philo.h"

void	ft_usleep(useconds_t to_sleep)
{
	useconds_t	start;

	start = init_time();
	usleep(5);
	while (init_time() - start < to_sleep)
		usleep(5);
}

void	print_and_eat(t_list *philo)
{
	useconds_t	current_time;

	if (is_finish(philo))
		return ;
	current_time = get_time(philo->data->time);
	pthread_mutex_lock(&philo->data->m_print);
	if (philo->data->dead == false)
	{
		printf("%u %ld is eating\n", \
		current_time, philo->philo_nb);
	}
	pthread_mutex_unlock(&philo->data->m_print);
	ft_usleep(philo->data->time_to_eat);
	if (philo->data->nb_of_time_philo_eat && --philo->nb_of_eat == 0)
		philo->finish_eating = true;
	*philo->right_fork_is_taken = false;
	*philo->left_fork_is_taken = false;

}

void	print_and_think(t_list *philo)
{
	useconds_t	current_time;

	if (is_finish(philo))
		return ;
	current_time = get_time(philo->data->time);
	pthread_mutex_lock(&philo->data->m_print);
	if (philo->data->dead == false)
	{
		printf("%u %ld is thinking\n", \
		current_time, philo->philo_nb);
	}
	pthread_mutex_unlock(&philo->data->m_print);
	philo->think = true;
}

void	print_and_sleep(t_list *philo)
{
	useconds_t	current_time;

	if (is_finish(philo))
		return ;
	current_time = get_time(philo->data->time);
	pthread_mutex_lock(&philo->data->m_print);
	if (philo->data->dead == false)
	{
		printf("%u %ld is sleeping\n", \
		current_time, philo->philo_nb);
	}
	pthread_mutex_unlock(&philo->data->m_print);
	ft_usleep(philo->data->time_to_sleep);
}
