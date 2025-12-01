/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cecompte <cecompte@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/19 19:27:15 by cecompte          #+#    #+#             */
/*   Updated: 2025/11/19 19:27:15 by cecompte         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <stdlib.h>
# include <stdio.h>
# include <unistd.h>
# include <pthread.h>
# include <limits.h>
# include <string.h>
# include <sys/time.h>

# define TRUE 1
# define FALSE 0

typedef struct s_philo
{
	pthread_t			thread;
	int					id;
	int					eating;
	size_t				meals_eaten;
	size_t				last_meal;
	size_t				time_to_die;
	size_t				time_to_eat;
	size_t				time_to_sleep;
	size_t				start_time;
	size_t				num_of_philos;
	size_t				num_times_to_eat;
	int					fork_1;
	int					fork_2;
	pthread_mutex_t		meals_mutex;
	struct s_program	*program;
}	t_philo;

typedef struct s_fork
{
	pthread_mutex_t		mutex;
	int					id;
}	t_fork;

typedef struct s_program
{
	t_philo				*philos;
	t_fork				*forks;
	int					dead_flag;
	pthread_mutex_t		dead_mutex;
	pthread_mutex_t		print_mutex;
}	t_program;

int			init_program(t_program *program, t_philo philos[],
				t_fork forks[], char **argv);
int			init_mutexes(t_program *program);
void		set_fork_order(t_philo *philo);
int			read_dead_flag(t_program *program);
void		*routine(void *arg);
void		*monitor(void *arg);
size_t		get_current_time(void);
int			print(t_philo *philo, char *message, int flag);
#endif