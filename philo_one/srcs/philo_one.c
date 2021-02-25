/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_one.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: darbib <darbib@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/24 11:39:05 by darbib            #+#    #+#             */
/*   Updated: 2021/02/25 13:48:14 by darbib           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include "philo_one.h"
#include <stdlib.h>
#include <unistd.h>

int check_arg(char *arg) 
{
	int i;
	int len;

	i = 0;
	while (arg[i] && ft_isdigit(arg[i]))
		i++;
	if (arg[i])
		return (0);
	len = ft_strlen(arg);
	if (len > 10)
		return (0);
	if (len == 10 && ft_strcmp(arg, "2147483647") > 0)
		return (0);
	return (1);
}

int	parse_args(int ac, char **av, t_philo *param)
{
	int		i;
	int		success;
	
	i = 1;
	success = 1;
	while (i < ac)
		success *= check_arg(av[i++]);
	if (!success)
		return (1);
	param->number_of_philosophers = ft_atoi(av[1]);
	param->time_to_die = ft_atoi(av[2]);
	param->time_to_eat = ft_atoi(av[3]);
	param->time_to_sleep = ft_atoi(av[4]);
	if (ac == 6)
		param->number_of_times_each_philosophers_must_eat = ft_atoi(av[5]);
	else
		param->number_of_times_each_philosophers_must_eat = 0;
	return (0);
}

int main(int ac, char **av)
{
	t_philo	param;

	if (ac < 5 || ac > 6)
	{
		write(2, "Error arguments\n", 16);
		return (1);
	}
	if (parse_args(ac, av, &param))
	{
		write(2, "Error arguments\n", 16);
		return (1);
	}
	printf("number_of_philosophers = %d\n", param.number_of_philosophers);
	printf("time_to_die = %d\n", param.time_to_die);
	printf("time_to_eat = %d\n", param.time_to_eat);
	printf("time_to_sleep = %d\n", param.time_to_sleep);
	printf("nb times eat = %d\n", param.number_of_times_each_philosophers_must_eat);
	print_fork_taken(10, 2);
	print_eating(10, 2);
	print_sleeping(10, 2);
	print_thinking(10, 2);
	print_died(10, 2);
	return (0);
}
