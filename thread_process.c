#include "philosophers.h"

void	thread_process(t_data *ap)
{
	int	i;

	i = 0;
	while (i < ap->num_philo)
	{
		pthread_create(&ap->philos[i].thread, NULL, &routine, &ap->philos[i]);
		i++;
	}
}

void	routine(void *arg)
{
	t_philo	*philo;

	philo = (t_philo *)arg;
	pickup_forks(philo);
	eat(philo);	
}

void	pickup_forks(t_philo *philo)
{
	if (philo->id % 2 != 0)
	{
		pthread_mutex_lock(philo->l_fork);
		print_event(philo->id, "has taken left fork");
		pthread_mutex_lock(philo->r_fork);
		print_event(philo->id, "has taken right fork");
	}
	else
	{
		pthread_mutex_lock(philo->r_fork);
		print_event(philo->id, "has taken right fork");
		pthread_mutex_lock(philo->l_fork);
		print_event(philo->id, "has taken left fork");
	}
}