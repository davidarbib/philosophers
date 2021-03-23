/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   simulation.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: darbib <darbib@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/18 10:26:21 by darbib            #+#    #+#             */
/*   Updated: 2021/03/23 12:21:49 by darbib           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_one.h"
#include <unistd.h>
#include <string.h>

int		check_for_death(t_philo *philo, t_param *param)
{
	int	ret;

	if (param->death)
		return (1);
	if (get_relative_ms(philo->last_dinner_tv) > param->time_to_die)
	{
		philo->state = dead;
		if (param->death == 0)
		{
			memset(philo->buf, 0, MESSAGE_LEN);
			ret = ft_ltobuffer(get_relative_ms(param->begin_tv), philo->buf);
			philo->buf[ret] = ' ';
			ret += ft_ltobuffer(philo->id, philo->buf + ret + 1) + 1;
			ft_memmove(philo->buf + ret, DIE_MSG, DIE_MSG_LEN);  
			write(1, philo->buf, ret + DIE_MSG_LEN);
		}
		param->death = 1;
		return (1);
	}
	return (0);
}

void	loop_until_death(t_philo *philo, t_param *param)
{
	while (1)
	{
		if (check_for_death(philo, param))
			break;
		g_philo_actions[philo->state](philo, param);
		if (param->fed_philo_n == param->number_of_philosophers)
			break;
		philo->state++;
		philo->state = philo->state % STATE_NB;
	}
	param->death = 1;
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
	loop_until_death(philo, param);
	/*
	if (philo->state == right_fork_taking)
		pthread_mutex_unlock(&philo->fork);
	if (philo->state == left_fork_taking)
	{
		pthread_mutex_unlock(&philo->fork);
		pthread_mutex_unlock(&philo->next->fork);
	}
	*/
	return (NULL);
}

void	launch_simulation(t_philo *philo, t_param *param)
{
	gettimeofday(&param->begin_tv, NULL);
	param->death = 0;
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
	while (1)
	{
		check_for_death(philo, param);
		philo = philo->next;
	}
	join_threads(philo);
}
