/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_init_threads.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aruzafa- <aruzafa-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/01 17:18:29 by aruzafa-          #+#    #+#             */
/*   Updated: 2023/05/01 20:53:36 by aruzafa-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static void	philo_print(t_philo *philo, char *status)
{
	u_int64_t	time;

	pthread_mutex_lock(&(philo->data->mutex_print));
	time = philo_current_time() - philo->data->t0;
	printf("%-6llu %-3d %s\n", time, philo->id, status);
	pthread_mutex_unlock(&(philo->data->mutex_print));
}

static void	try_take_fork(t_philo *philo)
{
	pthread_mutex_lock(&(philo->mutex_fork));
	if (!philo->fork)
	{
		philo->fork = 1;
		philo_print(philo, "soy subnormal");
	}
	pthread_mutex_unlock(&(philo->mutex_fork));
}

static void	*philo_routine(void *params)
{
	t_philo	*philo;

	philo = (t_philo *) params;
	try_take_fork(philo);
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
