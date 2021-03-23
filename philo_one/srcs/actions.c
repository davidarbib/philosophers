/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   actions.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: darbib <darbib@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/02 14:35:21 by darbib            #+#    #+#             */
/*   Updated: 2021/03/23 11:48:35 by darbib           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_one.h"
#include <unistd.h>
#include <string.h>
#include <stdio.h>

void	philo_eat(t_philo *philo, t_param *param)
{
	int ret;

	if (param->death == 0)
	{
		memset(philo->buf, 0, MESSAGE_LEN);
		ret = ft_ltobuffer(get_relative_ms(param->begin_tv), philo->buf);
		philo->buf[ret] = ' ';
		ret += ft_ltobuffer(philo->id, philo->buf + ret + 1) + 1;
		ft_memmove(philo->buf + ret, EAT_MSG, EAT_MSG_LEN);  
		write(1, philo->buf, ret + EAT_MSG_LEN);
	}
	gettimeofday(&philo->last_dinner_tv, NULL);
	philo->meals_n++;
	if (param->number_of_times_each_philosophers_must_eat > 0
		&& philo->meals_n == param->number_of_times_each_philosophers_must_eat)
		param->fed_philo_n++;
	ft_usleep(param->time_to_eat);
}

void	take_his_fork(t_philo *philo, t_param *param)
{
	int	ret;

	while (!philo->free_fork)
	{
		if (check_for_death(philo, param))
			return ;
	}
	pthread_mutex_lock(&philo->fork);
	philo->free_fork = 0;
	if (param->death == 0)
	{
		memset(philo->buf, 0, MESSAGE_LEN);
		ret = ft_ltobuffer(get_relative_ms(param->begin_tv), philo->buf);
		philo->buf[ret] = ' ';
		ret += ft_ltobuffer(philo->id, philo->buf + ret + 1) + 1;
		ft_memmove(philo->buf + ret, FORK_MSG, FORK_MSG_LEN);  
		write(1, philo->buf, ret + FORK_MSG_LEN);
	}
}

void	take_left_fork(t_philo *philo, t_param *param)
{
	int	ret;

	while (!philo->next->free_fork)
	{
		if (check_for_death(philo, param))
			return ;
	}
	pthread_mutex_lock(&philo->next->fork);
	philo->next->free_fork = 0;
	if (param->death == 0)
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

	pthread_mutex_unlock(&philo->fork);
	philo->free_fork = 1;
	pthread_mutex_unlock(&philo->next->fork);
	philo->next->free_fork = 1;
	if (param->death == 0)
	{
		memset(philo->buf, 0, MESSAGE_LEN);
		ret = ft_ltobuffer(get_relative_ms(param->begin_tv), philo->buf);
		philo->buf[ret] = ' ';
		ret += ft_ltobuffer(philo->id, philo->buf + ret + 1) + 1;
		ft_memmove(philo->buf + ret, SLEEP_MSG, SLEEP_MSG_LEN);  
		write(1, philo->buf, ret + SLEEP_MSG_LEN);
	}
	ft_usleep(param->time_to_sleep);
}

void	philo_think(t_philo *philo, t_param *param)
{
	int ret;

	if (param->death == 0)
	{
		memset(philo->buf, 0, MESSAGE_LEN);
		ret = ft_ltobuffer(get_relative_ms(param->begin_tv), philo->buf);
		philo->buf[ret] = ' ';
		ret += ft_ltobuffer(philo->id, philo->buf + ret + 1) + 1;
		ft_memmove(philo->buf + ret, THINK_MSG, THINK_MSG_LEN);  
		write(1, philo->buf, ret + THINK_MSG_LEN);
	}
}
