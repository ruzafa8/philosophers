/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_init_threads.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aruzafa- <aruzafa-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/01 17:18:29 by aruzafa-          #+#    #+#             */
/*   Updated: 2023/05/01 21:41:24 by aruzafa-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static void	philo_print(int id, t_philo *philo, char *status)
{
	u_int64_t	time;

	pthread_mutex_lock(&(philo->data->mutex_print));
	time = philo_current_time() - philo->data->t0;
	printf("%-6llu %-3d %s\n", time, id, status);
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
static void think(int id, t_philo *fork)
{
	int	taken;

	taken = 0;
	philo_print(id, fork, "is thinking");
	while (!taken)
		taken = try_take_fork(id, fork);
}

static void eat(int id, t_philo *first_fork, t_philo *second_fork)
{
	philo_print(id, first_fork, "is eating");
	usleep(first_fork->data->time_to_eat * 1000);
	pthread_mutex_lock(&(first_fork->mutex_fork));
	first_fork->fork = 0;
	pthread_mutex_unlock(&(first_fork->mutex_fork));
	pthread_mutex_lock(&(second_fork->mutex_fork));
	second_fork->fork = 0;
	pthread_mutex_unlock(&(second_fork->mutex_fork));
}
static void	try_take_forks(int id, t_philo *first_fork, t_philo *second_fork)
{
	if (!try_take_fork(id, first_fork))
		think(id, first_fork);
	if (!try_take_fork(id, second_fork))
		think(id, second_fork);
	eat(id, first_fork, second_fork);
}

static void	*philo_routine(void *params)
{
	t_philo	*philo;
	t_philo *next_philo;

	philo = (t_philo *) params;
	next_philo = philo->next;
	if (next_philo == 0)
		next_philo = philo->data->philos;
	if (philo->id % 2 == 0)
		try_take_forks(philo->id, philo, next_philo);
	else
		try_take_forks(philo->id, next_philo, philo);
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
