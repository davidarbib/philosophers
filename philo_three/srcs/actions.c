/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   actions.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: darbib <darbib@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/02 14:35:21 by darbib            #+#    #+#             */
/*   Updated: 2021/03/27 16:28:06 by darbib           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_three.h"
#include <unistd.h>
#include <stdio.h>

void	philo_eat(t_philo *philo, t_param *param)
{
	int ret;

	if (!check_death_bool(param))
	{
		memset(philo->buf, 0, MESSAGE_LEN);
		ret = ft_ltobuffer(get_relative_ms(param->begin_tv), philo->buf);
		philo->buf[ret] = ' ';
		ret += ft_ltobuffer(philo->id, philo->buf + ret + 1) + 1;
		ft_memmove(philo->buf + ret, EAT_MSG, EAT_MSG_LEN);  
		write(1, philo->buf, ret + EAT_MSG_LEN);
	}
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
	int ret;

	while (param->forks_nb == 0)
	{
		if (check_for_death(philo, param))
			break ;
	}
	sem_wait(param->forks);
	param->forks_nb--;
	if (!check_death_bool(param))
	{
		memset(philo->buf, 0, MESSAGE_LEN);
		ret = ft_ltobuffer(get_relative_ms(param->begin_tv), philo->buf);
		philo->buf[ret] = ' ';
		ret += ft_ltobuffer(philo->id, philo->buf + ret + 1) + 1;
		ft_memmove(philo->buf + ret, FORK_MSG, FORK_MSG_LEN);  
		write(1, philo->buf, ret + FORK_MSG_LEN);
	}
}

void	take_other_fork(t_philo *philo, t_param *param)
{
	int ret;

	while (param->forks_nb == 0)
	{
		if (check_for_death(philo, param))
			break ;
	}
	sem_wait(param->forks);
	param->forks_nb--;
	if (!check_death_bool(param))
	{
		memset(philo->buf, 0, MESSAGE_LEN);
		ret = ft_ltobuffer(get_relative_ms(param->begin_tv), philo->buf);
		philo->buf[ret] = ' ';
		ret += ft_ltobuffer(philo->id, philo->buf + ret + 1) + 1;
		ft_memmove(philo->buf + ret, FORK_MSG, FORK_MSG_LEN);  
		write(1, philo->buf, ret + 18);
	}
}

void	philo_sleep(t_philo *philo, t_param *param)
{
	int ret;

	sem_post(param->forks);
	param->forks_nb++;
	sem_post(param->forks);
	param->forks_nb++;
	if (!check_death_bool(param))
	{
		memset(philo->buf, 0, MESSAGE_LEN);
		ret = ft_ltobuffer(get_relative_ms(param->begin_tv), philo->buf);
		philo->buf[ret] = ' ';
		ret += ft_ltobuffer(philo->id, philo->buf + ret + 1) + 1;
		ft_memmove(philo->buf + ret, SLEEP_MSG, SLEEP_MSG_LEN);  
		write(1, philo->buf, ret + SLEEP_MSG_LEN);
	}
	ft_msleep(param->time_to_sleep, param);
}

void	philo_think(t_philo *philo, t_param *param)
{
	int ret;

	if (!check_death_bool(param))
	{
		memset(philo->buf, 0, MESSAGE_LEN);
		ret = ft_ltobuffer(get_relative_ms(param->begin_tv), philo->buf);
		philo->buf[ret] = ' ';
		ret += ft_ltobuffer(philo->id, philo->buf + ret + 1) + 1;
		ft_memmove(philo->buf + ret, THINK_MSG, THINK_MSG_LEN);  
		write(1, philo->buf, ret + THINK_MSG_LEN);
	}
}
