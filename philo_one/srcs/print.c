/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: darbib <darbib@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/24 13:25:27 by darbib            #+#    #+#             */
/*   Updated: 2021/03/03 14:43:41 by darbib           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <unistd.h>
#include "philo_one.h"

void	print_state(t_philo *philo)
{
	ft_putnbr_fd(get_usec_from_epoch(), 1);
	write(1, " ", 1);
	ft_putnbr_fd(philo->id, 1);
	if (philo->state == thinking)
		write(1, " is thinking\n", 13);
	if (philo->state == eating)
		write(1, " is eating\n", 11);
	if (philo->state == right_fork_taking)
		write(1, " has taken a fork\n", 18);
	if (philo->state == left_fork_taking)
		write(1, " has taken a fork\n", 18);
	if (philo->state == sleeping)
		write(1, " is sleeping\n", 13);
	if (philo->state == dead)
		write(1, " died\n", 6);
}
