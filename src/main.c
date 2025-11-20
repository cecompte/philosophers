/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cecompte <cecompte@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/19 19:26:32 by cecompte          #+#    #+#             */
/*   Updated: 2025/11/20 13:18:57 by cecompte         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	print_philo(t_philo philo[])
{
    int i;
	
	i = 4;
	printf("Id: %d\n", philo[4].id);
    printf("Num of philos: %d\n", philo[4].num_of_philos);
    printf("Time to die: %d\n", philo[4].time_to_die);
    printf("Time to eat: %d\n", philo[4].time_to_eat);
    printf("Time to sleep: %d\n", philo[4].time_to_sleep);
    printf("Num times to eat: %d\n", philo[4].num_times_to_eat);
    printf("Meals eaten: %d\n", philo[4].meals_eaten);
    return (0);
}
int	 main(int argc, char **argv)
{
    t_philo	philo[200];

    if (argc < 5)
        return (printf("Error: Wrong number of arguments\n"));
    init_struct(philo, argv);
    print_philo(philo);
    return (0);
}