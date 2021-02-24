/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_functions.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: darbib <darbib@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/24 13:25:27 by darbib            #+#    #+#             */
/*   Updated: 2021/02/24 15:51:02 by darbib           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <unistd.h>
#include "philo_one.h"

void	print_fork_taken(int timestamp, int philo_id)
{
	ft_putnbr_fd(timestamp, 1);
	write(1, " ", 1);
	ft_putnbr_fd(philo_id, 1);
	write(1, " has taken a fork\n", 18);
}

void	print_eating(int timestamp, int philo_id)
{
	ft_putnbr_fd(timestamp, 1);
	write(1, " ", 1);
	ft_putnbr_fd(philo_id, 1);
	write(1, " is eating\n", 11);
}

void	print_sleeping(int timestamp, int philo_id)
{
	ft_putnbr_fd(timestamp, 1);
	write(1, " ", 1);
	ft_putnbr_fd(philo_id, 1);
	write(1, " is sleeping\n", 13);
}

void	print_thinking(int timestamp, int philo_id)
{
	ft_putnbr_fd(timestamp, 1);
	write(1, " ", 1);
	ft_putnbr_fd(philo_id, 1);
	write(1, " is thinking\n", 13);
}

void	print_died(int timestamp, int philo_id)
{
	ft_putnbr_fd(timestamp, 1);
	write(1, " ", 1);
	ft_putnbr_fd(philo_id, 1);
	write(1, " died\n", 6);
}
