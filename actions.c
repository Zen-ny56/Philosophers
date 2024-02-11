#include "philosophers.h"

int	eat(t_philo *philo)
{
	if (check_status(philo))
		return (1);
	print_event(philo, "is eating");
	ft_usleep(philo->info->eatin_time, philo->info);
	pthread_mutex_lock(&philo->info->mt_lock);
	philo->last_meal_time = get_time();
	if (philo->info->max_meals != -1)
		philo->meals_eaten++;
	if (philo->info->max_meals == philo->meals_eaten)
	{
		philo->info->full_philos++;
		if (philo->info->full_philos == philo->info->num_philo)
		{
			drop_forks(philo);
			pthread_mutex_unlock(&philo->info->mt_lock);
			exit(0);
		}
		drop_forks(philo);
		print_event(philo, "is thinking");
		pthread_mutex_unlock(&philo->info->mt_lock);
		return (1);
	}
	pthread_mutex_unlock(&philo->info->mt_lock);
	return (0);

}

int	ft_sleep(t_philo *philo)
{
	if (check_status(philo))
		return (1);
	print_event(philo, "is sleeping");
	ft_usleep(philo->info->sleepin_time, philo->info);
	print_event(philo, "is thinking");
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
	*(philo->l_fork) = philo->id;
	print_event(philo, "has taken a fork");
}

void	pick_right(t_philo *philo)
{
	pthread_mutex_lock(philo->r_lock);
	*(philo->r_fork) = philo->id;
	print_event(philo, "has taken a fork");
}

