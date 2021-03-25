/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   actions.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: darbib <darbib@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/02 14:35:21 by darbib            #+#    #+#             */
/*   Updated: 2021/03/25 12:05:27 by darbib           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_three.h"
#include <unistd.h>
#include <stdio.h>

void	philo_eat(t_philo *philo, t_param *param)
{
	if (!check_death_bool(param))
	{
		printf("%ld %d is eating\n", get_relative_ms(param->begin_tv),
				philo->id);
	}
	gettimeofday(&philo->last_dinner_tv, NULL);
	ft_msleep(param->time_to_eat, param);
	philo->meals_n++;
	if (param->number_of_times_each_philosophers_must_eat > 0
		&& philo->meals_n == param->number_of_times_each_philosophers_must_eat)
	{
		sem_wait(param->fed_sem);
		param->fed_philo_n++;
		sem_post(param->fed_sem);
	}
}

void	take_his_fork(t_philo *philo, t_param *param)
{
	while (param->forks_nb == 0)
	{
		if (check_death_bool(param))
			return ;
	}
	sem_wait(param->forks);
	param->forks_nb--;
	if (!check_death_bool(param))
	{
		printf("%ld %d has taken a fork\n", get_relative_ms(param->begin_tv),
				philo->id);
	}
}

void	take_other_fork(t_philo *philo, t_param *param)
{
	while (param->forks_nb == 0)
	{
		if (check_death_bool(param))
			return ;
	}
	sem_wait(param->forks);
	param->forks_nb--;
	if (!check_death_bool(param))
	{
		printf("%ld %d has taken a fork\n", get_relative_ms(param->begin_tv),
				philo->id);
	}
}

void	philo_sleep(t_philo *philo, t_param *param)
{
	sem_post(param->forks);
	param->forks_nb++;
	sem_post(param->forks);
	param->forks_nb++;
	if (!check_death_bool(param))
	{
		printf("%ld %d is sleeping\n", get_relative_ms(param->begin_tv),
				philo->id);
	}
	ft_msleep(param->time_to_sleep, param);
}

void	philo_think(t_philo *philo, t_param *param)
{
	if (!check_death_bool(param))
	{
		printf("%ld %d is thinking\n", get_relative_ms(param->begin_tv),
				philo->id);
	}
}
