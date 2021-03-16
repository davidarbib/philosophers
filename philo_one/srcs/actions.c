/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   actions.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: darbib <darbib@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/02 14:35:21 by darbib            #+#    #+#             */
/*   Updated: 2021/03/16 16:22:57 by darbib           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_one.h"
#include <unistd.h>
#include <stdio.h>

void	philo_eat(t_philo *philo, t_param *param)
{
	pthread_mutex_lock(&param->prompt_mutex);
	printf("%ld %d is eating\n", get_relative_ms(param->begin_tv), philo->id);
	pthread_mutex_unlock(&param->prompt_mutex);
	gettimeofday(&philo->last_dinner_tv, NULL);
	ft_usleep(param->time_to_eat);
	philo->meals_n++;
	if (param->number_of_times_each_philosophers_must_eat > 0
		&& philo->meals_n == param->number_of_times_each_philosophers_must_eat)
		param->fed_philo_n++;
}

void	take_his_fork(t_philo *philo, t_param *param)
{
	(void)param;
	pthread_mutex_lock(&philo->fork);
	pthread_mutex_lock(&param->prompt_mutex);
	printf("%ld %d has taken a fork %p\n", get_relative_ms(param->begin_tv),
			philo->id, &philo->fork);
	pthread_mutex_unlock(&param->prompt_mutex);
}

void	take_left_fork(t_philo *philo, t_param *param)
{
	(void)param;
	pthread_mutex_lock(&philo->next->fork);
	pthread_mutex_lock(&param->prompt_mutex);
	printf("%ld %d has taken a fork %p\n", get_relative_ms(param->begin_tv),
			philo->id, &philo->next->fork);
	pthread_mutex_unlock(&param->prompt_mutex);
}

void	philo_sleep(t_philo *philo, t_param *param)
{
	(void)philo;
	pthread_mutex_unlock(&philo->fork);
	pthread_mutex_unlock(&philo->next->fork);
	pthread_mutex_lock(&param->prompt_mutex);
	printf("%ld %d is sleeping\n", get_relative_ms(param->begin_tv), philo->id);
	pthread_mutex_unlock(&param->prompt_mutex);
	ft_usleep(param->time_to_sleep);
}

void	philo_think(t_philo *philo, t_param *param)
{
	pthread_mutex_lock(&param->prompt_mutex);
	printf("%ld %d is thinking\n", get_relative_ms(param->begin_tv), philo->id);
	pthread_mutex_unlock(&param->prompt_mutex);
	(void)param;
}
