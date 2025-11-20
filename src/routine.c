/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cecompte <cecompte@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/20 14:35:18 by cecompte          #+#    #+#             */
/*   Updated: 2025/11/20 17:06:27 by cecompte         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	philo_died(t_philo	philo[])
{
	size_t			i;

	i = 0;
	while (i < philo[i].num_of_philos)
	{
		if (philo[i].dead == 1)
		{
			philo[i].data->dead_flag = 1;
			break;
		}
		i++;
	}
}

void	*routine(void *arg)
{
	t_philo	*philo;
    
   	philo = (t_philo *)arg;
	while (philo->meals_eaten < philo->num_times_to_eat)
	{
    	printf("%zu: %d is eating\n", philo->start_time, philo->id);
		philo->meals_eaten++;
		usleep(philo->time_to_eat * 1000);
		printf("%zu: %d is sleeping\n", philo->start_time, philo->id);
		usleep(philo->time_to_sleep * 1000);
		printf("%zu: %d is thinking\n", philo->start_time, philo->id);
	}
	return (NULL);
}
