#include "philosophers.h"

size_t    get_death_time(t_philo *philo)
{
    pthread_mutex_lock(&philo->info->lock);
    size_t death_time = philo->info->death_time;
    pthread_mutex_unlock(&philo->info->lock);
    return (death_time);
}