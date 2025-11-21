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

// Basic resources
typedef struct s_fork
{
	pthread_mutex_t		mutex;
	int					id;
}	t_fork;

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
}	t_philo;

// Shared program state
typedef struct s_program
{
    t_philo         	*philos;		// Array of all philosophers
    t_fork          	*forks;			// Array of all forks
    int             	dead_flag;		// Shared death flag
    pthread_mutex_t 	dead_mutex;		// Protect dead_flag reads/writes
    pthread_mutex_t 	print_mutex;	// Protect printf calls
} t_program;

// Thread arguments
typedef struct s_thread_data
{
	t_philo				*philo;			// This specific philosopher
	t_program			*program;		// Access to all shared resources
} t_thread_data;

int			init_program(t_program *program, t_philo philos[], t_fork forks[], char **argv);
int			init_mutexes(t_fork forks[], int size);
void		*routine(void *arg);
void		*monitor(void *arg);
size_t		get_current_time(void);
int			print(t_philo *philo, char *message, int flag);
#endif