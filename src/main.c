/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cecompte <cecompte@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/19 19:26:32 by cecompte          #+#    #+#             */
/*   Updated: 2025/11/20 16:43:07 by cecompte         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	print_philo(t_philo philo[])
{
    int i;
	
	i = 4;
    printf("Data at init:\n");
	printf("Id: %d\n", philo[4].id);
    printf("Num of philos: %zu\n", philo[4].num_of_philos);
    printf("Time to die: %zu\n", philo[4].time_to_die);
    printf("Time to eat: %zu\n", philo[4].time_to_eat);
    printf("Time to sleep: %zu\n", philo[4].time_to_sleep);
    printf("Num times to eat: %zu\n", philo[4].num_times_to_eat);
    printf("Meals eaten: %d\n", philo[4].meals_eaten);
    printf("Start time (ms): %zu\n", philo[4].start_time);
    printf("-------------\n");
    return (0);
}

int	 main(int argc, char **argv)
{
    t_philo	philo[200];
    t_data  data;
    size_t  i;

    if (argc < 5)
        return (printf("Error: Wrong number of arguments\n"));
    if (init_philo(philo, &data, argv))
        return (1);
    print_philo(philo);
    i = 0;
    while (i < philo[0].num_of_philos)
    {
        pthread_create(&philo[i].thread, NULL, routine, (void*)&philo[i]);
        i++;
    }
    i = 0;
    while (i < philo[0].num_of_philos)
    {
        pthread_join(philo[i].thread, NULL);
        i++;
    }
    return (0);
}