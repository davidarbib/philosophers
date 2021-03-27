/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   death_handling.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: darbib <darbib@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/27 13:27:57 by darbib            #+#    #+#             */
/*   Updated: 2021/03/27 13:33:43 by darbib           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_three.h"
#include <unistd.h>
#include <stdlib.h>

int		check_for_death(t_philo *philo, t_param *param)
{
	if (check_death_bool(param))
		return (1);
	if (get_relative_ms(philo->last_dinner_tv) > param->time_to_die)
	{
		philo->state = dead;
		set_death_bool(param);
		printf("%ld %d died\n", get_relative_ms(param->begin_tv),
				philo->id);
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
