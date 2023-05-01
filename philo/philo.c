/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aruzafa- <aruzafa-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/01 13:39:13 by aruzafa-          #+#    #+#             */
/*   Updated: 2023/05/01 18:33:42 by aruzafa-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	main(int argc, char **argv)
{
	t_data	*data;

	data = philo_parse_params(argc, argv);
	if (!data)
		return (1);
	printf("num_philos: %d\n", data->num_philos);
	printf("time_to_die: %d\n", data->time_to_die);
	printf("time_to_eat: %d\n", data->time_to_eat);
	printf("time_to_sleep: %d\n", data->time_to_sleep);
	printf("num_meals: %d\n", data->num_meals);
	t_philo *philo = data->philos;
	while (philo)
	{
		pthread_join(philo->thread, 0);
		philo = philo->next;
	}
	free_philos(data->philos);
	free(data);
	return (0);
}
