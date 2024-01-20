#include "philosophers.h"

size_t	get_death_time(t_philo *philo)
{
	pthread_mutex_lock(&philo->info->lock);
	size_t death_time = philo->info->death_time;
	pthread_mutex_unlock(&philo->info->lock);
	return (death_time);
}

void	set_cutlery(t_philo *philo)
{
	pthread_mutex_lock(&philo->p_data);
	*(philo->lavailable) = false;
	*(philo->ravailable) = false;
	philo->is_eating = true;
	pthread_mutex_unlock(&philo->p_data);
}

void	update_meal_count(t_philo *philo)
{
	pthread_mutex_lock(&philo->p_data);
	philo->meals_eaten++;
	pthread_mutex_unlock(&philo->p_data);
}

void	update_meal_time(t_philo *philo)
{
	pthread_mutex_lock(&philo->p_data);
	philo->last_meal_time = get_time();
	pthread_mutex_unlock(&philo->p_data);
}

void    bri_the_check(t_philo *philo)
{
	pthread_mutex_lock(&philo->p_data);
	*(philo->lavailable) = true;
	*(philo->ravailable) = true;
	philo->is_eating = false;
	pthread_mutex_unlock(&philo->p_data);
}

void	pickup_coffin(t_philo *philo)
{
	pthread_mutex_lock(&philo->info->lock);
	philo->info->dead_id = philo->id;
	pthread_mutex_unlock(&philo->info->lock);
}

void	process_kill(t_data *info)
{
	pthread_mutex_lock(&info->lock);
	info->terminate++;
	pthread_mutex_unlock(&info->lock);
}