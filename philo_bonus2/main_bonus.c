#include "philo_bonus.h"

void	free_and_destroy(t_data *data, t_list **philo)
{
	free(data->pid_philo);
	ft_lstclear(philo);
	if (data->s_dead_to_destroy == true)
	{
		sem_close(data->s_dead);
		sem_unlink(S_DEAD);
	}
	if (data->s_forks_to_destroy == true)
	{
		sem_close(data->s_forks);
		sem_unlink(S_FORKS);
	}
	if (data->s_print_to_destroy == true)
	{
		sem_close(data->s_print);
		sem_unlink(S_PRINT);
	}
	if (data->s_start_to_destroy == true)
	{
		sem_close(data->s_start);
		sem_unlink(S_START);
	}
	if (data->s_finish_to_destroy == true)
	{
		sem_close(data->s_finish);
		sem_unlink(S_FINISH);
	}
}

void	*wait_dead(void *arg)
{
	t_list	*philo;

	philo = (t_list *)arg;
	sem_wait(philo->data->s_dead);
	sem_post(philo->data->s_dead);
	sem_wait(philo->s_is_dead);
	philo->is_dead = true;
	sem_post(philo->s_is_dead);
	return (NULL);
}

void	routine(t_data *data, t_list *philo)
{
	sem_wait(data->s_start);
	if (pthread_create(&philo->th_dead, NULL, &wait_dead, philo) != 0)
		return (free_and_destroy(data, &philo), exit(EXIT_FAILURE));
	philo->die_at = get_time(philo->data->time) + philo->data->time_to_die;
	while (is_finish(philo) == false)
	{
		philo->think = false;
		take_forks_or_think(philo);
		print_eat(philo);
		philo->die_at = get_time(philo->data->time) + philo->data->time_to_die;
		if (philo->data->nb_of_time_philo_eat && --philo->nb_of_eat == 0)
		{
			sem_post(data->s_finish);
			// exit(0);
			break ;
		}
		print_sleep(philo);
	}
	pthread_join(philo->th_dead, NULL);
	return (free_and_destroy(data, &philo), exit(0));
}

void	*wait_finish(void *arg)
{
	long	i;
	t_data	*data;

	data = (t_data *)arg;
	i = -1;
	while (++i < data->nb_of_philo)
	{
		sem_wait(data->s_finish);
	}
	i = -1;
	while (++i < data->nb_of_philo)
		sem_post(data->s_dead);
	return (NULL);
}

int	finish_lauch(t_data *data)
{
	long	i;

	if (pthread_create(&data->th_finish, NULL, &wait_finish, data) != 0)
		return (EXIT_FAILURE);
	sem_wait(data->s_dead);
	i = -1;
	while (++i < data->nb_of_philo)
		sem_post(data->s_forks);
	i = -1;
	while (++i < data->nb_of_philo)
		// kill(data->pid_philo[i], SIGTERM);
		waitpid(data->pid_philo[i], NULL, 0);
	while (i--)
		sem_post(data->s_finish);
	pthread_join(data->th_finish, NULL);
	return (EXIT_SUCCESS);
}

int	lauch_lunch(t_data *data, t_list *philo)
{
	long		i;

	i = -1;
	while (++i < data->nb_of_philo)
	{
		data->pid_philo[i]= fork();
		if (data->pid_philo[i] == -1)
		{
				while (i--)
					kill(data->pid_philo[i], SIGTERM);
				return (EXIT_FAILURE);
		}
		if (data->pid_philo[i] == 0)
			routine(data, philo);
		philo = philo->next;
	}
	ft_usleep(10);
	while (i--)
	{
		ft_usleep(1);
		sem_post(data->s_start);
	}
	return (finish_lauch(data));
}

int	main(int argc, char **argv)
{
	t_data		data;
	t_list		*philo;

	if (argc < 5 || argc > 6)
		return (EXIT_FAILURE);
	if (init_data(&data, argv) != EXIT_SUCCESS)
		return (EXIT_FAILURE);
	if (init_sem(&data) || init_philo(&data, &philo) != EXIT_SUCCESS)
		return (free_and_destroy(&data, &philo), EXIT_FAILURE);
	if (lauch_lunch(&data, philo) == EXIT_FAILURE)
		return (free_and_destroy(&data, &philo), EXIT_FAILURE);
	free_and_destroy(&data, &philo);
	return (EXIT_SUCCESS);
}
