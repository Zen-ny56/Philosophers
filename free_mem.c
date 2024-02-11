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
		printf("%d\n",i);
		pthread_join(info->philos[i].thread, NULL);
		i++;
	}
	printf("Threads are joined \n");
	i = 0;
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
	free(info);
}