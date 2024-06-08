/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_bonus.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chrstein <chrstein@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/08 05:24:13 by chrstein          #+#    #+#             */
/*   Updated: 2024/06/08 05:27:37 by chrstein         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_BONUS_H
# define PHILO_BONUS_H

# include <stdio.h>
# include <string.h>
# include <stdlib.h>
# include <unistd.h>
# include <sys/time.h>
# include <pthread.h>
# include <semaphore.h>
# include <stdbool.h>
# include <limits.h>
# include <fcntl.h>
# include <sys/types.h>
# include <sys/wait.h>
# include <signal.h>

# define S_FORKS "forks"
# define S_FORK "fork"
# define S_DEAD "dead"
# define S_IS_DEAD "is_dead"
# define S_PRINT "print"
# define S_START "start"
# define S_FINISH "finish"

typedef struct s_data
{
	long			nb_of_philo;
	long			time_to_die;
	long			time_to_eat;
	long			time_to_sleep;
	long			nb_of_time_philo_eat;
	sem_t			*s_forks;
	bool			s_forks_to_destroy;
	sem_t			*s_dead;
	bool			s_dead_to_destroy;
	sem_t			*s_finish;
	bool			s_finish_to_destroy;
	pthread_t		th_finish;
	sem_t			*s_print;
	bool			s_print_to_destroy;
	sem_t			*s_start;
	bool			s_start_to_destroy;
	pid_t			*pid_philo;
	useconds_t		time;
}					t_data;

typedef struct s_list
{
	pthread_t		th_dead;
	pthread_t		th_fork;
	bool			think;
	long			philo_nb;
	long			nb_of_eat;
	sem_t			*s_is_dead;
	bool			s_is_dead_to_destroy;
	bool			is_dead;
	sem_t			*s_fork;
	bool			s_fork_to_destroy;
	bool			fork_taken;
	t_data			*data;
	useconds_t		die_at;
	struct s_list	*next;
	struct s_list	*prev;
}	t_list;

void		ft_skip_wspaces(char **ptr);
int			ft_isdigit(int c);
int			ft_isalpha(int c);
long		ft_strtol(char *str, char **endptr, int base);
t_list		*ft_lstnew(t_data *data, long philo_nb);
void		ft_lstclear(t_list **lst);
void		ft_lstadd_back(t_list **lst, t_list *new);

int			init_data(t_data *data, char **argv);
int			init_sem(t_data *data);
int			init_philo(t_data *data, t_list **philo);
useconds_t	init_time(void);

void		*wait_dead(void *arg);
void		*wait_finish(void *arg);

void		take_forks_or_think(t_list *philo);
void		print_and_think(t_list *philo);
void		print_and_sleep(t_list *philo);
void		print_and_eat(t_list *philo);

void		print_eat(t_list *philo);
void		print_sleep(t_list *philo);

useconds_t	get_time(useconds_t start);
bool		is_finish(t_list *philo);
void		ft_usleep(useconds_t to_sleep);

void		free_and_destroy(t_data *data, t_list **philo);

#endif
