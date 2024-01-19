#include "philosophers.h"

int avai_fork(t_philo *philo)
{
    pthread_mutex_lock(&philo->p_data);
    if (*(philo->lavailable) == true && *(philo->ravailable) == true)
    {
        pthread_mutex_unlock(&philo->p_data);
        return (0);
    }
    pthread_mutex_unlock(&philo->p_data);
    return (1);
}