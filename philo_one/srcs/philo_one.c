/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_one.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: darbib <darbib@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/24 11:39:05 by darbib            #+#    #+#             */
/*   Updated: 2021/03/03 15:45:58 by darbib           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include "philo_one.h"
#include <stdlib.h>
#include <unistd.h>

int	create_philo_table(int number_of_philosophers, t_philo **table)
{
	t_philo	*node;
	t_philo	*head;

	head = (t_philo *)malloc(sizeof(t_philo));
	if (!head)
		return (1);
	node = head;
	number_of_philosophers--;
	while (number_of_philosophers > 0)
	{
		node->next = (t_philo *)malloc(sizeof(t_philo));
		if (!node)
			return (1);
		node->id = number_of_philosophers;
		node->state = thinking;
		number_of_philosophers--;
		node = node->next;
	}
	node->next = head;
	*table = head;
	return (0);
}

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

int	parse_args(int ac, char **av, t_param *param)
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

void	*live(void *place)
{
	t_philo *philo_place;

	philo_place = (t_philo *)place;
	pthread_mutex_lock(&philo_place->fork);	
	printf("philo %d takes his fork\n", philo_place->id);
	pthread_mutex_unlock(&philo_place->fork);
	/*
	while (1)
	{
		take_his_fork();
		take_left_fork();
		eat();
		sleep();
		think();
	}
	*/
	return (NULL);
}

int main(int ac, char **av)
{
	t_param	param;
	t_philo	*table;

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
	printf("time : %lu\n", get_usec_from_epoch());
	printf("number_of_philosophers = %d\n", param.number_of_philosophers);
	printf("time_to_die = %d\n", param.time_to_die);
	printf("time_to_eat = %d\n", param.time_to_eat);
	printf("time_to_sleep = %d\n", param.time_to_sleep);
	printf("nb times eat = %d\n", param.number_of_times_each_philosophers_must_eat);
	create_philo_table(param.number_of_philosophers, &table);
	t_philo *place = table;
	while (1)
	{
		printf("philo id : %d\n", place->id);
		pthread_create(&place->philo, NULL, live, place);
		pthread_mutex_init(&place->fork, NULL);
		place = place->next;
		if (place == table)
			break;
	}
	while (1)
	{
		pthread_join(place->philo, NULL);
		place = place->next;
		if (place == table)
			break;
	}
	return (0);
}
