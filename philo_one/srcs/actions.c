/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   actions.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: darbib <darbib@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/02 14:35:21 by darbib            #+#    #+#             */
/*   Updated: 2021/03/04 00:05:20 by darbib           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_one.h"
#include <unistd.h>

void	philo_eat(t_philo *philo, t_param *param)
{
	(void)philo;
	usleep(param->time_to_eat * 1000);
}

void	take_his_fork(t_philo *philo, t_param *param)
{
	(void)param;
	pthread_mutex_lock(&philo->fork);	
}

void	take_left_fork(t_philo *philo, t_param *param)
{
	(void)param;
	pthread_mutex_lock(&philo->next->fork);	
}

void	philo_sleep(t_philo *philo, t_param *param)
{
	pthread_mutex_unlock(&philo->fork);
	pthread_mutex_unlock(&philo->next->fork);
	usleep(param->time_to_sleep * 1000);
}

void	philo_think(t_philo *philo, t_param *param)
{
	(void)philo;
	(void)param;
}
