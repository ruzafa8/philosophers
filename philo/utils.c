/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aruzafa- <aruzafa-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/01 17:21:40 by aruzafa-          #+#    #+#             */
/*   Updated: 2023/05/01 20:45:15 by aruzafa-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

uint64_t	philo_current_time(void)
{
	struct timeval	time;

	gettimeofday(&time, 0);
	return ((time.tv_sec * ((uint64_t)1000)) + (time.tv_usec / 1000));
}

void	*philo_calloc(size_t len)
{
	void	*ptr;

	ptr = malloc(len);
	if (!ptr)
		return ((void *) 0);
	memset(ptr, 0, len);
	return (ptr);
}
