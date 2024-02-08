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