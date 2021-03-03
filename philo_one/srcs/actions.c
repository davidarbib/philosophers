/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   actions.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: darbib <darbib@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/02 14:35:21 by darbib            #+#    #+#             */
/*   Updated: 2021/03/03 15:28:06 by darbib           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_one.h"

void	philo_eat(t_philo *philo)
{
	(void)philo;
}

void	take_his_fork(t_philo *philo)
{
	pthread_mutex_lock(&philo->fork);	
	print_state(philo);	
}

void	take_left_fork(t_philo *philo)
{
	pthread_mutex_lock(&philo->next->fork);	
	print_state(philo);	
}

void	philo_sleep(t_philo *philo)
{
	pthread_mutex_unlock(&philo->fork);
	pthread_mutex_unlock(&philo->next->fork);
}

void	philo_think(t_philo *philo)
{
	(void)philo;
}
