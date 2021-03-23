/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_one.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: darbib <darbib@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/24 11:39:05 by darbib            #+#    #+#             */
/*   Updated: 2021/03/23 19:28:41 by darbib           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include "philo_one.h"
#include <stdlib.h>
#include <unistd.h>

int		init_philo_one(t_param *param)
{
	int	i;

	param->prompt_mutex = NULL;
	param->forks = NULL;
	param->prompt_mutex = (t_mutex *)calloc(1, sizeof(t_mutex));
	param->forks = (t_fork *)calloc(param->number_of_philosophers,
					sizeof(t_fork));
	if (!param->prompt_mutex || !param->forks)
		return (1);
	pthread_mutex_init(param->prompt_mutex, NULL);
	i = 0;
	while (i < param->number_of_philosophers)
	{
		pthread_mutex_init(&(param->forks + i)->fork, NULL);
		(param->forks + i)->free_fork = 1;
		i++;
	}
	param->fed_philo_n = 0;
	param->death = 0;
	g_philo_actions[other_fork_taking] = take_other_fork;
	g_philo_actions[his_fork_taking] = take_his_fork;
	g_philo_actions[eating] = philo_eat;
	g_philo_actions[sleeping] = philo_sleep;
	g_philo_actions[thinking] = philo_think;
	return (0);
}

int	create_philo_table(t_philo **table, t_param *pm)
{
	int		id;
	
	*table = (t_philo *)calloc(pm->number_of_philosophers, sizeof(t_philo));
	if (!*table)
		return (1);
	id = 0;
	while (id < pm->number_of_philosophers)
	{
		(*table)[id].id = id;
		(*table)[id].state = thinking;
		(*table)[id].last_dinner_tv = (struct timeval){0, 0};
		(*table)[id].meals_n = 0;
		(*table)[id].sim_param = pm;
		(*table)[id].his_fork = pm->forks + id;
		if (id < pm->number_of_philosophers - 1)
			(*table)[id].neighbour_fork = pm->forks + id + 1;
		else
			(*table)[id].neighbour_fork = pm->forks;
		id++;
	}
	return (0);
}

void	destroy_simulation(t_philo **table, t_param *param)
{
	int		i;

	pthread_mutex_destroy(param->prompt_mutex);
	free(param->prompt_mutex);
	param->prompt_mutex = NULL;
	i = 0;
	while (i < param->number_of_philosophers)
	{
		pthread_mutex_destroy(&(param->forks[i]).fork);
		i++;
	}
	free(param->forks);
	param->forks = NULL;
	free(*table);
	*table = NULL;
}

int main(int ac, char **av)
{
	t_param	param;
	t_philo	*table;
	
	if (ac < 5 || ac > 6)
	{
		write(2, "Error arguments\n", 16);
		return (1);
	}
	if (parse_args(ac, av, &param))
	{
		write(2, "Error arguments\n", 16);
		return (1);
	}
	init_philo_one(&param);
	create_philo_table(&table, &param);
	simulate_philo_table(table, &param);
	usleep(param.time_to_eat * TIME_FACTOR);
	destroy_simulation(&table, &param);
	return (0);
}
