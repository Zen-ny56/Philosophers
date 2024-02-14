#include "philosophers.h"

int all_full(t_data *info)
{
	int i = 0;
	pthread_mutex_lock(&info->meal_lock);
	if (info->full_philos == info->num_philo)
	{
		pthread_mutex_unlock(&info->meal_lock);
		return (1);
	}
	pthread_mutex_unlock(&info->meal_lock);
}

int	monitor_simulation(t_data *info)
{

	while (1)
	{
		int i = 0;
		if (all_full(info))
			break ;
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
	pthread_mutex_lock(&philo->info->meal_lock);
	if (philo->meals_eaten == philo->info->max_meals)
	{
		pthread_mutex_unlock(&philo->info->meal_lock);
		return (0);
	}
	pthread_mutex_unlock(&philo->info->meal_lock);
	pthread_mutex_lock(&philo->info->time_lock);
	if ((get_time() - philo->last_meal_time) > philo->info->death_time)
	{
		philo->info->dead_id = philo->id;
		pthread_mutex_unlock(&philo->info->time_lock);
		return (philo->info->dead_id);
	}
	pthread_mutex_unlock(&philo->info->time_lock);
	return (philo->info->dead_id);
}
