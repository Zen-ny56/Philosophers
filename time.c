#include "philosophers.h"

void	print_event(t_philo *philo, char *event)
{
	size_t			time;
	pthread_mutex_lock(&philo->info->write);
	if (check_status(philo))
	{
		pthread_mutex_unlock(&philo->info->write);
		return;
	}
	time = get_time();
	printf("%zu %d %s\n", time - philo->info->start, philo->id, event);
	pthread_mutex_unlock(&philo->info->write);
}

void	ft_usleep(size_t ms, t_philo *philo)
{
	size_t	time;

	time = get_time();
	while (get_time() - time < ms)
	{
		if (check_status(philo))
			return ;
		usleep(500);
	}
}

size_t	get_time(void)
{
	struct timeval	tv;

	if (gettimeofday(&tv, NULL))
	{
		write (2, "Error\n", 7);
		exit(1);
	}
	return ((tv.tv_sec * (size_t)1000) + (tv.tv_usec / (size_t)1000));
}

void	timeofdeath(t_philo *philo)
{
	size_t			time;

	time = get_time();
	pthread_mutex_lock(&philo->info->write);
	printf("%zu %d philo has died\n", time - philo->info->start, philo->info->dead_id);
	pthread_mutex_unlock(&philo->info->write);
}