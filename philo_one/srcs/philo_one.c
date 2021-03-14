/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_one.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: darbib <darbib@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/24 11:39:05 by darbib            #+#    #+#             */
/*   Updated: 2021/03/14 23:06:24 by darbib           ###   ########.fr       */
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

	number_of_philosophers--;
	head = (t_philo *)malloc(sizeof(t_philo));
	if (!head)
		return (1);
	head->id = number_of_philosophers--;
	head->state = thinking;
	pthread_mutex_init(&head->fork, NULL);
	node = head;
	while (number_of_philosophers >= 0)
	{
		node->next = (t_philo *)malloc(sizeof(t_philo));
		if (!node->next)
			return (1);
		node = node->next;
		node->id = number_of_philosophers--;
		node->state = thinking;
		pthread_mutex_init(&node->fork, NULL);
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
	while (philo->state != dead)
	{
		g_philo_actions[philo->state](philo, param);
		philo->state++;
		if (philo->state == STATE_NB)
			philo->state = 0;
	}
	printf("un camarade est mort\n");
	if (!param->death)
	{
		param->death = 1;
		printf("%ld %d died\n", get_relative_ms(philo->begin_tv), philo->id);
		philo->state = dead;
		usleep(param->time_to_die * 1000);
		pthread_mutex_unlock(&param->prompt_mutex);
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

void	launch_simulation(t_philo *philo, t_param *param)
{
	while (1)
	{
		philo->sim_param = param;
		pthread_create(&philo->soul, NULL, live, philo);
		printf("philo id : %d his fork is %p\n", philo->id, &philo->fork);
		if (philo->id == 0)
			break;
		philo = philo->next;
	}
}

void	wait_for_death(t_philo *philo, t_param *param)
{
	while (1)
	{
		pthread_join(philo->soul, NULL);
		if (get_relative_ms(philo->last_dinner_tv) > param->time_to_die)
		{
			philo->state = dead;
			param->death = 1;
			break;
		}
		philo = philo->next;
	}
}

void	join_threads(t_philo *philo)
{
	while (1)
	{
		pthread_join(philo->soul, NULL);
		if (philo->id == 0)
			break;
		philo = philo->next;
	}
}

void	simulate_philo_table(t_philo *table, t_param *param)
{
	t_philo *philo;
	t_philo *head;

	head = table;
	philo = table;
	launch_simulation(philo, param);
	philo = head;
	wait_for_death(philo, param);
	philo = head;
	join_threads(philo);
	printf("abort simulation\n");
}

void	print_table(t_philo *table)
{
	t_philo *philo = table;
	while (1)
	{
		printf("Philo id : %d\n", philo->id);
		printf("Philo fork : %p\n", &philo->fork);
		philo = philo->next;
	}
}

int main(int ac, char **av)
{
	t_param	param;
	t_philo	*table;
	t_mutex	*forks;
	
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
	forks = NULL;
	create_philo_table(param.number_of_philosophers, &table);
	init_ft_array();
	param.death = 0;
	pthread_mutex_init(&param.prompt_mutex, NULL);
	simulate_philo_table(table, &param);
	return (0);
}
