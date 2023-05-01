/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_init_threads.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aruzafa- <aruzafa-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/01 17:18:29 by aruzafa-          #+#    #+#             */
/*   Updated: 2023/05/01 22:35:39 by aruzafa-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static int	all_eaten(t_data *data)
{
	int	all_eaten;

	pthread_mutex_lock(&(data->mutex_num_philos_eaten));
	all_eaten = data->num_philos_eaten >= data->num_philos;
	pthread_mutex_unlock(&(data->mutex_num_philos_eaten));
	return (all_eaten);
}

static void	philo_print(int id, t_data *data, char *status)
{
	u_int64_t	time;

	time = philo_current_time() - data->t0;
	printf("%-6llu %-3d %s\n", time, id, status);
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
		if (all_eaten(philo->data))
		{
			pthread_mutex_unlock(&(philo->data->mutex_print));
			return (0);
		}
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
	pthread_mutex_lock(&(fork->data->mutex_print));
	if (all_eaten(fork->data))
	{
		pthread_mutex_unlock(&(fork->data->mutex_print));
		return ;
	}
	philo_print(id, fork->data, "is thinking");
	pthread_mutex_unlock(&(fork->data->mutex_print));
	while (!taken)
		taken = try_take_fork(id, fork);
}

static void eat(t_philo *me, t_philo *first_fork, t_philo *second_fork)
{
	pthread_mutex_lock(&(me->data->mutex_print));
	if (all_eaten(me->data))
	{
		pthread_mutex_unlock(&(me->data->mutex_print));
		return ;
	}
	philo_print(me->id, first_fork->data, "is eating");
	pthread_mutex_unlock(&(me->data->mutex_print));
	usleep(first_fork->data->time_to_eat * 1000);
	me->time_last_meal = philo_current_time();
	me->num_meals_eaten++;
	pthread_mutex_lock(&(me->data->mutex_print));
	if (me->num_meals_eaten == me->data->num_meals)
	{
		pthread_mutex_lock(&(me->data->mutex_num_philos_eaten));
		me->data->num_philos_eaten++;
		pthread_mutex_unlock(&(me->data->mutex_num_philos_eaten));
	}
	pthread_mutex_lock(&(first_fork->mutex_fork));
	first_fork->fork = 0;
	pthread_mutex_unlock(&(first_fork->mutex_fork));
	pthread_mutex_lock(&(second_fork->mutex_fork));
	second_fork->fork = 0;
	pthread_mutex_unlock(&(second_fork->mutex_fork));
	philo_print(me->id, me->data, "is sleeping");
	pthread_mutex_unlock(&(me->data->mutex_print));
	usleep(me->data->time_to_sleep * 1000);
}
static void	try_take_forks(t_philo *me, t_philo *first_fork, t_philo *second_fork)
{
	if (!try_take_fork(me->id, first_fork))
		think(me->id, first_fork);
	if (!try_take_fork(me->id, second_fork))
		think(me->id, second_fork);
	eat(me, first_fork, second_fork);
}

static void	*philo_routine(void *params)
{
	t_philo	*philo;
	t_philo *next_philo;

	philo = (t_philo *) params;
	next_philo = philo->next;
	if (next_philo == 0)
		next_philo = philo->data->philos;
	while (!all_eaten(philo->data))
	{
		if (philo->id % 2 == 0)
			try_take_forks(philo, philo, next_philo);
		else
			try_take_forks(philo, next_philo, philo);
	}
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
