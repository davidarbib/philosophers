/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   time_tools.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: darbib <darbib@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/02 20:26:03 by darbib            #+#    #+#             */
/*   Updated: 2021/03/02 20:48:27 by darbib           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <sys/time.h>
#include <stdlib.h>

long	get_usec_from_epoch()
{
	struct timeval	tv;

	gettimeofday(&tv, NULL);
	return (tv.tv_usec);
}
