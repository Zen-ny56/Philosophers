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
	int			*fork;
	bool		*taken_both;
	//int			terminate;
	int			num_philo;
	int			max_meals;
	int			full_philos;
	int			dead_id;
	pthread_mutex_t *fork_lock;
	pthread_mutex_t *taken_lock;
	pthread_mutex_t meal_lock;
	pthread_mutex_t death_lock;
	pthread_mutex_t time_lock;
	pthread_mutex_t write;
	size_t			start;
}
			t_data;

typedef struct s_philo
{
	int				id;
	pthread_t		thread;
	size_t	last_meal_time;
	int 		meals_eaten;
	int				*l_fork;
	int				*r_fork;
	bool			*taken_point;
	//bool			full;
	pthread_mutex_t *taken_loc;
	pthread_mutex_t	*r_lock;
	pthread_mutex_t *l_lock;
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
size_t	get_time(void);
void	*routine(void *arg);
void	eat(t_philo *philo);
void	ft_usleep(size_t time, t_data *ap);
void	check_death(t_philo *philo);
void	ft_sleep(t_philo *philo);
void	check_death(t_philo *philo);
void	cleanup_data(t_data *ap);
void	init_personal_data(t_data *ap);
void	drop_forks(t_philo *philo);
void	check_values(t_philo *philo);
void	registration(t_philo *philo);
void	r_u_on_the_list(t_philo *philo);
void	get_a_table(t_philo *philo);
void	bon_appetit(t_philo *philo);
int		lock_mutex(t_philo *philo);
void	print_values(t_philo *philo);
void	*monitor(void *arg);
void   	notify(t_philo *philo);
int     autopsy(t_philo *philo);
size_t	get_death_time(t_philo *philo);
void   *waiter(void *arg);
int		weigh_in(t_philo *philo);
void 	set_cutlery(t_philo *philo);
void    bri_the_check(t_philo *philo);
void	update_meal_count(t_philo *philo);
void	update_meal_time(t_philo *philo);
int		avai_fork(t_philo *philo);
int		satisfied(t_philo *philo);
void	pickup_coffin(t_philo *philo);
void	timeofdeath(t_philo *philo);
void	second_linen(t_philo *philo);
void 	free_memory(t_data *data);
int		oj(t_philo *philo);
int		ru_full(t_data *info);
void	process_kill(t_data *info);
int 	terminate(t_data *info);
void	join_threads(t_data *info);
void   	drop_right(t_philo *philo);
void   	drop_left(t_philo *philo);
void  	drop_forks(t_philo *philo);
void 	pick_left(t_philo *philo);
void 	pick_right(t_philo *philo);
void	check(t_philo *philo);
void 	monitor_simulation(t_data *ap);

#endif