#ifndef PHILOSOPHERS_H
# define PHILOSOPHERS_H

# include <stdlib.h>
# include <stdio.h>
# include <unistd.h>
# include <stdint.h>
# include <pthread.h>
# include <sys/time.h>
# include <stdbool.h>

typedef struct s_philo t_philo;

typedef struct s_data
{
	size_t		eatin_time;
	size_t		sleepin_time;
	size_t		death_time;
	t_philo		*philos;
	int			num_philo;
	int			meal_times;
	int			time_eat;
	int			time_death;
	int			is_even;
	pthread_mutex_t	lock;
	pthread_mutex_t picking_first;
	pthread_mutex_t *fork;
	pthread_mutex_t write;
	size_t			start;
}
			t_data;

typedef struct s_philo
{
	pthread_t		thread;
	size_t	last_meal_time;
	size_t		meals_eaten;
	int					id;
	bool			ate_last;
	bool			is_eating;
	bool			is_dead;
	bool			is_sleeping;
	bool			taken_forks;
	bool			pickup_forks;
	pthread_mutex_t	front_desk;
	pthread_mutex_t	*r_fork;
	pthread_mutex_t *l_fork;
	t_data			*info;
}
		t_philo;


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
size_t	get_start_time(void);
void	*routine(void *arg);
void	eat(t_philo *philo);
void	ft_usleep(size_t time, t_data *ap);
void	check_death(t_philo *philo);
void	ft_sleep(t_philo *philo);
void	check_death(t_philo *philo);
void	cleanup_data(t_data *ap);
size_t	get_elapsed_time(t_data *ap);
void	init_personal_data(t_data *ap);
void	drop_forks(t_philo *philo);
void	check_values(t_philo *philo);
void	registration(t_philo *philo);
void	r_u_on_the_list(t_philo *philo);
void	get_a_table(t_philo *philo);
void	bon_appetit(t_philo *philo);

#endif