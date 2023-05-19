/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aruzafa- <aruzafa-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/01 17:20:42 by aruzafa-          #+#    #+#             */
/*   Updated: 2023/05/19 16:55:44 by aruzafa-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	philo_sleeping(t_philo *me)
{
	uint64_t	time_before_sleep;

	time_before_sleep = philo_current_time();
	while ((int)(philo_current_time() - time_before_sleep)
		< me->data->time_to_sleep)
	{
		usleep(50);
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
	node->time_last_meal = philo_current_time();
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
