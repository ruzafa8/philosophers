/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aruzafa- <aruzafa-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/01 13:39:13 by aruzafa-          #+#    #+#             */
/*   Updated: 2023/05/19 15:51:25 by aruzafa-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	check_philo_status(t_data *data)
{
	t_philo	*philo;

	philo = data->philos;
	while (!all_eaten(data) && !philo_check_dead(philo))
	{
		philo = philo->next;
		if (!philo)
			philo = data->philos;
	}
}

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
