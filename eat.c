#include "philosophers.h"

void    eat(t_philo *philo)
{
	pthread_mutex_lock(&philo->info->lock);
	print_event(philo, "is eating");
	philo->lflag = &philo->id;
	philo->rflag = &philo->id;
	philo->info->meal_times++;
	philo->just_ate = true;
	pthread_mutex_unlock(&philo->info->lock);
	philo->meals_eaten++;
	ft_usleep(philo->info->eatin_time, philo->info);
}

void	ft_sleep(t_philo *philo)
{
	pthread_mutex_lock(&philo->info->lock);
	print_event(philo, "is sleeping");
	pthread_mutex_unlock(&philo->info->lock);
}

void	check_death(t_philo *philo)
{
	pthread_mutex_lock(&philo->info->lock);
	if (get_elapsed_time(philo->info) - philo->last_meal_time > philo->info->death_time)
	{
		philo->is_dead = true;
		print_event(philo, "died");
		pthread_mutex_unlock(&philo->info->lock);
		pthread_join(philo->thread, NULL);
		pthread_mutex_destroy(&philo->info->lock);
		pthread_mutex_destroy(philo->info->fork);
		cleanup_data(philo->info);
	}
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
