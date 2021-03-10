/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   actions.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: darbib <darbib@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/02 14:35:21 by darbib            #+#    #+#             */
/*   Updated: 2021/03/10 19:21:33 by darbib           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_one.h"
#include <unistd.h>
#include <stdio.h>

void	philo_eat(t_philo *philo, t_param *param)
{
	(void)philo;
	ft_usleep(param->time_to_eat);
	gettimeofday(&philo->last_dinner_tv, NULL);
}

void	take_his_fork(t_philo *philo, t_param *param)
{
	(void)param;
	pthread_mutex_lock(&philo->fork);
//	printf("philo %d lock %p\n", philo->id, &philo->fork);
}

void	take_left_fork(t_philo *philo, t_param *param)
{
	(void)param;
	pthread_mutex_lock(&philo->next->fork);
//	printf("philo %d lock %p\n", philo->id, &philo->next->fork);
}

void	philo_sleep(t_philo *philo, t_param *param)
{
	pthread_mutex_unlock(&philo->fork);
//	printf("philo %d unlock %p\n", philo->id, &philo->fork);
	pthread_mutex_unlock(&philo->next->fork);
//	printf("philo %d unlock %p\n", philo->id, &philo->next->fork);
	ft_usleep(param->time_to_sleep);
}

void	philo_think(t_philo *philo, t_param *param)
{
	(void)philo;
	(void)param;
}
