/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: darbib <darbib@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/24 13:25:27 by darbib            #+#    #+#             */
/*   Updated: 2021/03/04 14:49:50 by darbib           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include "philo_one.h"

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

	buf[20] = 0;
	i = 19;
	if (n == 0)
		buf[i--] = '0';
	while ((n >= 1 && n > 0) || (n <= -1 && n < 0))
	{
		tmp = n % 10;
		if (tmp < 0)
			tmp = tmp * -1;
		buf[i] = tmp + '0';
		n /= 10;
		i--;
	}
	ft_memmove(buf, buf + i, 19 - i);
	return ((int)(19 - i));
}

char	*concatenate_philo_message(t_philo *philo, char *message)
{
	int		timestamp_usec;
	int		count;	

	memset(message, 0, 50);
	timestamp_usec = get_usec_from_epoch();
	count = ft_ltobuffer(timestamp_usec, message);	
	message[count] = ' ';
	count += ft_ltobuffer(philo->id, message + count);	
	message[count] = ' ';
	if (philo->state == thinking)
		ft_memmove(message + count, " is thinking\n", 13);
	if (philo->state == eating)
		ft_memmove(message + count, " is eating\n", 11);
	if (philo->state == right_fork_taking)
		ft_memmove(message + count, " has taken a fork\n", 18);
	if (philo->state == left_fork_taking)
		ft_memmove(message + count, " has taken a fork\n", 18);
	if (philo->state == sleeping)
		ft_memmove(message + count, " is sleeping\n", 13);
	if (philo->state == dead)
		ft_memmove(message + count, " died\n", 6);	
	return (message);
}

void	print_state(t_philo *philo)
{
	char	message[50];

	message = concatenate_philo_message(philo, message);
	write(1, message, ft_strlen(message));
}
