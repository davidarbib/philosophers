/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_three.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: darbib <darbib@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/24 11:39:05 by darbib            #+#    #+#             */
/*   Updated: 2021/03/28 17:44:59 by darbib           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include "philo_three.h"
#include <stdlib.h>
#include <unistd.h>

int		init_philo_one(t_param *param)
{
	param->death_sem = NULL;
	param->forks = NULL;
	param->fed_sem = NULL;
	param->prompt_sem = NULL;
	sem_unlink(DEATH_NAME);
	sem_unlink(FED_NAME);
	sem_unlink(FORKS_NAME);
	sem_unlink(PROMPT_NAME);
	param->forks = sem_open(FORKS_NAME, O_CREAT | O_EXCL, S_IRWXU,
							param->number_of_philosophers);
	param->fed_sem = sem_open(FED_NAME, O_CREAT | O_EXCL, S_IRWXU, 0);
	param->death_sem = sem_open(DEATH_NAME, O_CREAT | O_EXCL, S_IRWXU, 1);
	param->prompt_sem = sem_open(PROMPT_NAME, O_CREAT | O_EXCL, S_IRWXU, 1);
	if (param->death_sem == SEM_FAILED || param->fed_sem == SEM_FAILED
		|| param->forks == SEM_FAILED || param->prompt_sem == SEM_FAILED)
		return (1);
	param->forks_nb = param->number_of_philosophers;
	param->fed_philo_n = 0;
	param->death = 0;
	param->prompt_allow = 1;
	param->pids = (pid_t *)calloc(param->number_of_philosophers,
										sizeof(pid_t));
	if (!param->pids)
		return (1);
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

int		main(int ac, char **av)
{
	t_param	param;

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
		destroy_semaphores(&param);
		perror("philo_two");
		return (1);
	}
	init_ft_array();
	simulate_philo_table(&param);
	free(param.pids);
	destroy_semaphores(&param);
	return (0);
}
