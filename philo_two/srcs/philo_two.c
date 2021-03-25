/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_two.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: darbib <darbib@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/24 11:39:05 by darbib            #+#    #+#             */
/*   Updated: 2021/03/25 00:57:33 by darbib           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include "philo_two.h"
#include <stdlib.h>
#include <unistd.h>

int		init_philo_one(t_param *param)
{
	int	i;

	param->death_sem = NULL;
	param->forks = NULL;
	param->fed_sem = NULL; 
	param->forks = sem_open(FORKS_NAME, O_CREAT);
		perror("philo_two");
	i = 0;
	param->fed_sem = sem_open(FED_NAME, O_CREAT);
		perror("philo_two");
	param->death_sem = sem_open(DEATH_NAME, O_CREAT);
		perror("philo_two");
	if (param->death_sem == SEM_FAILED || param->fed_sem == SEM_FAILED 
		|| param->forks == SEM_FAILED)
		return (1);
	while (i < param->number_of_philosophers)
	{
		sem_post(param->forks);
		i++;
	}
	sem_post(param->fed_sem);
	sem_post(param->death_sem);
	param->forks_nb = param->number_of_philosophers;
	param->fed_philo_n = 0;
	param->death = 0;
	return (0);
}

void	init_ft_array(void)
{
	g_philo_actions[other_fork_taking] = take_other_fork;
	g_philo_actions[his_fork_taking] = take_his_fork;
	g_philo_actions[eating] = philo_eat;
	g_philo_actions[sleeping] = philo_sleep;
	g_philo_actions[thinking] = philo_think;
}

int		create_philo_table(t_philo **table, t_param *pm)
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
		id++;
	}
	return (0);
}

void	destroy_simulation(t_philo **table, t_param *param)
{
	sem_unlink(DEATH_NAME);
	sem_unlink(FED_NAME);
	sem_unlink(FORKS_NAME);
	sem_close(param->death_sem);
	sem_close(param->fed_sem);
	sem_close(param->forks);
	free(*table);
	*table = NULL;
}

int		main(int ac, char **av)
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
	if (init_philo_one(&param))
	{
		perror("philo_two");
		return (1);
	}
	init_ft_array();
	create_philo_table(&table, &param);
	simulate_philo_table(table, &param);
	usleep(param.time_to_eat * TIME_FACTOR);
	destroy_simulation(&table, &param);
	return (0);
}
