/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_death.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aruzafa- <aruzafa-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/02 18:21:50 by aruzafa-          #+#    #+#             */
/*   Updated: 2023/05/19 17:32:25 by aruzafa-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	philo_any_dead(t_data *data)
{
	int	any_dead;

	pthread_mutex_lock(&(data->mutex_anyone_dead));
	any_dead = data->anyone_dead;
	pthread_mutex_unlock(&(data->mutex_anyone_dead));
	return (any_dead);
}

int	philo_check_dead(t_philo *me)
{
	int			i_am_dead;
	uint64_t	current_time;

	i_am_dead = 0;
	current_time = philo_current_time();
	if (current_time - me->time_last_meal > (u_int64_t)me->data->time_to_die)
	{
		pthread_mutex_lock(&(me->data->mutex_print));
		if (all_eaten(me->data) || philo_any_dead(me->data))
			return (pthread_mutex_unlock(&(me->data->mutex_print)), 1);
		pthread_mutex_lock(&(me->data->mutex_anyone_dead));
		me->data->anyone_dead = 1;
		pthread_mutex_unlock(&(me->data->mutex_anyone_dead));
		philo_print(me->id, me->data, "died");
		pthread_mutex_unlock(&(me->data->mutex_print));
		i_am_dead = 1;
	}
	return (i_am_dead);
}
