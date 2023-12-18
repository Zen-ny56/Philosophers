#include "philosophers.h"

void	print_event(t_philo *philo, char *event)
{
	size_t			time;

	time = get_start_time();
	pthread_mutex_lock(&philo->info->write);
	printf("%zu %d %s\n", time - philo->info->start, philo->id, event);
	pthread_mutex_unlock(&philo->info->write);
}

/* size_t	get_start_time(void)
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
} */


void	ft_usleep(size_t ms, t_data *philo)
{
	(void)philo;
	size_t	time;

	time = get_start_time();
	while (get_start_time() - time < ms)
	{
		usleep(500);
	/* 	pthread_mutex_lock(&philo->data->dead_lock);
		if (philo->data->dead == 1)
		{
			pthread_mutex_unlock(&philo->data->dead_lock);
			break ;
		}
		pthread_mutex_unlock(&philo->data->dead_lock); */
	}
}

size_t	get_start_time(void)
{
	struct timeval	tv;

	if (gettimeofday(&tv, NULL))
	{
		write (2, "Error\n", 7);
		return (0);
	}
	return ((tv.tv_sec * (size_t)1000) + (tv.tv_usec / 1000));
}
