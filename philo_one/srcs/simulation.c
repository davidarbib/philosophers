/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   simulation.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: darbib <darbib@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/18 10:26:21 by darbib            #+#    #+#             */
/*   Updated: 2021/03/22 16:47:19 by darbib           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_one.h"
#include <unistd.h>

void	loop_until_death(t_philo *philo, t_param *param)
{
	while (!param->death)
	{
		g_philo_actions[philo->state](philo, param);
		if (get_relative_ms(philo->last_dinner_tv) > param->time_to_die)
		{
			philo->state = dead;
			//pthread_mutex_lock(param->prompt_mutex);
			if (param->death == 0)
			{
				ret = ft_ltobuffer(get_relative_ms(param->begin_tv), philo->buf);
				philo->buf[ret] = ' ';
				ret += ft_ltobuffer(philo->id, philo->buf + ret + 1) + 1;
				ft_memmove(philo->buf + ret, DIE_MSG, DIE_MSG_LEN);  
				write(1, philo->buf, ret + DIE_MSG_LEN);
			}
			param->death = 1;
			break;
		}
		if (param->fed_philo_n == param->number_of_philosophers)
		{
			param->death = 1;
			break;
		}
		philo->state++;
		philo->state = philo->state % STATE_NB;
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
	loop_until_death(philo, param);
	if (philo->state == right_fork_taking)
		pthread_mutex_unlock(&philo->fork);
	if (philo->state == left_fork_taking)
	{
		pthread_mutex_unlock(&philo->fork);
		pthread_mutex_unlock(&philo->next->fork);
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
	join_threads(philo);
}
