/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   simulation.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: darbib <darbib@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/18 10:26:21 by darbib            #+#    #+#             */
/*   Updated: 2021/03/24 14:25:07 by darbib           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_one.h"
#include <unistd.h>

int		check_for_death(t_philo *philo, t_param *param)
{
	if (param->death)
		return (1);
	if (get_relative_ms(philo->last_dinner_tv) > param->time_to_die)
	{
		philo->state = dead;
		param->death = 1;
		printf("%ld %d died\n", get_relative_ms(param->begin_tv),
				philo->id);
		return (1);
	}
	if (param->fed_philo_n == param->number_of_philosophers)
	{
		param->death = 1;
		return (1);
	}
	return (0);
}

void	*live(void *atypic_philo)
{
	t_philo *philo;
	t_param *param;

	philo = (t_philo *)atypic_philo;
	param = philo->sim_param;
	if (philo->id % 2)
		ft_msleep(1);
	gettimeofday(&philo->last_dinner_tv, NULL);
	while (!param->death)
	{
		if (check_for_death(philo, param))
			break;
		g_philo_actions[philo->state](philo, param);
		philo->state++;
		if (philo->state == STATE_NB)
			philo->state = 0;
	}
	return (NULL);
}

void	simulate_philo_table(t_philo *philos, t_param *param)
{
	int i;

	gettimeofday(&param->begin_tv, NULL);
	i = 0;
	while (i < param->number_of_philosophers)
	{
		pthread_create(&(philos[i].soul), NULL, live, philos + i);
		i++;
	}
	i = 0;
	while (i < param->number_of_philosophers)
	{
		pthread_join(philos[i].soul, NULL);
		i++;
	}
}
