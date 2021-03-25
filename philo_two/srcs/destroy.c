/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   destroy.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: darbib <darbib@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/25 11:49:14 by darbib            #+#    #+#             */
/*   Updated: 2021/03/25 11:53:21 by darbib           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_two.h"
#include <stdlib.h>

void	destroy_semaphores(t_param *param)
{
	sem_unlink(DEATH_NAME);
	sem_unlink(FED_NAME);
	sem_unlink(FORKS_NAME);
	sem_close(param->death_sem);
	sem_close(param->fed_sem);
	sem_close(param->forks);
}

void	destroy_simulation(t_philo **table, t_param *param)
{
	destroy_semaphores(param);
	free(*table);
	*table = NULL;
}
