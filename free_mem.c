#include "philosophers.h"

void	free_memory(t_data *info)
{
	int i = 0;

	while (i < info->num_philo)
	{
		pthread_mutex_destroy(&info->philos[i].p_data);
		i++;
	}
	i = 0;
	while (i < info->num_philo)
	{
		pthread_mutex_destroy(&info->fork[i]);
		i++;
	}
	pthread_mutex_destroy(&info->write);
	pthread_mutex_destroy(&info->lock);
	free(info->array);
	free(info->available);
	free(info);
	exit(0);
}

void	join_threads(t_data *info)
{
	int i = 0;

	while (i < info->num_philo)
	{
		pthread_join(info->philos[i].thread, NULL);
		i++;
	}
	pthread_join(info->waiter, NULL);
	pthread_join(info->monitor, NULL);
}