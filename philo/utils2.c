/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aruzafa- <aruzafa-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/01 17:20:42 by aruzafa-          #+#    #+#             */
/*   Updated: 2023/05/13 16:56:06 by aruzafa-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	all_eaten(t_data *data)
{
	int	all_has_eaten;

	pthread_mutex_lock(&(data->mutex_num_philos_eaten));
	all_has_eaten = data->num_philos_eaten >= data->num_philos;
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
		if (philo_check_dead(me))
			return (0);
		usleep(10);
	}
	return (1);
}

void	*free_philos(t_philo *head)
{
	t_philo	*tmp;

	while (head)
	{
		tmp = head;
		head = head->next;
		pthread_mutex_destroy(&(tmp->mutex_fork));
		free(tmp);
	}
	return (0);
}

t_philo	*philo_list_new(int id, t_data *data)
{
	t_philo	*node;

	node = philo_calloc(sizeof(t_philo));
	if (!node)
		return (0);
	node->id = id;
	node->data = data;
	return (node);
}

void	philo_list_add_back(t_philo **head, t_philo *new)
{
	t_philo	*last;

	if (!*head)
	{
		*head = new;
		return ;
	}
	last = *head;
	while (last->next)
		last = last->next;
	last->next = new;
}
