#include "philosophers.h"

int	eat(t_philo *philo)
{
	int b;
	if (check_status(philo))
	{
		b = drop_forks(philo);
		return (1);
	}
	// print_event(philo, "is eating");
	pthread_mutex_lock(&philo->info->meal_lock);
	if (philo->info->max_meals != -1)
	{
		philo->meals_eaten++;
		if (philo->info->max_meals == philo->meals_eaten)
		{
			philo->info->full_philos++;
			if (philo->info->full_philos == philo->info->num_philo)
			{
				ft_usleep(philo->info->eatin_time,philo);
				//drop_forks(philo);
				pthread_mutex_unlock(&philo->info->meal_lock);
				//free_mem(philo->info);
				exit(0);
			}
			ft_usleep(philo->info->eatin_time,philo);
			drop_forks(philo);
			pthread_mutex_unlock(&philo->info->meal_lock);
			return (1);
		}
	}
	pthread_mutex_unlock(&philo->info->meal_lock);
	ft_usleep(philo->info->eatin_time,philo);
	return (0);
}

int	ft_sleep(t_philo *philo)
{
	if (check_status(philo))
		return (1);
	print_event(philo, "is sleeping");
	ft_usleep(philo->info->sleepin_time,philo);
	//print_event(philo, "is thinking");
	return (0);
}

int	thinking(t_philo *philo)
{
	if (check_status(philo))
		return (1);
	print_event(philo, "is thinking");
	return (0);
}
