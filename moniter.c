#include "philosophers.h"

int	monitor_simulation(t_data *info)
{

	while (1)
	{
		int i = 0;
		while (i < info->num_philo)
		{
			if (autopsy(&info->philos[i]) > 0)
				return (info->dead_id);
			if (waiter(&info->philos[i]) > 0)
				change_status(&info->philos[i]);
			i++;
		}
	}
	return (0);
}


void	change_status(t_philo *philo)
{
	pthread_mutex_lock(philo->status_lock_ptr);
	*(philo->status_ptr) = 1;
	pthread_mutex_unlock(philo->status_lock_ptr);
}

int	autopsy(t_philo *philo)
{
	pthread_mutex_lock(&philo->info->time_lock);
	if ((get_time() - philo->last_meal_time) > philo->info->death_time)
	{
		pthread_mutex_lock(&philo->info->death_lock);
		philo->info->dead_id = philo->id;
		pthread_mutex_unlock(&philo->info->death_lock);
		pthread_mutex_unlock(&philo->info->time_lock);
		return (philo->info->dead_id);
	}
	pthread_mutex_unlock(&philo->info->time_lock);
	return (philo->info->dead_id);
}

int		waiter(t_philo *philo)
{
	pthread_mutex_lock(&philo->info->meal_lock);
	if (philo->meals_eaten == philo->info->max_meals)
	{
		pthread_mutex_unlock(&philo->info->meal_lock);
		return (1);
	}
	pthread_mutex_unlock(&philo->info->meal_lock);
	return (0);
}
