#ifndef PHILOSOPHERS_H
# define PHILOSOPHERS_H

# include <stdlib.h>
# include <stdio.h>
# include <unistd.h>
# include <stdint.h>
# include <pthread.h>
# include <sys/time.h>
# include <stdbool.h>


typedef struct s_philo
{
	pthread_t		thread;
	size_t		time_death;
	size_t		time_eat;
	int				id;
	int				success;
	pthread_mutex_t	lock;
	int				r_fork;
	int 			l_fork;
	int 			success2;
	t_data			*info;
}
		t_philo;

typedef struct s_data
{
	size_t		eatin_ti;
	size_t		sleepin_ti;
	size_t		death_ti;
	t_philo		*philos;
	int			num_philo;
	int			meal_times;
	int			time_eat;
	int			time_death;
	pthread_mutex_t *fork;
	pthread_mutex_t write;
	size_t			start;
}
			t_data;

int		ft_isdigit(int a);
void	parse(char **av);
void	check_digit(char **av);
int		ft_atoi(const char *str);
void	init(char **argv, t_data *ap);
void	alloc(t_data *ap);
void	cleanup_data(t_data *ap);
void	mutex_init(t_data *ap);
void	thread_process(t_data *ap);
void	print_event(t_philo *philo, char *event);
size_t	get_start_time(t_data *ap);
#endif