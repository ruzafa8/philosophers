/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_init_threads.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aruzafa- <aruzafa-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/01 17:18:29 by aruzafa-          #+#    #+#             */
/*   Updated: 2023/05/01 18:59:49 by aruzafa-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static void	*philo_routine(void *params)
{
	t_philo	*philo;

	philo = (t_philo *) params;
	if (philo->id % 2 == 0)
		usleep(1000);
	pthread_mutex_lock(&(philo->data->mutex_print));
	printf("philo %d\n", philo->id);
	pthread_mutex_unlock(&(philo->data->mutex_print));
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
