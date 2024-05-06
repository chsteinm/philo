#ifndef PHILO_H
# define PHILO_H

# include <stdio.h>
# include <string.h>
# include <stdlib.h>
# include <unistd.h>
# include <sys/time.h>
# include <pthread.h>
# include <semaphore.h>
# include <stdbool.h>
# include <limits.h>

typedef struct s_data
{
	long			nb_of_philo;
	long			time_to_die;
	long			time_to_eat;
	long			time_to_sleep;
	long			nb_of_time_philo_eat;
	sem_t			*s_forks;
	long			nb_s_forks_to_destroy;
	sem_t			s_dead;
	bool			s_dead_to_destroy;
	sem_t			s_print;
	bool			s_print_to_destroy;
	pid_t			*pid_philo;
	useconds_t		time;
}					t_data;

typedef struct s_list
{
	pthread_t		th;
	bool			think;
	long			philo_nb;
	long			nb_of_eat;
	bool			dead;
	bool			finish_eating;
	t_data			*data;
	useconds_t		die_at;
	struct s_list	*next;
	struct s_list	*prev;
}	t_list;

void	ft_skip_wspaces(char **ptr);
int		ft_isdigit(int c);
int		ft_isalpha(int c);
long	ft_strtol(char *str, char **endptr, int base);
t_list	*ft_lstnew(t_data *data, long philo_nb);
void	ft_lstclear(t_list **lst);
void	ft_lstadd_back(t_list **lst, t_list *new);

int			init_data(t_data *data, char **argv);
int			init_mutex(t_data *data);
int			init_philo(t_data *data, t_list **philo);
useconds_t	init_time();

void	take_right_fork_or_think(t_list *philo);
void	take_left_fork_or_think(t_list *philo);
void	print_and_think(t_list *philo);
void	print_and_sleep(t_list *philo);
void	print_and_eat(t_list *philo);

useconds_t	get_time(useconds_t start);
bool		is_finish(t_list *philo);

#endif