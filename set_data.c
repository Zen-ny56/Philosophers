#include "philosophers.h"

size_t	get_death_time(t_philo *philo)
{
	size_t death_time = philo->info->death_time;
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
	philo->meals_eaten++;
}

void	update_meal_time(t_philo *philo)
{
	philo->last_meal_time = get_time();
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
	philo->info->dead_id = philo->id;
}

void	process_kill(t_data *info)
{
	pthread_mutex_lock(&info->t_lock);
	info->terminate++;
	pthread_mutex_unlock(&info->t_lock);
}