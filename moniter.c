#include "philosophers.h"

void	monitor_simulation(t_data *ap)
{

	while (1)
	{
		int i = 0;
		while (i < ap->num_philo)
		{
			pthread_mutex_lock(&ap->time_lock);
			if (get_time() - ap->philos[i].last_meal_time > get_death_time(&ap->philos[i]))
			{
				pthread_mutex_unlock(&ap->time_lock);
				pthread_mutex_lock(&ap->death_lock);
				ap->philos[i].info->dead_id = ap->philos[i].id;
				pthread_mutex_unlock(&ap->death_lock);
				return (ap);
			}
		}
	}
	return (NULL);
}

int	autopsy(t_philo *philo)
{

	if (get_time() - philo->last_meal_time > get_death_time(philo))
	{
		philo->info->dead_id = philo->id;
		return (0);
	}
	return (1);
}

void	*waiter(void *arg)
{
	t_data *shared = (t_data *)arg;
	t_philo *philo = shared->philos;
	while (1)
	{
		int i = 0;
		while (i < shared->num_philo)
		{
			if (weigh_in(&philo[i]) == 0)
			{
				shared->full_philos++;
			}
			i++;
		}
	}
	return (NULL);
}

int	weigh_in(t_philo *philo)
{
	if (philo->meals_eaten == philo->info->max_meals)
	{
		philo->full = true;
		return (0);
	}
	return (1);
}