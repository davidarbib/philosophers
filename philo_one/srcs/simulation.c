/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   simulation.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: darbib <darbib@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/18 10:26:21 by darbib            #+#    #+#             */
/*   Updated: 2021/03/24 17:01:47 by darbib           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_one.h"
#include <unistd.h>

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

	pthread_mutex_lock(param->fed_mutex);
	if (param->fed_philo_n == param->number_of_philosophers)
	{
		pthread_mutex_unlock(param->fed_mutex);
		set_death_bool(param);
		return (1);
	}
	pthread_mutex_unlock(param->fed_mutex);
	return (0);
}

int		check_death_bool(t_param *param)
{
	int death;

	pthread_mutex_lock(param->death_mutex);
	death = param->death;
	pthread_mutex_unlock(param->death_mutex);
	return (death);
}

void	set_death_bool(t_param *param)
{
	pthread_mutex_lock(param->death_mutex);
	param->death = 1;
	pthread_mutex_unlock(param->death_mutex);
}

void	*live(void *atypic_philo)
{
	t_philo *philo;
	t_param *param;

	philo = (t_philo *)atypic_philo;
	param = philo->sim_param;
	printf("%p\n", param);
	if (philo->id % 2)
		ft_msleep(10, param);
	while (!check_death_bool(param))
	{
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
	printf("%p\n", param);
	while (i < param->number_of_philosophers)
	{
		gettimeofday(&(philos + i)->last_dinner_tv, NULL);
		pthread_create(&(philos[i].soul), NULL, live, philos + i);
		i++;
	}
	usleep(500);
	i = 0;
	while (1)
	{
		if (check_for_death(philos + i, param))
			break;
		i++;
		i %= param->number_of_philosophers;
	}
	i = 0;
	while (i < param->number_of_philosophers)
	{
		pthread_join(philos[i].soul, NULL);
		i++;
	}
}
