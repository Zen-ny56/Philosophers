#include "philosophers.h"

void   notify(t_philo *philo)
{
	int i = 0;
	while (i < philo->info->num_philo)
	{
		pthread_mutex_lock(&philo->p_data);
		philo->is_dead = true;
		pthread_mutex_unlock(&philo->p_data);
		i++;
	}
}

void    monitor(void *arg)
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
            if (autopsy(&philos[i], shared) == 0)
			{
				print_event(&philos[i], "died");
				notify(&philos[i]);
				return;
			}
            i++;
        }
	}
}

int     autopsy(t_philo *philo, t_data *shared)
{
    pthread_mutex_lock(&philo->p_data);
    if (get_start_time() - philo->last_meal_time > get_death_time(philo) && shared->is_dead == false)
    {
        philo->is_dead = true;
        pthread_mutex_unlock(&philo->p_data);
        return (0);
    }
    pthread_mutex_unlock(&philo->p_data);
    return (1);
}
