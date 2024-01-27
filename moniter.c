#include "philosophers.h"

void	*monitor(void *arg)
{
	t_data *shared;
	t_philo *philos;
	int nb_philos;

	shared = (t_data *)arg;
	philos = shared->philos;
	int i = 0;
	nb_philos = shared->num_philo;
	while (1)
	{
		i = 0;
		if (ru_full(shared) == 1)
		{
			process_kill(shared);
			return (NULL);
		}
		while (i < nb_philos)
		{
			if (autopsy(&philos[i]) == 0)
			{
				timeofdeath(&philos[i]);
				process_kill(shared);
				return (NULL);
			}
			i++;
		}
	}
	return (NULL);
}

int	autopsy(t_philo *philo)
{
	pthread_mutex_lock(&philo->death_lock);
	if (get_time() - philo->last_meal_time > get_death_time(philo))
	{
		pickup_coffin(philo);
		pthread_mutex_unlock(&philo->death_lock);
		return (0);
	}
	pthread_mutex_unlock(&philo->death_lock);
	return (1);
}

void	*waiter(void *arg)
{
	t_data *shared = (t_data *)arg;
	t_philo *philo = shared->philos;
	
	if (shared->max_meals == -1)
	{
		process_kill(shared);
		return (NULL);
	}
	while (1)
	{
		int i = 0;
		if (ru_full(shared) == 1 || oj(philo) == 1)
		{
			process_kill(shared);
			return (NULL);
		}
		while (i < shared->num_philo)
		{
			if (weigh_in(&philo[i]) == 0)
			{
				pthread_mutex_lock(&shared->weight);
				shared->full_philos++;
				pthread_mutex_unlock(&shared->weight);
			}
			i++;
		}
	}
	return (NULL);
}

int	weigh_in(t_philo *philo)
{
	pthread_mutex_lock(&philo->weigh_in);
	if (philo->meals_eaten == philo->info->max_meals)
	{
		philo->full = true;
		pthread_mutex_unlock(&philo->weigh_in);
		return (0);
	}
	pthread_mutex_unlock(&philo->weigh_in);
	return (1);
}