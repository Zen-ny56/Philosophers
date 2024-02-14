#include "philosophers.h"

void	free_mem(t_data *info)
{
	int i = 0;
	while (i < info->num_philo)
	{
		pthread_mutex_destroy(&info->fork_lock[i]);
		i++;
	}
	pthread_mutex_destroy(&info->write);
	pthread_mutex_destroy(&info->meal_lock);
	pthread_mutex_destroy(&info->time_lock);   
	if (info->philos != NULL) {
		free(info->philos);
		info->philos = NULL;
	}
	if (info->fork_lock != NULL) {
		free(info->fork_lock);
		info->fork_lock = NULL;
	}
	if (info->fork != NULL) {
		free(info->fork);
		info->fork = NULL;
	}
}