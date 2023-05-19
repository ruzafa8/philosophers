/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_eat.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aruzafa- <aruzafa-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/13 17:39:41 by aruzafa-          #+#    #+#             */
/*   Updated: 2023/05/19 17:37:59 by aruzafa-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	all_eaten(t_data *data)
{
	int	all_has_eaten;

	pthread_mutex_lock(&(data->mutex_num_philos_eaten));
	all_has_eaten = data->num_philos_eaten == data->num_philos;
	pthread_mutex_unlock(&(data->mutex_num_philos_eaten));
	return (all_has_eaten);
}

int	philo_eating(t_philo *me)
{
	uint64_t	time_before_eat;

	time_before_eat = philo_current_time();
	while ((int)(philo_current_time() - time_before_eat)
		< me->data->time_to_eat)
	{
		usleep(50);
	}
	return (1);
}
