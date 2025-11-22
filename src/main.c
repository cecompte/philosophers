/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cecompte <cecompte@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/19 19:26:32 by cecompte          #+#    #+#             */
/*   Updated: 2025/11/22 16:28:12 by cecompte         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

/*
int	print_philo(t_philo philos[])
{
	int		i;

	i = 0;
	printf("Data at init:\n");
	printf("Id: %d\n", philos[i].id);
	printf("Num of philos: %zu\n", philos[i].num_of_philos);
	printf("Time to die: %zu\n", philos[i].time_to_die);
	printf("Time to eat: %zu\n", philos[i].time_to_eat);
	printf("Time to sleep: %zu\n", philos[i].time_to_sleep);
	printf("Num times to eat: %zu\n", philos[i].num_times_to_eat);
	printf("Meals eaten: %zu\n", philos[i].meals_eaten);
	printf("Start time (ms): %zu\n", philos[i].start_time);
	printf("-------------\n");
	return (0);
}
*/
int	create_threads(t_philo philos[], t_program *program, pthread_t *thread)
{
	t_thread_data	data[200];
	size_t			i;

	i = 0;
	while (i < philos[0].num_of_philos)
	{
		data[i].philo = &philos[i];
		data[i].program = program;
		if (pthread_create(&philos[i].thread, NULL, routine, (void *)&data[i]))
			return (printf("pthread_create error\n"));
		i++;
	}
	if (pthread_create(thread, NULL, monitor, (void *)program))
		return (printf("pthread_create error\n"));
	return (0);
}

int	join_threads(t_philo philos[], pthread_t *thread)
{
	size_t	i;

	i = 0;
	while (i < philos[0].num_of_philos)
	{
		if (pthread_join(philos[i].thread, NULL))
			return (printf("pthread_join error\n"));
		i++;
	}
	if (pthread_join(*thread, NULL))
		return (printf("pthread_join error\n"));
	return (0);
}

int	destroy_mutexes(t_program *program)
{
	t_fork	*forks;
	size_t	i;

	i = 0;
	forks = program->forks;
	while (i < program->philos->num_of_philos)
	{
		pthread_mutex_destroy(&forks[i].mutex);
		pthread_mutex_destroy(&program->philos[i].meals_mutex);
		i++;
	}
	pthread_mutex_destroy(&program->dead_mutex);
	pthread_mutex_destroy(&program->print_mutex);
	return (0);
}

int	main(int argc, char **argv)
{
	t_program	program;
	t_philo		philos[200];
	t_fork		forks[200];
	pthread_t	monitor_thread;

	if (argc < 5)
		return (printf("Error: Wrong number of arguments\n"));
	if (init_program(&program, philos, forks, argv))
		return (1);
	if (init_mutexes(&program))
		return (1);
	if (create_threads(philos, &program, &monitor_thread))
		return (1);
	if (join_threads(philos, &monitor_thread))
		return (1);
	destroy_mutexes(&program);
	return (0);
}
