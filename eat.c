#include "philosophers.h"

void    eat(t_philo *philo)
{
	pthread_mutex_lock(&philo->info->lock);
	philo->is_eating = true;
	print_event(philo, "is eating");
	pthread_mutex_unlock(&philo->info->lock);
	ft_usleep(philo->info->eatin_time, philo->info);
	philo->meals_eaten++;
	if (philo->is_eating == true)
	{
		drop_forks(philo);
		ft_sleep(philo);
	}
}

void	ft_sleep(t_philo *philo)
{
	pthread_mutex_lock(&philo->lala);
	pthread_mutex_lock(&philo->info->lock);
	philo->is_eating = false;
	print_event(philo, "is sleeping");
	pthread_mutex_unlock(&philo->info->lock);
	pthread_mutex_unlock(&philo->lala);
}

void	check_death(t_philo *philo)
{
	pthread_mutex_lock(&philo->life_check);
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
		exit(0);
	}
	pthread_mutex_unlock(&philo->info->lock);
	pthread_mutex_unlock(&philo->life_check);
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