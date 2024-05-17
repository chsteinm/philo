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
	philo->s_is_dead = sem_open(S_IS_DEAD, O_CREAT, 0666, 1);
	if (philo->s_is_dead == SEM_FAILED)
		return (free_and_destroy(data, &philo), exit(EXIT_FAILURE));
	philo->s_is_dead_to_destroy = true;
	if (pthread_create(&philo->th_dead, NULL, &wait_dead, philo) != 0)
		return (free_and_destroy(data, &philo), exit(EXIT_FAILURE));
	while (0 && !is_finish(philo))
	{
		philo->think = false;
		//take_forks_or_think(philo);
	}
	return (free_and_destroy(data, &philo), exit(EXIT_SUCCESS));
}

int	lauch_lunch(t_data *data, t_list *philo)
{
	long		i;

	i = -1;
	while (++i < data->nb_of_philo)
	{
		data->pid_philo[i]= fork();
		if (data->pid_philo[i] == -1)
			return (EXIT_FAILURE); // voir comment gerer ca
		if (data->pid_philo[i] == 0)
			routine(data, philo);
		philo = philo->next;
	}
	sem_post(data->s_start);
	return (EXIT_SUCCESS);
}

int	main(int argc, char **argv)
{
	t_data		data;
	t_list		*philo;

	if (argc < 5 || argc > 6)
		return (EXIT_FAILURE);
	if (init_data(&data, argv) != EXIT_SUCCESS)
		return (EXIT_FAILURE);
	//printf("nb philo = %ld\ntime to die = %ld\ntime to eat = %ld\ntime to sleep = %ld\nnb time must eat = %ld\n", data.nb_of_philo, data.time_to_die, data.time_to_eat, data.time_to_sleep, data.nb_of_time_philo_eat);
	if (init_sem(&data) || init_philo(&data, &philo) != EXIT_SUCCESS)
		return (free_and_destroy(&data, &philo), EXIT_FAILURE);
	if (lauch_lunch(&data, philo) == EXIT_FAILURE)
		return (free_and_destroy(&data, &philo), EXIT_FAILURE);
	free_and_destroy(&data, &philo);
	return (EXIT_SUCCESS);
}
