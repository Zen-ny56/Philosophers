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
}

void	pickup_forks(t_philo *philo)
{
	print_event(philo->id, "has taken left fork");
	print_event(philo->id, "has taken right fork");
}