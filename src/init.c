/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cecompte <cecompte@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/20 11:45:52 by cecompte          #+#    #+#             */
/*   Updated: 2025/11/21 17:33:13 by cecompte         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	is_valid(const char *nptr, size_t *result)
{
	int		i;

	i = 0;
	if (nptr[i] == '+')
		i++;
	while (nptr[i] >= '0' && nptr[i] <= '9')
	{
		if (*result > INT_MAX / 10 || (*result == INT_MAX / 10
				&& nptr[i] - '0' > 7))
			return (0);
		*result = *result * 10 + (nptr[i++] - '0');
	}
	if ((nptr[i] < '0' || nptr[i] > '9') && nptr[i])
		return (0);
	return (1);
}

int	check_args(char **argv, size_t values[])
{
	int	i;

	i = -1;
	while (++i < 4)
	{
		if (!is_valid(argv[i + 1], &values[i]) || !values[i])
			return (printf("Error: Invalid argument\n"));
	}
	if (argv[5] && !is_valid(argv[5], &values[4]))
		return (printf("Error: Invalid argument\n"));
	if (values[0] > 200)
		return (printf("Error: Too many philosophers\n"));
	return (0);
}
void	set_fork_order(t_philo *philo)
{
	int	left;
	int	right;
	
	right = philo->id - 1;
	if (philo->id == (int)philo->num_of_philos)
		left = 0;
	else
		left = philo->id;
	if (philo->id % 2 == 0) //even number -> pick right fork first (same as philo ID number)
	{
		philo->fork_1 = right;
		philo->fork_2 = left;
	}
	else //odd number -> pick left fork first (philo ID number + 1)
	{
		philo->fork_1 = left;
		philo->fork_2 = right;
	}
}
	
int	init_arrays(t_philo philos[], t_fork forks[], char **argv)
{
	size_t	values[5];
	size_t	i;

	memset(values, 0, sizeof(values));
	if (check_args(argv, values))
		return (1);
	memset(forks, 0, values[0] * sizeof(t_fork));
	memset(philos, 0, values[0] * sizeof(t_philo));
	i = 0;
	while (i < values[0])
	{
		forks[i].id = i + 1;
		philos[i].num_of_philos = values[0];
		philos[i].id = i + 1;
		philos[i].time_to_die = values[1];
		philos[i].time_to_eat = values[2];
		philos[i].time_to_sleep = values[3];
		philos[i].num_times_to_eat = values[4];
		philos[i].start_time = get_current_time();
		philos[i].last_meal = get_current_time();
		set_fork_order(&philos[i]);
		i++;
	}
	return (0);
}

int	init_program(t_program *program, t_philo philos[], t_fork forks[], char **argv)
{
	program->philos = philos;
	program->forks = forks;
	program->dead_flag = 0;
    if (init_arrays(philos, forks, argv))
		return (1);
	return (0);
}

int	init_mutexes(t_program *program)
{
	t_fork	*forks;
	size_t	i;

	forks = program->forks;
	i = 0;
	while (i < program->philos[0].num_of_philos)
	{
		if (pthread_mutex_init(&forks[i].mutex, NULL))
			return (printf("pthread_mutex_init error\n"));
		i++;
	}
	if (pthread_mutex_init(&program->dead_mutex, NULL) 
		|| pthread_mutex_init(&program->print_mutex, NULL))
		return (printf("pthread_mutex_init error\n"));
	return (0);
}


