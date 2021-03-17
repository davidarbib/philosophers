/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_one.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: darbib <darbib@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/24 11:39:05 by darbib            #+#    #+#             */
/*   Updated: 2021/03/17 15:39:00 by darbib           ###   ########.fr       */
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
	//head->last_dinner_tv = (struct timeval){0, 0};
	head->meals_n = 0;
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
		node->last_dinner_tv = (struct timeval){0, 0};
		node->meals_n = 0;
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
	philo->last_dinner_tv = param->begin_tv;
	if (philo->id % 2)
		usleep(10);
	while (!param->death)
	{
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

void	launch_simulation(t_philo *philo, t_param *param)
{
	gettimeofday(&param->begin_tv, NULL);
	while (1)
	{
		philo->sim_param = param;
		pthread_create(&philo->soul, NULL, live, philo);
		pthread_detach(philo->soul);
		printf("philo id : %d his fork is %p\n", philo->id, &philo->fork);
		if (philo->id == 0)
			break;
		philo = philo->next;
	}
}

void	wait_for_death(t_philo *philo, t_param *param)
{
	param->fed_philo_n = 0;
	usleep(param->time_to_eat * TIME_FACTOR);
	while (1)
	{
		if (get_relative_ms(philo->last_dinner_tv) > param->time_to_die)
		{
			philo->state = dead;
			param->death = 1;
			printf("%ld %d died\n", get_relative_ms(param->begin_tv),
					philo->id);
			break;
		}
		if (param->fed_philo_n == param->number_of_philosophers)
		{
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

	philo = table;
	launch_simulation(philo, param);
	philo = table;
	wait_for_death(philo, param);
	//philo = table;
	//join_threads(philo);
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
		//pthread_mutex_destroy(&tmp->fork);
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
	pthread_mutex_init(param.prompt_mutex, NULL);
	simulate_philo_table(table, &param);
	usleep(param.time_to_eat * TIME_FACTOR);
	destroy_simulation(&table, &param);
	return (0);
}
