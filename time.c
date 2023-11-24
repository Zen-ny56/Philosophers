#include "philosophers.h"

void	print_event(t_philo *philo, char *event)
{
	struct timeval	now;
	size_t			time;

	pthread_mutex_lock(&philo->info->write);
	gettimeofday(&now, NULL);
	time = (now.tv_sec * 1000) + (now.tv_usec / 1000);
	printf("%zu %d %s\n", time - philo->info->start, philo->id, event);
	pthread_mutex_unlock(&philo->info->write);
}

size_t	get_start_time(t_data *ap)
{
	struct timeval	start;
	(void)ap;

	gettimeofday(&start, NULL);
	return (start.tv_sec * 1000) + (start.tv_usec / 1000);
}
