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
		while (i < nb_philos)
		{
			if (autopsy(&philos[i]) == 0)
			{
				timeofdeath(&philos[i]);
				return (NULL);
			}
			i++;
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