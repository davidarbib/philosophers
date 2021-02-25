#ifndef PHILO_ONE_H
# define PHILO_ONE_H

typedef struct	s_philo
{
	int	number_of_philosophers;
	int	time_to_die;
	int	time_to_eat;
	int	time_to_sleep;
	int	number_of_times_each_philosophers_must_eat;
}				t_philo;

void	print_died(int timestamp, int philo_id);
void	print_fork_taken(int timestamp, int philo_id);
void	print_eating(int timestamp, int philo_id);
void	print_sleeping(int timestamp, int philo_id);
void	print_thinking(int timestamp, int philo_id);
void	ft_putnbr_fd(int n, int fd);
int		ft_atoi(const char *str);
int		ft_strcmp(const char *s1, const char *s2);
int		ft_isdigit(int c);
size_t	ft_strlen(const char *s);

#endif
