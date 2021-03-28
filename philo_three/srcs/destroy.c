/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   destroy.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: darbib <darbib@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/25 11:49:14 by darbib            #+#    #+#             */
/*   Updated: 2021/03/28 17:16:09 by darbib           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_three.h"
#include <stdlib.h>

void	destroy_semaphores(t_param *param)
{
	sem_unlink(DEATH_NAME);
	sem_unlink(FED_NAME);
	sem_unlink(FORKS_NAME);
	sem_unlink(PROMPT_NAME);
	sem_close(param->death_sem);
	sem_close(param->fed_sem);
	sem_close(param->forks);
	sem_close(param->prompt_sem);
}
