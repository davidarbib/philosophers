/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_two.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: darbib <darbib@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/26 14:25:41 by darbib            #+#    #+#             */
/*   Updated: 2021/03/25 00:26:39 by darbib           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_TWO_H
# define PHILO_TWO_H

# include <pthread.h>
# include <sys/time.h>
# include <stdio.h>
# include <fcntl.h>
# include <sys/stat.h>
# include <semaphore.h>

# define STATE_NB		5
# define MESSAGE_LEN	50
# define TIME_FACTOR	1000
# define SLEEP_STEP_US	500
# define FORKS_NAME		"/forks"
# define FED_NAME		"/fed"
# define DEATH_NAME		"/death"

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
	sem_t			*forks;
	sem_t			*death_sem;			
	int				forks_nb;
	int				death;
}					t_param;

typedef struct		s_philo
{
	pthread_t		soul;
	int				id;
	enum e_philo	state;
	struct timeval	last_dinner_tv;
	int				meals_n;
	t_param			*sim_param;
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
void				simulate_philo_table(t_philo *table, t_param *param);
void				*live(void *atypic_philo);
void				launch_simulation(t_philo *philo, t_param *param);
int					parse_args(int ac, char **av, t_param *param);
int					check_for_death(t_philo *philo, t_param *param);
void				set_death_bool(t_param *param);
int					check_death_bool(t_param *param);

#endif
