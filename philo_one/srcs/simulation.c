/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   simulation.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: darbib <darbib@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/18 10:26:21 by darbib            #+#    #+#             */
/*   Updated: 2021/03/18 14:25:51 by darbib           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_one.h"
#include <unistd.h>

void	wait_for_death(t_philo *philo, t_param *param)
{
	param->fed_philo_n = 0;
	usleep(param->time_to_eat * TIME_FACTOR);
	while (1)
	{
		if (get_relative_ms(philo->last_dinner_tv) > param->time_to_die)
		{
			philo->state = dead;
			param->death = 1;
			printf("%ld %d died\n", get_relative_ms(param->begin_tv),
					philo->id);
			break;
		}
		if (param->fed_philo_n == param->number_of_philosophers)
		{
			param->death = 1;
			break;
		}
		philo = philo->next;
	}
}

void	*live(void *atypic_philo)
{
	t_philo *philo;
	t_param *param;

	philo = (t_philo *)atypic_philo;
	param = philo->sim_param;
	philo->last_dinner_tv = param->begin_tv;
	if (philo->id % 2)
		ft_usleep(10);
	while (!param->death)
	{
		g_philo_actions[philo->state](philo, param);
		philo->state++;
		if (philo->state == STATE_NB)
			philo->state = 0;
	}
	return (NULL);
}

void	launch_simulation(t_philo *philo, t_param *param)
{
	gettimeofday(&param->begin_tv, NULL);
	while (1)
	{
		philo->sim_param = param;
		pthread_create(&philo->soul, NULL, live, philo);
		if (philo->id == 0)
			break;
		philo = philo->next;
	}
}

void	join_threads(t_philo *philo)
{
	while (1)
	{
		pthread_join(philo->soul, NULL);
		if (philo->id == 0)
			break;
		philo = philo->next;
	}
}

void	simulate_philo_table(t_philo *table, t_param *param)
{
	t_philo *philo;

	philo = table;
	launch_simulation(philo, param);
	philo = table;
	wait_for_death(philo, param);
	philo = table;
	join_threads(philo);
	printf("abort simulation\n");
}
