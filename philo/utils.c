/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aruzafa- <aruzafa-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/01 17:21:40 by aruzafa-          #+#    #+#             */
/*   Updated: 2023/05/01 17:21:52 by aruzafa-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	*philo_calloc(size_t len)
{
	void	*ptr;

	ptr = malloc(len);
	if (!ptr)
		return ((void *) 0);
	memset(ptr, 0, len);
	return (ptr);
}
