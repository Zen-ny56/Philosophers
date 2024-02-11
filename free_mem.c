#include "philosophers.h"

// void	free_memory(t_data *info)
// {
// 	int i = 0;

// 	while (i < info->num_philo)
// 	{
// 		pthread_mutex_destroy(&info->philos[i].p_data);
// 		i++;
// 	}
// 	i = 0;
// 	while (i < info->num_philo)
// 	{
// 		pthread_mutex_destroy(&info->fork[i]);
// 		i++;
// 	}
// 	pthread_mutex_destroy(&info->write);
// 	pthread_mutex_destroy(&info->lock);
// 	free(info->array);
// 	free(info->available);
// 	free(info);
// 	exit(0);
// }

void	free_mem(t_data *info)
{
	int i = 0;

	while (i < info->num_philo)
	{
		pthread_join(info->philos[i].thread, NULL);
		i++;
	}
	while (i < info->num_philo)
    {
        pthread_mutex_destroy(&info->fork_lock[i]);
        i++;
    }
    pthread_mutex_destroy(&info->write);
    pthread_mutex_destroy(&info->mt_lock);
    free(info->philos);
    free(info->fork_lock);
    free(info->fork);
}