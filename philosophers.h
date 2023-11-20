#ifndef PHILOSOPHERS_H
# define PHILOSOPHERS_H

# include <stdlib.h>
# include <stdio.h>
# include <unistd.h>
# include <stdint.h>
# include <pthread.h>
# include <sys/time.h>


typedef struct s_philo
{
	pthread_t		thread;
	size_t		time_death;
	size_t		time_eat;
	int				id;
	pthread_mutex_t	lock;
	pthread_mutex_t	*r_fork;
	pthread_mutex_t *l_fork;
}
		t_philo;

typedef struct s_data
{
	pthread_t	*ti;
	size_t		eatin_ti;
	size_t		sleepin_ti;
	size_t		death_ti;
	t_philo		*philos;
	int			num_philo;
	int			meal_times;
	int			time_eat;
	int			time_death;
	pthread_mutex_t waiter;
	pthread_mutex_t *fork;
	pthread_mutex_t write;
}
			t_data;

int		ft_isdigit(int a);
int		parse(char **av);
void	check_digit(char **av);
int		ft_atoi(const char *str);
void	init(char **argv, t_data *ap);
void	alloc(t_data *ap);
void	cleanup_data(t_data *ap);
void	mutex_init(t_data *ap);

#endif