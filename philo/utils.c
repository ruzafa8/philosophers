/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aruzafa- <aruzafa-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/01 17:21:40 by aruzafa-          #+#    #+#             */
/*   Updated: 2023/05/13 16:56:16 by aruzafa-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	philo_print(int id, t_data *data, char *status)
{
	u_int64_t	time;

	time = philo_current_time() - data->t0;
	printf("%-6llu %-3d %s\n", time, id, status);
}

void	increase_num_philos_eaten(t_data *data)
{
	pthread_mutex_lock(&(data->mutex_num_philos_eaten));
	data->num_philos_eaten++;
	pthread_mutex_unlock(&(data->mutex_num_philos_eaten));
}

void	set_fork(t_philo *fork, int value)
{
	pthread_mutex_lock(&(fork->mutex_fork));
	fork->fork = value;
	pthread_mutex_unlock(&(fork->mutex_fork));
}

uint64_t	philo_current_time(void)
{
	struct timeval	time;

	gettimeofday(&time, 0);
	return ((time.tv_sec * ((uint64_t)1000)) + (time.tv_usec / 1000));
}

void	*philo_calloc(size_t len)
{
	void	*ptr;

	ptr = malloc(len);
	if (!ptr)
		return ((void *) 0);
	memset(ptr, 0, len);
	return (ptr);
}
