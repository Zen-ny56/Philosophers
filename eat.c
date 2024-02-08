#include "philosophers.h"

void    eat(t_philo *philo)
{
	ft_usleep(philo->info->eatin_time, philo->info);
	pthread_mutex_lock(&philo->info->time_lock);
	philo->last_meal_time = get_time();
	pthread_mutex_unlock(&philo->info->time_lock);
	pthread_mutex_lock(&philo->info->gym);
	if (philo->info->max_meals != -1)
		philo->meals_eaten++;
	pthread_mutex_unlock(&philo->info->gym);

}

void	ft_sleep(t_philo *philo)
{
	print_event(philo, "is sleeping");
	ft_usleep(philo->info->sleepin_time, philo->info);
}

// void	cleanup_data(t_data *ap)
// {
// 	int	i;

// 	i = 0;
// 	while (i < ap->num_philo)
// 	{
// 		pthread_mutex_destroy(&ap->fork[i]);
// 		i++;
// 	}
// 	pthread_mutex_destroy(&ap->write);
// 	free(ap->fork);
// 	free(ap->philos);
// }
