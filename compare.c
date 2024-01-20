#include "philosophers.h"

int avai_fork(t_philo *philo)
{
	pthread_mutex_lock(&philo->p_data);
	if (*(philo->lavailable) == true && *(philo->ravailable) == true)
	{
		pthread_mutex_unlock(&philo->p_data);
		return (0);
	}
	pthread_mutex_unlock(&philo->p_data);
	return (1);
}

void	second_linen(t_philo *philo)
{
	pthread_mutex_lock(&philo->info->lock);
	if (philo->info->dead_id == philo->id)
		timeofdeath(philo);
	pthread_mutex_unlock(&philo->info->lock);
}

int	satisfied(t_philo *philo)
{
	pthread_mutex_lock(&philo->p_data);
	if (philo->full == true)
	{
		pthread_mutex_unlock(&philo->p_data);
		return (1);
	}
	pthread_mutex_unlock(&philo->p_data);
	return (0);
}

int	oj(t_philo *philo)
{
	pthread_mutex_lock(&philo->info->lock);
	if (philo->info->dead_id != 0)
	{
		pthread_mutex_unlock(&philo->info->lock);
		return (1);
	}
	pthread_mutex_unlock(&philo->info->lock);
	return (0);
}

int	ru_full(t_data *info)
{
	pthread_mutex_lock(&info->lock);
	if (info->full_philos >= info->num_philo)
	{
		pthread_mutex_unlock(&info->lock);
		return (1);
	}
	pthread_mutex_unlock(&info->lock);
	return (0);
}

int terminate(t_data *info)
{
	pthread_mutex_lock(&info->lock);
	if (info->terminate == 3)
	{
		pthread_mutex_unlock(&info->lock);
		return (1);
	}
	pthread_mutex_unlock(&info->lock);
	return (0);
}