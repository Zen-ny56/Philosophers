#include "philosophers.h"

void    eat(t_philo *philo)
{
	print_event(philo, "is eating");
	ft_usleep(philo->info->eatin_time, philo->info);
	philo->last_meal_time = 0;
	philo->meals_eaten++;
}

void	ft_sleep(t_philo *philo)
{
	print_event(philo, "is sleeping");
	ft_usleep(philo->info->sleepin_time, philo->info);
}

void	check_death(t_philo *philo)
{
	pthread_mutex_lock(&philo->info->lock);
	size_t time_passed = get_start_time() - philo->info->start;
	size_t time_s_lmeal = time_passed - philo->last_meal_time;
    if (time_s_lmeal > philo->info->death_time)
		philo->info->is_dead = true;
	pthread_mutex_unlock(&philo->info->lock);
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
