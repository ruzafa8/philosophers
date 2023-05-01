/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aruzafa- <aruzafa-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/01 14:06:45 by aruzafa-          #+#    #+#             */
/*   Updated: 2023/05/01 22:52:40 by aruzafa-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <pthread.h>
# include <string.h>
# include <stdio.h>
# include <stdlib.h>
# include <limits.h>
# include <sys/time.h>
# include <unistd.h>

typedef struct s_philo	t_philo;
typedef struct s_data	t_data;

struct s_data
{
	uint64_t		t0;
	int				num_philos;
	int				num_meals;
	int				num_philos_eaten;
	pthread_mutex_t	mutex_num_philos_eaten;
	int				time_to_die;
	int				time_to_eat;
	int				time_to_sleep;
	pthread_mutex_t	mutex_print;
	int				anyone_dead;
	pthread_mutex_t	mutex_anyone_dead;
	t_philo			*philos;
};

struct s_philo
{
	int				id;
	pthread_mutex_t	mutex_fork;
	int				fork;
	pthread_t		thread;
	int				time_last_meal;
	int				num_meals_eaten;
	t_data			*data;
	t_philo			*next;
};

t_data		*philo_parse_params(int argc, char **argv);

/** philo routine **/
void	*philo_routine(void *params);

/** utils **/
void		*philo_calloc(size_t len);
uint64_t	philo_current_time(void);
void		set_fork(t_philo *fork, int value);
void 		increase_num_philos_eaten(t_data *data);
void		philo_print(int id, t_data *data, char *status);

/** more utils **/
t_philo		*philo_list_new(int id, t_data *data);
void		philo_list_add_back(t_philo **head, t_philo *new);
void		*free_philos(t_philo *head);
int			all_eaten(t_data *data);

#endif