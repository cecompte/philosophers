/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cecompte <cecompte@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/20 14:35:18 by cecompte          #+#    #+#             */
/*   Updated: 2025/11/21 16:24:25 by cecompte         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	eating(t_philo *philo)
{
	print(philo, "is eating", 1);
	philo->eating = 1;
	usleep(philo->time_to_eat * 1000);
	philo->meals_eaten++;
	philo->last_meal = get_current_time();
	philo->eating = 0;
	return (0);
}

void	*routine(void *arg)
{
	// wait until all threads are created to start simulation ?
	t_thread_data	*data;
	t_philo			*philo;
	t_fork			*forks;
	int				right;
	int				left;
    
   	data = (t_thread_data *)arg;
	philo = data->philo;
	forks = data->program->forks;

	right = philo->id - 1;
	if (philo->id == philo->num_of_philos)
		left = 0;
	else
		left = philo->id;

	while (data->program->dead_flag == 0)
	{
    	pthread_mutex_lock(&forks[right].mutex);
		print(philo, "has taken a fork", 1);
		pthread_mutex_lock(&forks[left].mutex);
		print(philo, "has taken a fork", 1);
		eating(philo);
		pthread_mutex_unlock(&forks[right].mutex);
		pthread_mutex_unlock(&forks[left].mutex);
		print(philo, "is sleeping", 1);
		usleep(philo->time_to_sleep * 1000);
		print(philo, "is thinking", 1);
	}
	return (NULL);
}

