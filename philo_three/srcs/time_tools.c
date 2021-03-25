/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   time_tools.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: darbib <darbib@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/02 20:26:03 by darbib            #+#    #+#             */
/*   Updated: 2021/03/25 12:05:16 by darbib           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <sys/time.h>
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include "philo_three.h"

long	get_usec_from_epoch(void)
{
	struct timeval	tv;

	gettimeofday(&tv, NULL);
	return (tv.tv_usec / TIME_FACTOR + tv.tv_sec * TIME_FACTOR);
}

long	get_relative_ms(struct timeval begin_tv)
{
	struct timeval	current_tv;
	long			sec_interval;
	long			usec_interval;

	gettimeofday(&current_tv, NULL);
	sec_interval = current_tv.tv_sec - begin_tv.tv_sec;
	usec_interval = current_tv.tv_usec - begin_tv.tv_usec;
	return (usec_interval / TIME_FACTOR + sec_interval * TIME_FACTOR);
}

int		ft_msleep(int desired_interval_ms, t_param *param)
{
	struct timeval	ref_tv;

	gettimeofday(&ref_tv, NULL);
	while (get_relative_ms(ref_tv) < desired_interval_ms)
	{
		if (check_death_bool(param))
			return (1);
		usleep(SLEEP_STEP_US);
	}
	return (0);
}