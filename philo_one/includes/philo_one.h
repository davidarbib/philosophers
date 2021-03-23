/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_one.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: darbib <darbib@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/26 14:25:41 by darbib            #+#    #+#             */
/*   Updated: 2021/03/23 11:39:31 by darbib           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_ONE_H
# define PHILO_ONE_H

# include <pthread.h>
# include <sys/time.h>
# include <stdio.h>

# define STATE_NB		5
# define MESSAGE_LEN	50
# define TIME_FACTOR	1000
# define SLEEP_STEP_MS	10
# define FORK_MSG_LEN	18
# define SLEEP_MSG_LEN	13
# define THINK_MSG_LEN	13
# define EAT_MSG_LEN	11
# define DIE_MSG_LEN	9
# define SLEEP_MSG		" is sleeping\n"
# define THINK_MSG		" is thinking\n"
# define FORK_MSG		" has taken a fork\n"
# define EAT_MSG		" is eating\n"
# define DIE_MSG		" is died\n"

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
	int				fed_philo_n;
	struct timeval	begin_tv;
	t_mutex			*prompt_mutex;
	int				death;
}					t_param;

typedef struct		s_philo
{
	pthread_t		soul;
	t_mutex			fork;
	int				free_fork;
	int				id;
	enum e_philo	state;
	struct timeval	last_dinner_tv;
	int				meals_n;
	t_param			*sim_param;
	unsigned char	buf[MESSAGE_LEN];
	struct s_philo	*next;
}					t_philo;

void				(*g_philo_actions[STATE_NB])
											(t_philo *philo, t_param *param);
void				print_state(t_philo *philo, t_mutex *prompt_mutex);
void				ft_putnbr_fd(long n, int fd);
int					ft_atoi(const char *str);
int					ft_strcmp(const char *s1, const char *s2);
int					ft_isdigit(int c);
size_t				ft_strlen(const char *s);
size_t				ft_ltobuffer(unsigned long n, unsigned char *buf);
void				*ft_memmove(void *dst, const void *src, size_t len);
long				get_usec_from_epoch();
int					ft_usleep(int desired_interval_ms);
void				take_his_fork(t_philo *philo, t_param *param);
void				take_left_fork(t_philo *philo, t_param *param);
void				philo_eat(t_philo *place, t_param *param);
void				philo_sleep(t_philo *philo, t_param *param);
void				philo_think(t_philo *philo, t_param *param);
long				get_relative_ms(struct timeval begin_tv);
void				simulate_philo_table(t_philo *table, t_param *param);
void				*live(void *atypic_philo);
void				launch_simulation(t_philo *philo, t_param *param);
int					parse_args(int ac, char **av, t_param *param);
int					check_for_death(t_philo *philo, t_param *param);
void				loop_until_death(t_philo *philo, t_param *param);

#endif
