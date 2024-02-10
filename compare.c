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
	pthread_mutex_lock(&philo->info->death_lock);
	if (philo->info->dead_id > 0)
	{
		pthread_mutex_unlock(&philo->info->death_lock);
		return (1);
	}
	pthread_mutex_unlock(&philo->info->death_lock);
	return (0);
}

void	case_one(t_data *info)
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
	pthread_mutex_init(&info->write, NULL);
	int i = 0;
	while (i < info->num_philo)
	{
    	pthread_mutex_init(&info->fork_lock[i], NULL);
   		info->fork[i] = 0;
    	info->philos[i].l_fork = &info->fork[i];
    	info->philos[i].l_lock = &info->fork_lock[i];
    	info->philos[i].id = i + 1;
		info->philos[i].info = info;
		i++;
	}
	info->start = get_time();
	pthread_create(&info->philos[0].thread, NULL, &one_train, &info->philos[0]);
	pthread_join(info->philos[0].thread, NULL);
}

void	*one_train(void *arg)
{
	t_philo	*philo;
	philo = (t_philo *)arg;
	pthread_mutex_lock(philo->l_lock);
	*(philo->l_fork) = philo->id; 
	ft_usleep(philo->info->death_time, philo->info);
	pthread_mutex_unlock(philo->l_lock);
	print_event(philo, "has died");
	return (NULL);
}