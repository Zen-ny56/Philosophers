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

// int	wash_fork(t_philo *philo)
// {
// 	pthread_mutex_lock(&philo->p_data);
// 	if ((philo->rflag == philo->id || philo->rflag == philo->id)
// 		&& philo->meals_eaten > 0)
// 	{
// 		pthread_mutex_unlock(&philo->p_data);
// 		return (1);
// 	}
// 	pthread_mutex_unlock(&philo->p_data);
// 	return (0);
// }

void	set_cutlery(t_philo *philo)
{
	pthread_mutex_lock(&philo->p_data);
	*(philo->lavailable) = false;
	*(philo->ravailable) = false;
	pthread_mutex_unlock(&philo->p_data);
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