/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   actions.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: darbib <darbib@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/02 14:35:21 by darbib            #+#    #+#             */
/*   Updated: 2021/03/28 17:38:35 by darbib           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_three.h"
#include <unistd.h>
#include <stdio.h>

void	philo_eat(t_philo *philo, t_param *param)
{
	while (!param->prompt_allow)
	{
		if (check_death_bool(param))
			return ;
	}
	sem_wait(param->prompt_sem);
	param->prompt_allow = 0;
	print_actions(philo, param, EAT_MSG, EAT_MSG_LEN);
	sem_post(param->prompt_sem);
	param->prompt_allow = 1;
	gettimeofday(&philo->last_dinner_tv, NULL);
	ft_msleep(param->time_to_eat, param);
	philo->meals_n++;
	if (param->number_of_times_each_philosophers_must_eat > 0
		&& philo->meals_n == param->number_of_times_each_philosophers_must_eat
		&& philo->fed == 0)
	{
		philo->fed = 1;
		sem_post(param->fed_sem);
	}
}

void	take_his_fork(t_philo *philo, t_param *param)
{
	sem_wait(param->forks);
	while (!param->prompt_allow)
	{
		if (check_death_bool(param))
			return ;
	}
	sem_wait(param->prompt_sem);
	param->prompt_allow = 0;
	print_actions(philo, param, FORK_MSG, FORK_MSG_LEN);
	sem_post(param->prompt_sem);
	param->prompt_allow = 1;
}

void	take_other_fork(t_philo *philo, t_param *param)
{
	sem_wait(param->forks);
	while (!param->prompt_allow)
	{
		if (check_death_bool(param))
			return ;
	}
	sem_wait(param->prompt_sem);
	param->prompt_allow = 0;
	print_actions(philo, param, FORK_MSG, FORK_MSG_LEN);
	sem_post(param->prompt_sem);
	param->prompt_allow = 1;
}

void	philo_sleep(t_philo *philo, t_param *param)
{
	sem_post(param->forks);
	param->forks_nb++;
	sem_post(param->forks);
	param->forks_nb++;
	while (!param->prompt_allow)
	{
		if (check_death_bool(param))
			return ;
	}
	sem_wait(param->prompt_sem);
	param->prompt_allow = 0;
	print_actions(philo, param, SLEEP_MSG, SLEEP_MSG_LEN);
	sem_post(param->prompt_sem);
	param->prompt_allow = 1;
	ft_msleep(param->time_to_sleep, param);
}

void	philo_think(t_philo *philo, t_param *param)
{
	while (!param->prompt_allow)
	{
		if (check_death_bool(param))
			return ;
	}
	sem_wait(param->prompt_sem);
	param->prompt_allow = 0;
	print_actions(philo, param, THINK_MSG, THINK_MSG_LEN);
	sem_post(param->prompt_sem);
	param->prompt_allow = 1;
}
