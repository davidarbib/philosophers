/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_args.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: darbib <darbib@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/18 12:48:11 by darbib            #+#    #+#             */
/*   Updated: 2021/03/25 12:06:20 by darbib           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_three.h"

int		check_arg(char *arg)
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

int		parse_args(int ac, char **av, t_param *param)
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
	if (param->number_of_philosophers < 2)
		return (1);
	param->time_to_die = ft_atoi(av[2]);
	param->time_to_eat = ft_atoi(av[3]);
	param->time_to_sleep = ft_atoi(av[4]);
	if (ac == 6)
		param->number_of_times_each_philosophers_must_eat = ft_atoi(av[5]);
	else
		param->number_of_times_each_philosophers_must_eat = 0;
	return (0);
}
