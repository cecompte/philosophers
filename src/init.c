/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cecompte <cecompte@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/20 11:45:52 by cecompte          #+#    #+#             */
/*   Updated: 2025/11/20 17:11:22 by cecompte         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	ft_isdigit(int c)
{
	if ((c >= '0') && (c <= '9'))
		return (1);
	else
		return (0);
}

int	is_valid(const char *nptr, size_t *result)
{
	int		i;

	i = 0;
	if (nptr[i] == '+')
		i++;
	while (ft_isdigit(nptr[i]))
	{
		if (*result > INT_MAX / 10 || (*result == INT_MAX / 10
				&& nptr[i] - '0' > 7))
			return (0);
		*result = *result * 10 + (nptr[i++] - '0');
	}
	if (!ft_isdigit(nptr[i]) && nptr[i])
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

int	init_philo(t_philo philo[], t_data *data, char **argv)
{
	size_t	values[5];
	size_t	i;

	memset(values, 0, sizeof(values));
	if (check_args(argv, values))
		return (1);
	i = 0;
	data->dead_flag = 0;
	while (i < values[0])
	{
		philo[i].num_of_philos = values[0];
		philo[i].id = i + 1;
		philo[i].time_to_die = values[1];
		philo[i].time_to_eat = values[2];
		philo[i].time_to_sleep = values[3];
		philo[i].num_times_to_eat = values[4];
		philo[i].meals_eaten = 0;
		philo[i].start_time = get_current_time();
		philo[i].dead = 0;
		philo[i].data = data;
		i++;
	}
	return (0);
}


