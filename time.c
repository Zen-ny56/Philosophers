#include "philosophers.h"

void	print_event(t_philo *philo, char *event)
{
	struct timeval	now;
	size_t			time;

	pthread_mutex_lock(&ap->write);
	gettimeofday(&now, NULL);
	time = (now.tv_sec * 1000) + (now.tv_usec / 1000);
	printf("%zu %d %s\n", time - ap->start, id, event);
	pthread_mutex_unlock(&ap->write);
}