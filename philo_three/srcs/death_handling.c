/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   death_handling.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: darbib <darbib@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/27 13:27:57 by darbib            #+#    #+#             */
/*   Updated: 2021/03/28 17:40:34 by darbib           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_three.h"
#include <unistd.h>
#include <stdlib.h>

int		check_for_death(t_philo *philo, t_param *param)
{
	int ret;

	if (check_death_bool(param))
		return (1);
	if (get_relative_ms(philo->last_dinner_tv) > param->time_to_die)
	{
		set_death_bool(param);
		sem_wait(param->prompt_sem);
		param->prompt_allow = 0;
		memset(philo->buf, 0, MESSAGE_LEN);
		ret = ft_ltobuffer(get_relative_ms(param->begin_tv), philo->buf);
		philo->buf[ret] = ' ';
		ret += ft_ltobuffer(philo->id, philo->buf + ret + 1) + 1;
		ft_memmove(philo->buf + ret, DIE_MSG, DIE_MSG_LEN);
		write(1, philo->buf, ret + DIE_MSG_LEN);
		return (1);
	}
	return (0);
}

int		check_death_bool(t_param *param)
{
	int death;

	sem_wait(param->death_sem);
	death = param->death;
	sem_post(param->death_sem);
	return (death);
}

void	set_death_bool(t_param *param)
{
	sem_wait(param->death_sem);
	param->death = 1;
	sem_post(param->death_sem);
}
