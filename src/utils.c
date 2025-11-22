/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cecompte <cecompte@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/20 15:57:28 by cecompte          #+#    #+#             */
/*   Updated: 2025/11/22 16:48:08 by cecompte         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	set_fork_order(t_philo *philo)
{
	int	left;
	int	right;

	left = philo->id - 1;
	right = philo->id % philo->num_of_philos;
	if (philo->id % 2 == 0)
	{
		philo->fork_1 = left;
		philo->fork_2 = right;
	}
	else
	{
		philo->fork_1 = right;
		philo->fork_2 = left;
	}
}

size_t	get_current_time(void)
{
	struct timeval	time;

	if (gettimeofday(&time, NULL) == -1)
		printf("gettimeofday error\n");
	return (time.tv_sec * 1000 + time.tv_usec / 1000);
}

int	print(t_program *program, t_philo *philo, char *message, int flag)
{
	pthread_mutex_lock(&program->print_mutex);
	if (read_dead_flag(program) && flag == 1)
	{
		pthread_mutex_unlock(&program->print_mutex);
		return (1);
	}
	if (flag == 1 || flag == 2)
		printf("%zu   %d %s\n", get_current_time() - philo->start_time,
			philo->id, message);
	else
		printf("%zu   %s\n", get_current_time() - philo->start_time, message);
	pthread_mutex_unlock(&program->print_mutex);
	return (1);
}
