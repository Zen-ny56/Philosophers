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
			i++;
		}
	}
	return (0);
}

int	autopsy(t_philo *philo)
{
	// pthread_mutex_lock(&philo->info->mt_lock);
	// if (philo->meals_eaten == philo->info->max_meals)
	// {
	// 	pthread_mutex_unlock(&philo->info->mt_lock);
	// 	return (0);
	// }
	if ((get_time() - philo->last_meal_time) > philo->info->death_time)
	{
		philo->info->dead_id = philo->id;
		pthread_mutex_unlock(&philo->info->mt_lock);
		return (philo->info->dead_id);
	}
	pthread_mutex_unlock(&philo->info->mt_lock);
	return (philo->info->dead_id);
}
