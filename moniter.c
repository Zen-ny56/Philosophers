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
		while (i < nb_philos)
		{
			if (autopsy(&philos[i]) == 0)
			{
				second_linen(&philos[i]);
				return (NULL);
			}
			i++;
		}
	}
	return (NULL);
}

int	autopsy(t_philo *philo)
{
	pthread_mutex_lock(&philo->p_data);
	if (get_time() - philo->last_meal_time > get_death_time(philo))
	{
		pickup_coffin(philo);
		pthread_mutex_unlock(&philo->p_data);
		return (0);
	}
	pthread_mutex_unlock(&philo->p_data);
	return (1);
}

void	*waiter(void *arg)
{
	t_data *shared = (t_data *)arg;
	t_philo *philo = shared->philos;
	while (1)
	{
		int i = 0;
		if (ru_full(shared) == 1 || oj(shared) == 1)
			return (NULL);
		while (i < shared->num_philo)
		{
			if (weigh_in(&philo[i]) == 0)
			{
				pthread_mutex_lock(&shared->lock);
				shared->full_philos++;
				pthread_mutex_unlock(&shared->lock);
			}
			i++;
		}
	}
	return (NULL);
}

int	weigh_in(t_philo *philo)
{
	pthread_mutex_lock(&philo->p_data);
	if (philo->meals_eaten == philo->info->max_meals)
	{
		philo->full = true;
		pthread_mutex_unlock(&philo->p_data);
		return (0);
	}
	pthread_mutex_unlock(&philo->p_data);
	return (1);
}