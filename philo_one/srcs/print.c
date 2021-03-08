/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: darbib <darbib@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/24 13:25:27 by darbib            #+#    #+#             */
/*   Updated: 2021/03/08 14:02:54 by darbib           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include "philo_one.h"
#include <stdio.h>

void	*ft_memmove(void *dst, const void *src, size_t len)
{
	size_t i;

	if (dst < src)
	{
		i = 0;
		while (i < len)
		{
			((unsigned char *)dst)[i] = ((unsigned char *)src)[i];
			i++;
		}
	}
	else
	{
		i = len;
		while (i-- > 0)
			((unsigned char *)dst)[i] = ((unsigned char *)src)[i];
	}
	return (dst);
}

int		ft_ltobuffer(unsigned long n, char *buf)
{
	size_t	i;
	char	tmp;
	size_t	len;

	buf[20] = 0;
	i = 19;
	if (n == 0)
		buf[i--] = '0';
	while (n >= 1)
	{
		tmp = n % 10;
		buf[i] = tmp + '0';
		n /= 10;
		i--;
	}
	len = 19 - i;
	ft_memmove(buf, buf + i + 1, len);
	if (i > -1)
		memset(buf + len, 0, i);
	return ((int)(len));
}

/*
int main()
{
	char buf[30];
	bzero(buf, 30);
	unsigned long a = 23454546457;
	int len = ft_ltobuffer(a, buf);
	printf("%s\n", buf);
	printf("%d\n", len);
	return (0);
}
*/

void	print_state(t_philo *philo, t_mutex *prompt_mutex)
{
	long	interval_ms;

	pthread_mutex_lock(prompt_mutex);
	interval_ms = get_relative_ms(philo->begin_tv);
	pthread_mutex_unlock(prompt_mutex);
	if (philo->state == thinking)
		printf("%ld %d is thinking\n", interval_ms, philo->id);
	if (philo->state == eating)
		printf("%ld %d is eating\n", interval_ms, philo->id);
	if (philo->state == right_fork_taking)
		printf("%ld %d has taken a fork\n", interval_ms, philo->id);
	if (philo->state == left_fork_taking)
		printf("%ld %d has taken a fork\n", interval_ms, philo->id);
	if (philo->state == sleeping)
		printf("%ld %d is sleeping\n", interval_ms, philo->id);
	if (philo->state == dead)
		printf("%ld %d died\n", interval_ms, philo->id);
}
