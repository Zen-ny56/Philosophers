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
	t_philo		*philos;
	size_t		eatin_time;
	size_t		sleepin_time;
	size_t		death_time;
	size_t			start;
	int			*fork;
	// int		*taken_both;
	int			*status;
	int			num_philo;
	int			max_meals;
	int			full_philos;
	int			dead_id;
	pthread_mutex_t *fork_lock;
	pthread_mutex_t *status_lock;
	pthread_mutex_t meal_lock;
	pthread_mutex_t death_lock;
	pthread_mutex_t time_lock;
	pthread_mutex_t write;
}
			t_data;

typedef struct s_philo
{
	struct s_data	*info;
	int				id;
	pthread_t		thread;
	size_t	last_meal_time;
	int 		meals_eaten;
	int				*l_fork;
	int				*r_fork;
	int				*taken_ptr;
	int				*status_ptr;
	pthread_mutex_t *status_lock_ptr;
	pthread_mutex_t	*r_lock;
	pthread_mutex_t *l_lock;
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
size_t	get_time(void);
void	*routine(void *arg);
void	ft_usleep(size_t time, t_data *ap);
void	cleanup_data(t_data *ap);
void	init_personal_data(t_data *ap);
int		get_a_table(t_philo *philo);
void   	notify(t_philo *philo);
int     autopsy(t_philo *philo);
int		waiter(t_philo *philo);
int		eat(t_philo *philo);
int		ft_sleep(t_philo *philo);
int		thinking(t_philo *philo);
int		drop_forks(t_philo *philo);
// void 	free_memory(t_data *data);
void	join_threads(t_data *info);
void   	drop_right(t_philo *philo);
void   	drop_left(t_philo *philo);
void 	pick_left(t_philo *philo);
void 	pick_right(t_philo *philo);
void	drop_one(t_philo *philo);
int 	monitor_simulation(t_data *ap);
void	change_status(t_philo *philo);
int		check_status(t_philo *philo);
void 	notify_death(t_data *info);
void	*one_train(void *arg);
void	case_one(t_data *info);
#endif