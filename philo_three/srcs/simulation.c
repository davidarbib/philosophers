/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   simulation.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: darbib <darbib@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/18 10:26:21 by darbib            #+#    #+#             */
/*   Updated: 2021/03/27 13:35:42 by darbib           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_three.h"
#include <unistd.h>
#include <stdlib.h>

void	*supervise(void *atypic_philo)
{
	t_philo	*philo;
	t_param	*param;
	
	philo = (t_philo *)atypic_philo;
	param = philo->sim_param;
	while (1)
	{
		if (check_for_death(philo, param))
			break ;
	}
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
		ft_msleep(10, param);
	pthread_create(&handler, NULL, supervise, philo);
	while (!check_death_bool(param))
	{
		g_philo_actions[philo->state](philo, param);
		philo->state++;
		if (philo->state == STATE_NB)
			philo->state = 0;
	}
	return (NULL);
}

void	simulate_philo_table(t_param *param)
{
	int i;
	int	status;
	t_philo	philo;

	gettimeofday(&param->begin_tv, NULL);
	i = 0;
	while (i < param->number_of_philosophers)
	{
		param->pids[i] = fork();
		if (param->pids[i] == 0)
		{
			free(param->pids);
			philo.id = i;
			philo.state = thinking;
			gettimeofday(&philo.last_dinner_tv, NULL);
			philo.meals_n = 0;
			philo.sim_param = param;
			live(&philo);
			exit(0);
		}
		i++;
	}
	//usleep(500);
	waitpid(-1, &status, WUNTRACED);
	i = 0;
	while (i < param->number_of_philosophers)
	{
		kill(param->pids[i], SIGKILL);
		i++;
	}
}
