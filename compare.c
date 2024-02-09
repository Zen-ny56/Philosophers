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
	info->fork[0] = 0;
	info->philos[0].l_fork = &info->fork[0];
	pthread_create(&info->philos[0].thread, NULL, one_train, &info->philos[0]);
}

void	*one_train(void *arg)
{
	t_data *info = (t_data *)arg;
	t_philo *philo = info->philos;
	
	pick_left(philo);
	ft_usleep(info->death_time, info);
	drop_left(philo);
	print_event(philo, "has died");
	return (NULL);
}