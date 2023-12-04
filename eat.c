#include "philosophers.h"

void    eat(t_philo *philo)
{
	pthread_mutex_lock(&philo->info->lock);
	philo->is_eating = true;
	print_event(philo, "is eating");
	ft_usleep(philo->info->eatin_time, philo->info);
	pthread_mutex_unlock(&philo->info->lock);
}

void	ft_sleep(t_philo *philo)
{
	pthread_mutex_lock(&philo->info->lock);
	philo->is_eating = false;
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
		pthread_join(philo->thread, NULL);
		pthread_mutex_destroy(&philo->info->lock);
		pthread_mutex_destroy(philo->info->fork);
		cleanup_data(philo->info);
		exit(0);
	}
}

void	cleanup_data(t_data *ap)
{
	int	i;

	i = 0;
	while (i < ap->num_philo)
	{
		pthread_mutex_destroy(&ap->fork[i]);
		i++;
	}
	pthread_mutex_destroy(&ap->write);
	free(ap->fork);
	free(ap->philos);
}