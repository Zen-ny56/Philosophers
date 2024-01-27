#include "philosophers.h"

size_t	get_death_time(t_philo *philo)
{
	pthread_mutex_lock(&philo->info->lock);
	size_t death_time = philo->info->death_time;
	pthread_mutex_unlock(&philo->info->lock);
	return (death_time);
}

// void	set_cutlery(t_philo *philo)
// {
// 	pthread_mutex_lock(&philo->p_data);
// 	philo->is_eating = true;
// 	pthread_mutex_unlock(&philo->p_data);
// }

void	update_meal_count(t_philo *philo)
{
	if (philo->info->max_meals == -1)
		return ;
	pthread_mutex_lock(&philo->mlc_lock);
	philo->meals_eaten++;
	pthread_mutex_unlock(&philo->mlc_lock);
}

void	update_meal_time(t_philo *philo)
{
	pthread_mutex_lock(&philo->mlt_lock);
	philo->last_meal_time = get_time();
	pthread_mutex_unlock(&philo->mlt_lock);
}

// void    bri_the_check(t_philo *philo)
// {
// 	pthread_mutex_lock(&philo->p_data);
// 	*(philo->la) = true;
// 	*(philo->ra) = true;
// 	philo->is_eating = false;
// 	pthread_mutex_unlock(&philo->p_data);
// }

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