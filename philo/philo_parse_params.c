/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_parse_params.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aruzafa- <aruzafa-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/01 13:39:56 by aruzafa-          #+#    #+#             */
/*   Updated: 2023/05/01 20:50:58 by aruzafa-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static int	philo_atoi(char *str)
{
	long		nbr;

	nbr = 0;
	if (*str == '-')
		return (printf("Error: arguments must be non-negative numbers.\n"), -1);
	while (*str)
	{
		if (*str < '0' || *str > '9')
			return (printf("Error: arguments must be numeric.\n"), -1);
		nbr = nbr * 10 + (*str - '0');
		str++;
	}
	if (nbr < 0 || nbr > 2147483647)
		return (printf("Error: integer overflow.\n"), -1);
	return ((int) nbr);
}

static t_data	*create_philos(t_data *data)
{
	int	i;
	t_philo	*philo;

	if (!data)
		return (0);
	i = 0;
	while (i < data->num_philos)
	{
		philo_list_add_back(&data->philos, philo_list_new(i, data));
		i++;
	}
	philo = data->philos;
	while (philo)
	{
		pthread_mutex_init(&philo->mutex_fork, 0);
		philo = philo->next;
	}
	data->t0 = philo_current_time();
	pthread_mutex_init(&(data->mutex_print), 0);
	philo_init_threads(data);
	return (data);
}

static t_data	*init_data(int argc, char **argv)
{
	t_data	*data;

	data = (t_data *) philo_calloc(sizeof(t_data));
	if (!data)
		return (printf("Error: malloc failed.\n"), (t_data *) 0);
	data->num_philos = philo_atoi(argv[1]);
	if (data->num_philos == -1)
		return (free(data), (t_data *) 0);
	data->time_to_die = philo_atoi(argv[2]);
	if (data->time_to_die == -1)
		return (free(data), (t_data *) 0);
	data->time_to_eat = philo_atoi(argv[3]);
	if (data->time_to_eat == -1)
		return (free(data), (t_data *) 0);
	data->time_to_sleep = philo_atoi(argv[4]);
	if (data->time_to_sleep == -1)
		return (free(data), (t_data *) 0);
	data->num_meals = -1;
	if (argc == 6)
	{
		data->num_meals = philo_atoi(argv[5]);
		if (data->num_meals == -1)
			return (free(data), (t_data *) 0);
	}
	return (create_philos(data));
}

t_data	*philo_parse_params(int argc, char **argv)
{
	t_data	*data;

	if (argc < 5 || argc > 6)
		return (printf("Error: wrong number of arguments.\n"), (t_data *) 0);
	data = init_data(argc, argv);
	if (!data)
		return (0);
	return (data);
}
