#include "philosophers.h"

void	init(char **argv, t_data *info)
{
	info->num_philo = atoi(argv[1]);
	info->death_time = (size_t)atoi(argv[2]);
	info->eatin_time = (size_t)atoi(argv[3]);
	info->sleepin_time = (size_t)atoi(argv[4]);
	if (argv[5] != NULL)
		info->max_meals = atoi(argv[5]);
	else
		info->max_meals = -1;
	info->dead_id = 0;
	info->full_philos = 0;
	//info->terminate = 0;
}

void	alloc(t_data *info)
{
	info->fork = (int *)malloc(sizeof(int) * info->num_philo);
	if (info->fork == NULL)
		return ;
	info->fork_lock = (pthread_mutex_t *)malloc(sizeof(pthread_mutex_t) * info->num_philo);
	if (info->fork_lock == NULL)
		return ;
	info->philos = (t_philo *)malloc(sizeof(t_philo) * info->num_philo);
	if (info->philos == NULL)
		return ;
	info->status = (int *)malloc(sizeof(int) * info->num_philo);
	if (info->status == NULL)
		return ;
	info->status_lock = (pthread_mutex_t *)malloc(sizeof(pthread_mutex_t) * info->num_philo);
	if (info->status_lock == NULL)
		return ;
}

void	mutex_init(t_data *info)
{
	int	i;

	i = 0;
	pthread_mutex_init(&info->write, NULL);
	pthread_mutex_init(&info->death_lock, NULL);
	pthread_mutex_init(&info->time_lock, NULL);
	pthread_mutex_init(&info->meal_lock, NULL);
	while (i < info->num_philo)
	{
		info->fork[i] = 0;
		info->status[i] = 0;
		info->philos[i].info = info;
		pthread_mutex_init(&info->status_lock[i], NULL);
		pthread_mutex_init(&info->fork_lock[i], NULL);
		i++;
	}
	i = 0;
	while (i < info->num_philo)
	{
		info->philos[i].l_lock = &info->fork_lock[i];
		info->philos[i].r_lock = &info->fork_lock[(i + 1) % info->num_philo];
		info->philos[i].l_fork = &info->fork[i];
		info->philos[i].r_fork = &info->fork[(i + 1) % info->num_philo];
		info->philos[i].status_ptr = &info->status[i];
		info->philos[i].status_lock_ptr = &info->status_lock[i];
		i++;
	}
}

void	init_personal_data(t_data *info)
{
	int	i;

	i = 0;
	while (i < info->num_philo)
	{
		info->philos[i].id = i + 1;
		info->philos[i].info = info;
		info->philos[i].meals_eaten = 0;
		info->philos[i].last_meal_time = 0;
		i++;
	}
}