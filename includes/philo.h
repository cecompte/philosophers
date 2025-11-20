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

# define TRUE 1
# define FALSE 0

typedef struct s_philo
{
	pthread_t		thread;
	int				id;
	// int				eating;
	int				meals_eaten;
	// int				last_meal;
	int				time_to_die;
	int				time_to_eat;
	int				time_to_sleep;
	// int				start_time;
	int				num_of_philos;
	int				num_times_to_eat;
	int				*dead;
}	t_philo;


int	init_struct(t_philo philo[], char **argv);

#endif