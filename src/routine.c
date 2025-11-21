/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cecompte <cecompte@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/20 14:35:18 by cecompte          #+#    #+#             */
/*   Updated: 2025/11/21 17:25:38 by cecompte         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	eating(t_program *program, t_philo *philo)
{
	pthread_mutex_lock(&program->forks[philo->fork_1].mutex);
	print(program, philo, "has taken a fork", 1);
	pthread_mutex_lock(&program->forks[philo->fork_2].mutex);
	print(program, philo, "has taken a fork", 1);
	philo->last_meal = get_current_time();
	print(program, philo, "is eating", 1);
	philo->eating = 1;
	usleep(philo->time_to_eat * 1000);
	philo->meals_eaten++;
	philo->eating = 0;
	pthread_mutex_unlock(&program->forks[philo->fork_1].mutex);
	pthread_mutex_unlock(&program->forks[philo->fork_2].mutex);
	return (0);
}

int	read_dead_flag(t_program *program)
{
	int	is_dead;

	pthread_mutex_lock(&program->dead_mutex);
	is_dead = program->dead_flag;
	pthread_mutex_unlock(&program->dead_mutex);
	return (is_dead);
}

int	one_philo(t_program *program, t_philo *philo)
{
	if (philo->num_of_philos == 1)
	{
		pthread_mutex_lock(&program->forks[0].mutex);
		print(program, philo, "has taken a fork", 1);
		usleep(philo->time_to_die * 1000);
		pthread_mutex_unlock(&program->forks[0].mutex);
		return (1);
	}
	return (0);
}

void	*routine(void *arg)
{
	t_thread_data	*data;
	t_philo			*philo;
	t_program		*program;

	data = (t_thread_data *)arg;
	philo = data->philo;
	program = data->program;
	if (one_philo(program, philo))
		return (NULL);
	while (read_dead_flag(program) == 0)
	{
		eating(program, philo);
		print(program, philo, "is sleeping", 1);
		usleep(philo->time_to_sleep * 1000);
		print(program, philo, "is thinking", 1);
	}
	return (NULL);
}
