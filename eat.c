#include "philosophers.h"

void    eat(t_philo *philo)
{
	pthread_mutex_lock(&philo->info->lock);
	print_event(philo, "is eating");
	ft_usleep(philo->info->eatin_time, philo->info);
	pthread_mutex_unlock(&philo->info->lock);
}

void	sleep(t_philo *philo)
{
	pthread_mutex_lock(&philo->info->lock);
	print_event(philo, "is sleeping");
	ft_usleep(philo->info->sleepin_time, philo->info);
	pthread_mutex_unlock(&philo->info->lock);
}

void	check_death(t_philo *philo)
{
	pthread_mutex_lock(&philo->info->lock);
	if (get_elapsed_time(philo->info) - philo->last_meal_time > philo->info->death_time)
	{
		print_event(philo, "died");
		pthread_mutex_unlock(&philo->info->lock);
		exit(0);
	}
}