/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   actions.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: darbib <darbib@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/02 14:35:21 by darbib            #+#    #+#             */
/*   Updated: 2021/03/24 14:27:05 by darbib           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_one.h"
#include <unistd.h>
#include <stdio.h>

void	philo_eat(t_philo *philo, t_param *param)
{
	if (!param->death)
	{
		printf("%ld %d is eating\n", get_relative_ms(param->begin_tv),
				philo->id);
	}
	gettimeofday(&philo->last_dinner_tv, NULL);
	ft_msleep(param->time_to_eat);
	philo->meals_n++;
	if (param->number_of_times_each_philosophers_must_eat > 0
		&& philo->meals_n == param->number_of_times_each_philosophers_must_eat)
		//protect mutex
		param->fed_philo_n++;
}

void	take_his_fork(t_philo *philo, t_param *param)
{
	while (!philo->his_fork->free_fork)
	{
		if (check_for_death(philo, param))
			return ;
	}	
	pthread_mutex_lock(&philo->his_fork->fork);
	philo->his_fork->free_fork = 0;
	if (!param->death)
	{
		printf("%ld %d has taken a fork\n", get_relative_ms(param->begin_tv),
				philo->id);
	}
}

void	take_other_fork(t_philo *philo, t_param *param)
{
	while (!philo->neighbour_fork->free_fork)
	{
		if (check_for_death(philo, param))
			return ;
	}	
	pthread_mutex_lock(&philo->neighbour_fork->fork);
	philo->neighbour_fork->free_fork = 0;
	if (!param->death)
	{
		printf("%ld %d has taken a fork\n", get_relative_ms(param->begin_tv),
				philo->id);
	}
}

void	philo_sleep(t_philo *philo, t_param *param)
{
	pthread_mutex_unlock(&philo->his_fork->fork);
	philo->his_fork->free_fork = 1;
	pthread_mutex_unlock(&philo->neighbour_fork->fork);
	philo->neighbour_fork->free_fork = 1;
	if (!param->death)
	{
		printf("%ld %d is sleeping\n", get_relative_ms(param->begin_tv),
				philo->id);
	}
	ft_msleep(param->time_to_sleep);
}

void	philo_think(t_philo *philo, t_param *param)
{
	if (!param->death)
	{
		printf("%ld %d is thinking\n", get_relative_ms(param->begin_tv),
				philo->id);
	}
}
