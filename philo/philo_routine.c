/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_routine.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aruzafa- <aruzafa-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/01 17:18:29 by aruzafa-          #+#    #+#             */
/*   Updated: 2023/05/02 18:11:45 by aruzafa-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static int	try_take_fork(int id, t_philo *philo)
{
	int	taken;

	pthread_mutex_lock(&(philo->mutex_fork));
	taken = 0;
	if (!philo->fork)
	{
		philo->fork = 1;
		pthread_mutex_unlock(&(philo->mutex_fork));
		if (all_eaten(philo->data))
			return (1);
		pthread_mutex_lock(&(philo->data->mutex_print));
		printf("%-6llu %-3d chopstick %d taken.\n", philo_current_time() - philo->data->t0, id, philo->id);
		pthread_mutex_unlock(&(philo->data->mutex_print));
		taken = 1;
	}
	else
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
		increase_num_philos_eaten(me->data);
	set_fork(first_fork, 0);
	set_fork(second_fork, 0);
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

void	*philo_routine(void *params)
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
