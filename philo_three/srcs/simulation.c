/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   simulation.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: darbib <darbib@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/18 10:26:21 by darbib            #+#    #+#             */
/*   Updated: 2021/03/28 17:39:57 by darbib           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_three.h"
#include <unistd.h>
#include <stdlib.h>

void	*supervise(void *atypic_philo)
{
	t_philo	*philo;
	t_param	*param;
	int		i;

	philo = (t_philo *)atypic_philo;
	param = philo->sim_param;
	while (1)
	{
		if (check_for_death(philo, param))
			break ;
	}
	i = 0;
	while (i < param->number_of_philosophers)
	{
		sem_post(param->fed_sem);
		sem_post(param->forks);
		i++;
	}
	return (NULL);
	exit(0);
}

void	*live(void *atypic_philo)
{
	t_philo		*philo;
	t_param		*param;
	pthread_t	handler;

	philo = (t_philo *)atypic_philo;
	param = philo->sim_param;
	if (philo->id % 2)
		ft_msleep(SIM_SHIFT_MS, param);
	pthread_create(&handler, NULL, supervise, philo);
	while (!check_death_bool(param))
	{
		g_philo_actions[philo->state](philo, param);
		philo->state++;
		if (philo->state == STATE_NB)
			philo->state = 0;
	}
	pthread_join(handler, NULL);
	destroy_semaphores(param);
	exit(0);
	return (NULL);
}

void	forking(t_param *param, int i)
{
	t_philo	philo;

	param->pids[i] = fork();
	if (param->pids[i] == 0)
	{
		free(param->pids);
		philo.id = i;
		philo.state = thinking;
		philo.fed = 0;
		gettimeofday(&philo.last_dinner_tv, NULL);
		philo.meals_n = 0;
		philo.sim_param = param;
		live(&philo);
		exit(0);
	}
}

void	check_philo_feeding(t_param *param)
{
	int i;

	i = 0;
	while (i < param->number_of_philosophers)
	{
		sem_wait(param->fed_sem);
		i++;
	}
}

void	simulate_philo_table(t_param *param)
{
	int i;
	int	status;

	gettimeofday(&param->begin_tv, NULL);
	i = 0;
	while (i < param->number_of_philosophers)
	{
		forking(param, i);
		i++;
	}
	if (param->number_of_times_each_philosophers_must_eat > 0)
		check_philo_feeding(param);
	else
		waitpid(-1, &status, WUNTRACED);
	i = 0;
	while (i < param->number_of_philosophers)
	{
		kill(param->pids[i], SIGKILL);
		i++;
	}
}
