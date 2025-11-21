/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cecompte <cecompte@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/20 15:57:28 by cecompte          #+#    #+#             */
/*   Updated: 2025/11/21 13:36:24 by cecompte         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

size_t	get_current_time(void)
{
	struct timeval time;

	if (gettimeofday(&time, NULL) == -1)
		printf("gettimeofday error\n");
	return (time.tv_sec * 1000 + time.tv_usec / 1000);
}

int	print(t_philo *philo, char *message, int flag)
{
	if (flag == 1)
		printf("%zu   %d %s\n", get_current_time() - philo->start_time, philo->id, message);
	else
		printf("%zu   %s\n", get_current_time() - philo->start_time, message);
	return (1);
}

