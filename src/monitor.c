/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitor.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cecompte <cecompte@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/21 13:18:47 by cecompte          #+#    #+#             */
/*   Updated: 2025/11/21 16:21:03 by cecompte         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	check_if_died(t_philo philos[])
{
	int	i;

	i = 0;
	while (i < philos[0].num_of_philos)
	{
		if (get_current_time() - philos[i].last_meal < philos[i].time_to_die
			&& !philos[i].eating)
			return (print(&philos[i], "has died", 1));
		i++;
	}
	return (0);
}

int	check_all_eaten(t_philo philos[])
{
	int	i;

	i = 0;
	while (i < philos[0].num_of_philos)
	{
		if (philos[i].meals_eaten < philos[i].num_times_to_eat)
			return (0);
		i++;
	}
	return (print(&philos[i], "All philosophers have eaten", 0));
}

void	*monitor(void *arg)
{
	t_program	*program;
	t_philo		*philos;
	int	i;

	program = (t_program *)arg;
	philos = program->philos;
	i = 0;
	while (program->dead_flag == 0)
	{
		if (check_if_died(philos) || check_all_eaten(philos))
			program->dead_flag == 1;
	}
	return (NULL);
}