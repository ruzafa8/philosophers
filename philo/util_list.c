/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   util_list.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aruzafa- <aruzafa-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/01 17:20:42 by aruzafa-          #+#    #+#             */
/*   Updated: 2023/05/01 19:13:07 by aruzafa-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

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
