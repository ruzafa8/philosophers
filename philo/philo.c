/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aruzafa- <aruzafa-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/01 13:39:13 by aruzafa-          #+#    #+#             */
/*   Updated: 2023/05/13 18:13:54 by aruzafa-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	main(int argc, char **argv)
{
	t_data	*data;
	t_philo	*philo;

	data = philo_parse_params(argc, argv);
	if (!data)
		return (1);
	philo = data->philos;
	while (philo)
	{
		pthread_join(philo->thread, 0);
		philo = philo->next;
	}
	free_philos(data->philos);
	pthread_mutex_destroy(&(data->mutex_print));
	pthread_mutex_destroy(&(data->mutex_num_philos_eaten));
	pthread_mutex_destroy(&(data->mutex_anyone_dead));
	free(data);
	return (0);
}
