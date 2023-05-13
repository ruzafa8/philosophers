/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aruzafa- <aruzafa-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/01 13:39:13 by aruzafa-          #+#    #+#             */
/*   Updated: 2023/05/13 16:16:24 by aruzafa-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	main(int argc, char **argv)
{
	t_data	*data;

	data = philo_parse_params(argc, argv);
	if (!data)
		return (1);
	t_philo *philo = data->philos;
	while (philo)
	{
		pthread_join(philo->thread, 0);
		philo = philo->next;
	}
	if (data->num_philos_eaten == data->num_philos)
		printf("All philosophers have eaten at least %d times.\n", data->num_meals);
	free_philos(data->philos);
	pthread_mutex_destroy(&(data->mutex_print));
	pthread_mutex_destroy(&(data->mutex_num_philos_eaten));
	pthread_mutex_destroy(&(data->mutex_anyone_dead));
	free(data);
	return (0);
}
