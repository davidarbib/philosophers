/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_three.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: darbib <darbib@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/26 14:25:41 by darbib            #+#    #+#             */
/*   Updated: 2021/03/28 17:34:24 by darbib           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_THREE_H
# define PHILO_THREE_H

# include <pthread.h>
# include <sys/time.h>
# include <stdio.h>
# include <fcntl.h>
# include <sys/stat.h>
# include <sys/types.h>
# include <sys/wait.h>
# include <semaphore.h>
# include <signal.h>
# include <string.h>
# include <errno.h>

# define STATE_NB		5
# define MESSAGE_LEN	50
# define TIME_FACTOR	1000
# define SLEEP_STEP_US	500
# define SIM_SHIFT_MS	10
# define FORKS_NAME		"/forks_sem"
# define FED_NAME		"/fed_sem"
# define DEATH_NAME		"/death_sem"
# define PROMPT_NAME	"/prompt_sem"
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
	his_fork_taking,
	other_fork_taking,
	eating,
	sleeping,
	thinking,
	dead
};

typedef struct		s_param
{
	int				number_of_philosophers;
	int				time_to_die;
	int				time_to_eat;
	int				time_to_sleep;
	int				number_of_times_each_philosophers_must_eat;
	int				fed_philo_n;
	struct timeval	begin_tv;
	sem_t			*fed_sem;
	sem_t			*prompt_sem;
	sem_t			*forks;
	sem_t			*death_sem;
	int				forks_nb;
	int				death;
	int				prompt_allow;
	pid_t			*pids;
}					t_param;

typedef struct		s_philo
{
	int				id;
	enum e_philo	state;
	struct timeval	last_dinner_tv;
	int				meals_n;
	int				fed;
	t_param			*sim_param;
	unsigned char	buf[MESSAGE_LEN];
}					t_philo;

void				(*g_philo_actions[STATE_NB])
											(t_philo *philo, t_param *param);
void				ft_putnbr_fd(long n, int fd);
int					ft_atoi(const char *str);
int					ft_strcmp(const char *s1, const char *s2);
int					ft_isdigit(int c);
size_t				ft_strlen(const char *s);
long				get_usec_from_epoch();
int					ft_msleep(int desired_interval_ms, t_param *param);
void				take_his_fork(t_philo *philo, t_param *param);
void				take_other_fork(t_philo *philo, t_param *param);
void				philo_eat(t_philo *place, t_param *param);
void				philo_sleep(t_philo *philo, t_param *param);
void				philo_think(t_philo *philo, t_param *param);
long				get_relative_ms(struct timeval begin_tv);
void				*live(void *atypic_philo);
void				launch_simulation(t_philo *philo, t_param *param);
int					parse_args(int ac, char **av, t_param *param);
int					check_for_death(t_philo *philo, t_param *param);
void				set_death_bool(t_param *param);
int					check_death_bool(t_param *param);
void				destroy_semaphores(t_param *param);
void				destroy_simulation(t_philo **table, t_param *param);
void				simulate_philo_table(t_param *param);
int					ft_ltobuffer(unsigned long n, unsigned char *buf);
void				*ft_memmove(void *dst, const void *src, size_t len);
void				print_actions(t_philo *philo, t_param *param, char *message,
					size_t len);

#endif
