/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_one.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: darbib <darbib@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/24 11:39:05 by darbib            #+#    #+#             */
/*   Updated: 2021/03/22 15:24:19 by darbib           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include "philo_one.h"
#include <stdlib.h>
#include <string.h>
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
	head->last_dinner_tv = (struct timeval){0, 0};
	head->meals_n = 0;
	memset(head->buf, 0, MESSAGE_LEN);
	pthread_mutex_init(&head->fork, NULL);
	head->free_fork = 1;
	node = head;
	while (number_of_philosophers >= 0)
	{
		node->next = (t_philo *)malloc(sizeof(t_philo));
		if (!node->next)
			return (1);
		node = node->next;
		node->id = number_of_philosophers--;
		node->state = thinking;
		node->last_dinner_tv = (struct timeval){0, 0};
		node->meals_n = 0;
		memset(node->buf, 0, MESSAGE_LEN);
		pthread_mutex_init(&node->fork, NULL);
		node->free_fork = 1;
	}
	node->next = head;
	*table = head;
	return (0);
}

void	init_ft_array()
{
	g_philo_actions[left_fork_taking] = take_left_fork;
	g_philo_actions[right_fork_taking] = take_his_fork;
	g_philo_actions[eating] = philo_eat;
	g_philo_actions[sleeping] = philo_sleep;
	g_philo_actions[thinking] = philo_think;
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

void	destroy_simulation(t_philo **table, t_param *param)
{
	int		i;
	t_philo	*tmp;
	t_philo	*node;

	pthread_mutex_destroy(param->prompt_mutex);
	free(param->prompt_mutex);
	param->prompt_mutex = NULL;
	node = *table;
	i = 0;
	while (i < param->number_of_philosophers)
	{
		tmp = node;
		node = node->next;
		pthread_mutex_destroy(&tmp->fork);
		free(tmp);
		i++;
	}
	*table = NULL;
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
	param.prompt_mutex = (t_mutex *)calloc(1, sizeof(t_mutex));
	if (!param.prompt_mutex)
		return (1);
	param.fed_philo_n = 0;
	param.death = 0;
	pthread_mutex_init(param.prompt_mutex, NULL);
	simulate_philo_table(table, &param);
	usleep(param.time_to_eat * TIME_FACTOR);
	destroy_simulation(&table, &param);
	return (0);
}
