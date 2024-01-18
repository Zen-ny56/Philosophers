#include "philosophers.h"

void    eat(t_philo *philo)
{
	print_event(philo, "is eating");
	ft_usleep(philo->info->eatin_time, philo->info);
	philo->last_meal_time = get_start_time();
	philo->meals_eaten++;
}

void	ft_sleep(t_philo *philo)
{
	print_event(philo, "is sleeping");
	ft_usleep(philo->info->sleepin_time, philo->info);
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
