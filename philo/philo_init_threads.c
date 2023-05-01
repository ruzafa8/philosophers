/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_init_threads.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aruzafa- <aruzafa-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/01 17:18:29 by aruzafa-          #+#    #+#             */
/*   Updated: 2023/05/01 21:08:09 by aruzafa-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	philo_print(t_philo *philo, char *status)
{
	u_int64_t	time;

	pthread_mutex_lock(&(philo->data->mutex_print));
	time = philo_current_time() - philo->data->t0;
	printf("%-6llu %-3d %s\n", time, philo->id, status);
	pthread_mutex_unlock(&(philo->data->mutex_print));
}

static int	try_take_fork(int id, t_philo *philo)
{
	int	taken;

	pthread_mutex_lock(&(philo->mutex_fork));
	taken = 0;
	if (!philo->fork)
	{
		philo->fork = 1;
		pthread_mutex_lock(&(philo->data->mutex_print));
		printf("%-6llu %-3d chopstick %d taken.\n", philo_current_time() - philo->data->t0, id, philo->id);
		pthread_mutex_unlock(&(philo->data->mutex_print));
		taken = 1;
	}
	pthread_mutex_unlock(&(philo->mutex_fork));
	return (taken);
}

static void	*philo_routine(void *params)
{
	t_philo	*philo;
	t_philo *next_philo;
	int		taken;
	int		taken2;

	philo = (t_philo *) params;
	next_philo = philo->next;
	if (next_philo == 0)
		next_philo = philo->data->philos;
	if (philo->id % 2 == 0)
		taken = try_take_fork(philo->id, next_philo);
	else
		taken = try_take_fork(philo->id, philo);
	if (taken)
	{
		if (philo->id % 2 == 0)
			taken2 = try_take_fork(philo->id, philo);
		else
			taken2 = try_take_fork(philo->id, next_philo);
	}
	if (taken && taken2)
	{
		philo_print(philo, "is eating");
	}
	else
	{
		philo_print(philo, "is thinking");
	}
	//philo_print(philo, "Am alive!!!!!!!!!!!!!");
	return (0);
}

void	philo_init_threads(t_data *data)
{
	t_philo	*philo;

	philo = data->philos;
	while (philo)
	{
		pthread_create(&(philo->thread), 0, philo_routine, philo);
		philo = philo->next;
	}
}
