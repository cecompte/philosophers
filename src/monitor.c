/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitor.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cecompte <cecompte@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/21 13:18:47 by cecompte          #+#    #+#             */
/*   Updated: 2025/11/22 16:58:22 by cecompte         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	check_if_died(t_program *program)
{
	t_philo	*philos;
	size_t	i;

	philos = program->philos;
	i = 0;
	while (i < philos[0].num_of_philos)
	{
		pthread_mutex_lock(&philos[i].meals_mutex);
		if (get_current_time() - philos[i].last_meal > philos[i].time_to_die
			&& !philos[i].eating)
		{
			pthread_mutex_unlock(&philos[i].meals_mutex);
			pthread_mutex_lock(&program->dead_mutex);
			program->dead_flag = 1;
			pthread_mutex_unlock(&program->dead_mutex);
			return (print(program, &philos[i], "has died", 2));
		}
		pthread_mutex_unlock(&philos[i].meals_mutex);
		i++;
	}
	return (0);
}

int	check_all_eaten(t_program *program)
{
	t_philo	*philos;
	size_t	i;

	philos = program->philos;
	if (!philos[0].num_times_to_eat)
		return (0);
	i = 0;
	while (i < philos[0].num_of_philos)
	{
		pthread_mutex_lock(&philos[i].meals_mutex);
		if (philos[i].meals_eaten < philos[i].num_times_to_eat)
			return (pthread_mutex_unlock(&philos[i].meals_mutex), 0);
		pthread_mutex_unlock(&philos[i].meals_mutex);
		i++;
	}
	pthread_mutex_lock(&program->dead_mutex);
	program->dead_flag = 1;
	pthread_mutex_unlock(&program->dead_mutex);
	return (print(program, &philos[0], "All philosophers have eaten", 0));
}

void	*monitor(void *arg)
{
	t_program	*program;

	program = (t_program *)arg;
	while (read_dead_flag(program) == 0)
	{
		if (check_if_died(program) || check_all_eaten(program))
			return (NULL);
		usleep(1000);
	}
	return (NULL);
}
