/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_one.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: darbib <darbib@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/26 14:25:41 by darbib            #+#    #+#             */
/*   Updated: 2021/03/14 23:07:04 by darbib           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_ONE_H
# define PHILO_ONE_H

# include <pthread.h>
# include <sys/time.h>

# define STATE_NB		5
# define MESSAGE_LEN	50
# define TIME_FACTOR	1000
# define SLEEP_STEP		500

enum				e_philo
{
	right_fork_taking,
	left_fork_taking,
	eating,
	sleeping,
	thinking,
	dead
};

typedef pthread_mutex_t	t_mutex;

typedef struct		s_param
{
	int				number_of_philosophers;
	int				time_to_die;
	int				time_to_eat;
	int				time_to_sleep;
	int				number_of_times_each_philosophers_must_eat;
	t_mutex			prompt_mutex;
	int				death;
}					t_param;

typedef struct		s_philo
{
	pthread_t		soul;
	t_mutex			fork;
	int				id;
	enum e_philo	state;
	struct timeval	begin_tv;
	struct timeval	last_dinner_tv;
	t_param			*sim_param;
	struct s_philo	*next;
}					t_philo;

void				(*g_philo_actions[STATE_NB])
											(t_philo *philo, t_param *param);
t_mutex				g_test_mutex;
void				print_state(t_philo *philo, t_mutex *prompt_mutex);
void				ft_putnbr_fd(long n, int fd);
int					ft_atoi(const char *str);
int					ft_strcmp(const char *s1, const char *s2);
int					ft_isdigit(int c);
size_t				ft_strlen(const char *s);
long				get_usec_from_epoch();
int					ft_usleep(int desired_interval_ms);
void				take_his_fork(t_philo *philo, t_param *param);
void				take_left_fork(t_philo *philo, t_param *param);
void				philo_eat(t_philo *place, t_param *param);
void				philo_sleep(t_philo *philo, t_param *param);
void				philo_think(t_philo *philo, t_param *param);
long				get_relative_ms(struct timeval begin_tv);

#endif
