#include "philosophers.h"

void	print_event(t_philo *philo, char *event)
{
	size_t			time;

	pthread_mutex_lock(&philo->info->write);
	pthread_mutex_lock(&philo->info->lock);
	time = get_elapsed_time(philo->info);
	pthread_mutex_unlock(&philo->info->lock);
	printf("%zu %d %s\n", time, philo->id, event);
	pthread_mutex_unlock(&philo->info->write);
}

size_t	get_start_time(void)
{
	struct timeval	start;

	gettimeofday(&start, NULL);
	return (start.tv_sec * 1000) + (start.tv_usec / 1000);
}

size_t	get_elapsed_time(t_data *ap)
{
	struct timeval	now;
	size_t			time;

	gettimeofday(&now, NULL);
	time = (now.tv_sec * 1000) + (now.tv_usec / 1000);
	return (time - ap->start);
}

void	ft_usleep(size_t time, t_data *ap)
{
	size_t	end_time;

	end_time = get_elapsed_time(ap) + time;
	while (get_elapsed_time(ap) < end_time)
		usleep(100);
}