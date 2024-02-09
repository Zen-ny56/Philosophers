#include "philosophers.h"

int	eat(t_philo *philo)
{
	if (check_status(philo))
		return (1);
	pthread_mutex_lock(philo->taken_lock_ptr);
	if (philo->taken_ptr == false)
	{
		pthread_mutex_unlock(philo->taken_lock_ptr);
		return (0);
	}
	pthread_mutex_unlock(philo->taken_lock_ptr);
	ft_usleep(philo->info->eatin_time, philo->info);
	pthread_mutex_lock(&philo->info->time_lock);
	philo->last_meal_time = get_time();
	pthread_mutex_unlock(&philo->info->time_lock);
	pthread_mutex_lock(&philo->info->meal_lock);
	if (philo->info->max_meals != -1)
		philo->meals_eaten++;
	pthread_mutex_unlock(&philo->info->meal_lock);
	return (0);

}

int	ft_sleep(t_philo *philo)
{
	if (check_status(philo))
		return (1);
	pthread_mutex_lock(philo->taken_lock_ptr);
	if (philo->taken_ptr == false)
	{
		pthread_mutex_unlock(philo->taken_lock_ptr);
		return (0);
	}
	pthread_mutex_unlock(philo->taken_lock_ptr);
	print_event(philo, "is sleeping");
	ft_usleep(philo->info->sleepin_time, philo->info);
	return (0);
}

int	thinking(t_philo *philo)
{
	if (check_status(philo))
		return (1);
	print_event(philo, "is thinking");
	return (0);
}

void	pick_left(t_philo *philo)
{
	pthread_mutex_lock(philo->l_lock);
	*(philo->l_fork) = 1;
	print_event(philo, "has taken a fork");
}

void	pick_right(t_philo *philo)
{
	pthread_mutex_lock(philo->r_lock);
	*(philo->r_fork) = 1;
	print_event(philo, "has taken a fork");
}