/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_one.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: darbib <darbib@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/24 11:39:05 by darbib            #+#    #+#             */
/*   Updated: 2021/02/24 14:44:30 by darbib           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_one.h"
#include <stdlib.h>
#include <unistd.h>

int check_arg(char *arg) 
{
	int i;

	i = 0;
	while (arg[i] && ft_isdigit(arg[i]))
		i++;
	if (arg[i])
		return (0);


}

int	parse_args(int ac, char **av, t_philo *param)
{
	int		i;
	char	*arg;
	
	i = 0;
	success = 1;
	while (i < ac)
		success *= check_arg(av[i]);
}

int main(int ac, char **av)
{
	t_philo	param;

	if (ac < 5 || ac > 6)
	{
		write(2, "Error arguments\n", 16);
		return (1);
	}
	parse_args(ac, av, &param);
	print_fork_taken(10, 2);
	print_eating(10, 2);
	print_sleeping(10, 2);
	print_thinking(10, 2);
	print_died(10, 2);
	return (0);
}
