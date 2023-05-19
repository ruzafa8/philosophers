/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_routine.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aruzafa- <aruzafa-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/01 17:18:29 by aruzafa-          #+#    #+#             */
/*   Updated: 2023/05/19 17:40:37 by aruzafa-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static int	try_take_fork(t_philo *me, t_philo *philo)
{
	int	taken;

	if (all_eaten(philo->data) || philo_any_dead(philo->data))
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

static int	philo_try_take_fork(t_philo *me, t_philo *fork)
{
	int	taken;

	taken = 0;
	while (!taken)
		taken = try_take_fork(me, fork);
	return (taken);
}

static int	philo_eat(t_philo *me, t_philo *first_fork, t_philo *second_fork)
{
	pthread_mutex_lock(&(me->data->mutex_print));
	if (all_eaten(me->data) || philo_any_dead(me->data))
		return (pthread_mutex_unlock(&(me->data->mutex_print)));
	philo_print(me->id, first_fork->data, "is eating");
	pthread_mutex_unlock(&(me->data->mutex_print));
	me->time_last_meal = philo_current_time();
	me->num_meals_eaten++;
	if (!philo_eating(me))
		return (0);
	pthread_mutex_lock(&(me->data->mutex_print));
	if (all_eaten(me->data) || philo_any_dead(me->data))
		return (pthread_mutex_unlock(&(me->data->mutex_print)));
	set_fork(first_fork, 0);
	set_fork(second_fork, 0);
	if (me->num_meals_eaten == me->data->num_meals)
		increase_num_philos_eaten(me->data);
	philo_print(me->id, me->data, "is sleeping");
	pthread_mutex_unlock(&(me->data->mutex_print));
	philo_sleeping(me);
	pthread_mutex_lock(&(me->data->mutex_print));
	if (all_eaten(me->data) || philo_any_dead(me->data))
		return (pthread_mutex_unlock(&(me->data->mutex_print)));
	philo_print(me->id, me->data, "is thinking");
	pthread_mutex_unlock(&(me->data->mutex_print));
	return (0);
}

static void	try_take_forks(t_philo *me, t_philo *fst_fork, t_philo *snd_fork)
{
	if (philo_try_take_fork(me, fst_fork) == -1)
		return ;
	if (philo_try_take_fork(me, snd_fork) == -1)
		return ;
	philo_eat(me, fst_fork, snd_fork);
}

void	*philo_routine(void *params)
{
	t_philo	*me;
	t_philo	*mate;
	t_philo	*first_fork;
	t_philo	*second_fork;
	int		taken;

	taken = 0;
	me = (t_philo *) params;
	mate = me->next;
	if (mate == 0)
		mate = me->data->philos;
	first_fork = me;
	second_fork = mate;
	if (me->id % 2 == 0)
	{
		usleep(50);
	}
	while (!all_eaten(me->data) && !philo_any_dead(me->data))
		try_take_forks(me, first_fork, second_fork);
	return (0);
}
