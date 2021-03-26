/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   simulation.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: darbib <darbib@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/18 10:26:21 by darbib            #+#    #+#             */
/*   Updated: 2021/03/26 15:22:57 by darbib           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_three.h"
#include <unistd.h>
#include <stdlib.h>

int		check_for_death(t_philo *philo, t_param *param)
{
	if (check_death_bool(param))
		return (1);
	if (get_relative_ms(philo->last_dinner_tv) > param->time_to_die)
	{
		philo->state = dead;
		set_death_bool(param);
		printf("%ld %d died\n", get_relative_ms(param->begin_tv),
				philo->id);
		return (1);
	}
	/*
	sem_wait(param->fed_sem);
	if (param->fed_philo_n == param->number_of_philosophers)
	{
		sem_post(param->fed_sem);
		set_death_bool(param);
		return (1);
	}
	sem_post(param->fed_sem);
	*/
	return (0);
}

int		check_death_bool(t_param *param)
{
	int death;

	sem_wait(param->death_sem);
	death = param->death;
	sem_post(param->death_sem);
	return (death);
}

void	set_death_bool(t_param *param)
{
	sem_wait(param->death_sem);
	param->death = 1;
	sem_post(param->death_sem);
}

void	*live(void *atypic_philo)
{
	t_philo *philo;
	t_param *param;

	philo = (t_philo *)atypic_philo;
	param = philo->sim_param;
	if (philo->id % 2)
		ft_msleep(10, param);
	while (!check_death_bool(param))
	{
		if (check_for_death(philo, param))
			break ;
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

	printf("forks nb : %d\n", param->forks_nb);
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
