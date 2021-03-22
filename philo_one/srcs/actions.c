/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   actions.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: darbib <darbib@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/02 14:35:21 by darbib            #+#    #+#             */
/*   Updated: 2021/03/22 16:49:14 by darbib           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_one.h"
#include <unistd.h>
#include <stdio.h>

void	philo_eat(t_philo *philo, t_param *param)
{
	int ret;

	if (!param->death)
	{
		ret = ft_ltobuffer(get_relative_ms(param->begin_tv), philo->buf);
		philo->buf[ret] = ' ';
		ret += ft_ltobuffer(philo->id, philo->buf + ret + 1) + 1;
		ft_memmove(philo->buf + ret, EAT_MSG, EAT_MSG_LEN);  
		write(1, philo->buf, ret + EAT_MSG_LEN);
	}
	philo->meals_n++;
	if (param->number_of_times_each_philosophers_must_eat > 0
		&& philo->meals_n == param->number_of_times_each_philosophers_must_eat)
		param->fed_philo_n++;
	gettimeofday(&philo->last_dinner_tv, NULL);
	ft_usleep(param->time_to_eat);
}

void	take_his_fork(t_philo *philo, t_param *param)
{
	int	ret;

	while (!philo->free_fork)
	{
		if (get_relative_ms(philo->last_dinner_tv) > param->time_to_die)
		{
			philo->state = dead;
			if (param->death == 0)
			{
				ret = ft_ltobuffer(get_relative_ms(param->begin_tv), philo->buf);
				philo->buf[ret] = ' ';
				ret += ft_ltobuffer(philo->id, philo->buf + ret + 1) + 1;
				ft_memmove(philo->buf + ret, DIE_MSG, DIE_MSG_LEN);  
				write(1, philo->buf, ret + DIE_MSG_LEN);
			}
			param->death = 1;
			return ;
		}
	}	
	pthread_mutex_lock(&philo->fork);
	philo->free_fork = 0;
	if (!param->death)
	{
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
		if (get_relative_ms(philo->last_dinner_tv) > param->time_to_die)
		{
			philo->state = dead;
			if (param->death == 0)
			{
				ret = ft_ltobuffer(get_relative_ms(param->begin_tv), philo->buf);
				philo->buf[ret] = ' ';
				ret += ft_ltobuffer(philo->id, philo->buf + ret + 1) + 1;
				ft_memmove(philo->buf + ret, DIE_MSG, DIE_MSG_LEN);  
				write(1, philo->buf, ret + DIE_MSG_LEN);
			}
			param->death = 1;
			return ;
		}
	}	
	pthread_mutex_lock(&philo->next->fork);
	philo->next->free_fork = 0;
	if (!param->death)
	{
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
	if (!param->death)
	{
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

	if (!param->death)
	{
		ret = ft_ltobuffer(get_relative_ms(param->begin_tv), philo->buf);
		philo->buf[ret] = ' ';
		ret += ft_ltobuffer(philo->id, philo->buf + ret + 1) + 1;
		ft_memmove(philo->buf + ret, THINK_MSG, THINK_MSG_LEN);  
		write(1, philo->buf, ret + THINK_MSG_LEN);
	}
}
