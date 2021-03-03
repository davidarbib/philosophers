/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_one.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: darbib <darbib@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/26 14:25:41 by darbib            #+#    #+#             */
/*   Updated: 2021/03/03 15:24:05 by darbib           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_ONE_H
# define PHILO_ONE_H

# include <pthread.h>

typedef struct		s_param
{
	int	number_of_philosophers;
	int	time_to_die;
	int	time_to_eat;
	int	time_to_sleep;
	int	number_of_times_each_philosophers_must_eat;
}					t_param;

typedef pthread_mutex_t	t_mutex;

enum				e_philo
{
	left_fork_taking,
	right_fork_taking,
	eating,
	sleeping,
	thinking,
	dead
};

typedef struct		s_philo
{
	pthread_t		philo;
	t_mutex			fork;
	int				id;
	enum e_philo	state;
	struct s_philo	*next;
}					t_philo;

void				print_state(t_philo *philo);
void				ft_putnbr_fd(long n, int fd);
int					ft_atoi(const char *str);
int					ft_strcmp(const char *s1, const char *s2);
int					ft_isdigit(int c);
size_t				ft_strlen(const char *s);
long				get_usec_from_epoch();
void				take_his_fork(t_philo *philo);
void				philo_eat(t_philo *place);
void				take_left_fork(t_philo *philo);
void				philo_sleep(t_philo *philo);
void				philo_think(t_philo *philo);

#endif
