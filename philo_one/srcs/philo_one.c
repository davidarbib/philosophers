/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_one.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: darbib <darbib@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/24 11:39:05 by darbib            #+#    #+#             */
/*   Updated: 2021/03/09 15:55:31 by darbib           ###   ########.fr       */
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
	while (number_of_philosophers >= 0)
	{
		node->next = (t_philo *)malloc(sizeof(t_philo));
		if (!node)
			return (1);
		node->id = number_of_philosophers;
		node->state = thinking;
		//if (node->id % 2)
		//	node->state = sleeping;
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

int		check_death(t_philo *philo, int	time_to_die)
{
	if (get_relative_ms(philo->last_dinner_tv) > time_to_die)
		return (1);
	return (0);
}

void	*live(void *atypic_philo)
{
	t_philo *philo;
	t_param *param;

	philo = (t_philo *)atypic_philo;
	printf("philo id in thread : %d\n", philo->id);
	param = philo->sim_param;
	gettimeofday(&philo->begin_tv, NULL);
	philo->last_dinner_tv = philo->begin_tv;
	if (philo->id % 2)
		usleep(1000);
	while (1)
	{
		if (check_death(philo, param->time_to_die))
			break;
		print_state(philo, &param->prompt_mutex);
		g_philo_actions[philo->state](philo, param);
		philo->state++;
		if (philo->state == STATE_NB)
			philo->state = 0;
	}
	return (NULL);
}

void	init_ft_array()
{
	g_philo_actions[left_fork_taking] = take_left_fork;
	g_philo_actions[right_fork_taking] = take_his_fork;
	g_philo_actions[eating] = philo_eat;
	g_philo_actions[sleeping] = philo_sleep;
	g_philo_actions[thinking] = philo_think;
}

void	simulate_philo_table(t_philo *table, t_param *param)
{
	t_philo *philo;
	t_philo *head;

	head = table;
	philo = table;
	while (1)
	{
		philo->sim_param = param;
		pthread_mutex_init(&philo->fork, NULL);
		pthread_create(&philo->soul, NULL, live, philo);
		printf("philo id : %d\n", philo->id);
		if (philo->id == 0)
			break;
		philo = philo->next;
	}
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
	create_philo_table(param.number_of_philosophers, &table);
	init_ft_array();
	pthread_mutex_init(&param.prompt_mutex, NULL);
	simulate_philo_table(table, &param);
	while (1)
		;
	return (0);
}
