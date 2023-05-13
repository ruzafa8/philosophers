/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_routine.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aruzafa- <aruzafa-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/01 17:18:29 by aruzafa-          #+#    #+#             */
/*   Updated: 2023/05/13 17:15:18 by aruzafa-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static int	try_take_fork(t_philo *me, t_philo *philo)
{
	int	taken;

	if (philo_check_dead(me))
		return (-1);
	pthread_mutex_lock(&(philo->mutex_fork));
	taken = 0;
	if (!philo->fork)
	{
		philo->fork = 1;
		pthread_mutex_unlock(&(philo->mutex_fork));
		pthread_mutex_lock(&(philo->data->mutex_print));
		if (all_eaten(philo->data) || philo_any_dead(philo->data))
			return (pthread_mutex_unlock(&(philo->data->mutex_print)), -1);
		philo_print(me->id, philo->data, "has taken a fork");
		pthread_mutex_unlock(&(philo->data->mutex_print));
		taken = 1;
	}
	else
		pthread_mutex_unlock(&(philo->mutex_fork));
	return (taken);
}

static int	philo_think(t_philo *me, t_philo *fork)
{
	int	taken;

	taken = 0;
	if (philo_check_dead(fork))
		return (-1);
	pthread_mutex_lock(&(fork->data->mutex_print));
	if (all_eaten(fork->data) || philo_any_dead(fork->data))
	{
		pthread_mutex_unlock(&(fork->data->mutex_print));
		return (-1);
	}
	philo_print(me->id, fork->data, "is thinking");
	pthread_mutex_unlock(&(fork->data->mutex_print));
	while (!taken)
		taken = try_take_fork(me, fork);
	return (0);
}

static void	philo_eat(t_philo *me, t_philo *first_fork, t_philo *second_fork)
{
	if (philo_check_dead(me))
		return ;
	pthread_mutex_lock(&(me->data->mutex_print));
	if (all_eaten(me->data) || philo_any_dead(me->data))
	{
		pthread_mutex_unlock(&(me->data->mutex_print));
		return ;
	}
	philo_print(me->id, first_fork->data, "is eating");
	pthread_mutex_unlock(&(me->data->mutex_print));
	if (!philo_eating(me))
		return ;
	me->time_last_meal = philo_current_time();
	me->num_meals_eaten++;
	pthread_mutex_lock(&(me->data->mutex_print));
	if (me->num_meals_eaten == me->data->num_meals)
		increase_num_philos_eaten(me->data);
	if (all_eaten(me->data) || philo_any_dead(me->data))
	{
		pthread_mutex_unlock(&(me->data->mutex_print));
		return ;
	}
	set_fork(first_fork, 0);
	set_fork(second_fork, 0);
	philo_print(me->id, me->data, "is sleeping");
	pthread_mutex_unlock(&(me->data->mutex_print));
	usleep(me->data->time_to_sleep * 1000);
	if (philo_check_dead(me))
		return ;
}

static void	try_take_forks(t_philo *me, t_philo *fst_fork, t_philo *snd_fork)
{
	int	taken;

	taken = try_take_fork(me, fst_fork);
	if (taken == -1)
		return ;
	if (!taken)
		if (philo_think(me, fst_fork) == -1)
			return ;
	taken = try_take_fork(me, snd_fork);
	if (taken == -1)
		return ;
	if (!taken)
		if (philo_think(me, snd_fork) == -1)
			return ;
	philo_eat(me, fst_fork, snd_fork);
}

void	*philo_routine(void *params)
{
	t_philo	*philo;
	t_philo	*next_philo;

	philo = (t_philo *) params;
	next_philo = philo->next;
	if (next_philo == 0)
		next_philo = philo->data->philos;
	while (!all_eaten(philo->data) && !philo_any_dead(philo->data))
	{
		if (philo->id % 2 == 0)
			try_take_forks(philo, philo, next_philo);
		else
			try_take_forks(philo, next_philo, philo);
	}
	return (0);
}
