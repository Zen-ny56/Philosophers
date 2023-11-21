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
	while (1)
	{
		pthread_mutex_lock(&philo->info->fork[philo->l_fork]);
		print_event(philo->id, "has taken left fork");
		pthread_mutex_lock(&philo->info->fork[philo->r_fork]);
		print_event(philo->id, "has taken right fork");
		eat(philo);
	}
}

void	eat(t_philo *philo)
{
	while (philo)
	{
		print_event(philo, "is eating");
	
	}
}