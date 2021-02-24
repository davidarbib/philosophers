/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tools.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: darbib <darbib@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/24 13:36:07 by darbib            #+#    #+#             */
/*   Updated: 2021/02/24 14:42:33 by darbib           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <unistd.h>

void	ft_putnbr_fd(int n, int fd)
{
	char	s_nb[12];
	char	sign;
	size_t	i;
	char	tmp;

	sign = 0;
	if (n < 0)
		sign = 1;
	s_nb[11] = 0;
	i = 10;
	if (n == 0)
		s_nb[i--] = '0';
	while ((n >= 1 && n > 0) || (n <= -1 && n < 0))
	{
		tmp = n % 10;
		if (tmp < 0)
			tmp = tmp * -1;
		s_nb[i] = tmp + '0';
		n /= 10;
		i--;
	}
	if (sign)
		s_nb[i--] = '-';
	write(fd, s_nb + i + 1, 10 - i);
}

int		ft_atoi(const char *str)
{
	long long	nb;
	signed char	sign;

	nb = 0;
	sign = 1;
	while (*str && (*str == '\f' || *str == '\t' || *str == ' ' || *str == '\n'
			|| *str == '\r' || *str == '\v'))
		str++;
	if ((*str == '+' || *str == '-') && ft_isdigit(*(str + 1)))
	{
		if (*str == '-')
			sign = -1;
		str++;
	}
	while (*str && ft_isdigit(*str))
		nb = nb * 10 + *str++ - '0';
	return (sign * nb);
}

int		ft_isdigit(int c)
{
	if (c >= '0' && c <= '9')
		return (1);
	return (0);
}

int		ft_strcmp(const char *s1, const char *s2)
{
	while (*s1 && *s2 && (unsigned char)*s1 == (unsigned char)*s2)
	{
		s1++;
		s2++;
	}
	return ((unsigned char)*s1 - (unsigned char)*s2);
}
