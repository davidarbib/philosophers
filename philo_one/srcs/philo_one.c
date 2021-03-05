/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_one.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: darbib <darbib@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/24 11:39:05 by darbib            #+#    #+#             */
/*   Updated: 2021/03/05 16:39:12 by darbib           ###   ########.fr       */
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

void	*live(void *pack_in)
{
	t_philo *philo;
	t_param *param;
	t_pack	*pack;

	pack = (t_pack *)pack_in;
	philo = pack->philo;
	param = pack->param;
	//pthread_mutex_lock(&philo_place->fork);	
	//printf("philo %d takes his fork\n", philo_place->id);
	//pthread_mutex_unlock(&philo_place->fork);
	while (1)
	{
		print_state(philo, &pack->prompt_mutex);
		pack->philo_actions[philo->state](philo, param);
		philo->state++;
		if (philo->state == STATE_NB)
			philo->state = 0;
	}
	return (NULL);
}

void	init_ft_array(void (*philo_actions[STATE_NB])(t_philo *philo, 
														t_param *param))
{
	philo_actions[left_fork_taking] = take_left_fork;
	philo_actions[right_fork_taking] = take_his_fork;
	philo_actions[eating] = philo_eat;
	philo_actions[sleeping] = philo_sleep;
	philo_actions[thinking] = philo_think;
}

void	simulate_philo_table(t_pack *sim_pack)
{
	t_philo *philo;
	t_philo *head;

	head = sim_pack->philo;
	philo = sim_pack->philo;
	while (1)
	{
		sim_pack->philo = philo;
		pthread_create(&philo->soul, NULL, live, sim_pack);
		pthread_mutex_init(&philo->fork, NULL);
		philo = philo->next;
		if (philo == head)
			break;
	}
	while (1)
	{
		pthread_join(philo->soul, NULL);
		philo = philo->next;
		if (philo == head)
			break;
	}
}

int main(int ac, char **av)
{
	t_param	param;
	t_philo	*table;
	t_pack	pack;
	
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
	init_ft_array(pack.philo_actions);
	pack.philo = table;
	pack.param = &param;
	pthread_mutex_init(&pack.prompt_mutex, NULL);
	simulate_philo_table(&pack);
	return (0);
}
