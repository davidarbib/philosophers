/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: darbib <darbib@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/24 13:25:27 by darbib            #+#    #+#             */
/*   Updated: 2021/03/11 21:26:59 by darbib           ###   ########.fr       */
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
void	print_state(t_philo *philo, t_mutex *prompt_mutex)
{
	(void)prompt_mutex;
	long	interval_ms;

	//pthread_mutex_lock(prompt_mutex);
	interval_ms = get_relative_ms(philo->begin_tv);
	if (philo->state == thinking)
	if (philo->state == eating)
	if (philo->state == right_fork_taking)
	{
	}
	if (philo->state == left_fork_taking)
	{
	}
	if (philo->state == sleeping)
	if (philo->state == dead)
	//if (philo->state != dead)
	//	pthread_mutex_unlock(prompt_mutex);
}
*/
