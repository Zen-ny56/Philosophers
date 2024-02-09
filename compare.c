#include "philosophers.h"

int	check_status(t_philo *philo)
{
	pthread_mutex_lock(philo->status_lock_ptr);
	if (*(philo->status_ptr) == 1)
	{
		pthread_mutex_unlock(philo->status_lock_ptr);
		return (1);
	}
	pthread_mutex_unlock(philo->status_lock_ptr);
	return (0);
}

void	case_one(t_data *info)
{
	info->fork = malloc(sizeof(int) * info->num_philo);
	if (info->fork == NULL)
		return ;
	info->fork_lock = malloc(sizeof(pthread_mutex_t) * info->num_philo);
	if (info->fork_lock == NULL)
		return ;
	info->philos = malloc(sizeof(t_philo) * info->num_philo);
	if (info->philos == NULL)
		return ;
	pthread_mutex_init(&info->write, NULL);
	pthread_mutex_init(&info->fork_lock[0], NULL);
	info->fork[0] = 0;
	info->philos[0].l_fork = &info->fork[0];
	info->philos[0].l_lock = &info->fork_lock[0];
	info->philos[0].id = 1;
	info->start = get_time();
	pthread_create(&info->philos[0].thread, NULL, &one_train, &info->philos[0]);
	pthread_join(info->philos[0].thread, NULL);
	exit(0);
}

void	*one_train(void *arg)
{
	t_philo	*philo;
	philo = (t_philo *)arg;
	pick_left(philo);
	return (NULL);
	ft_usleep(philo->info->death_time, philo->info);
	drop_left(philo);
	print_event(philo, "has died");
}