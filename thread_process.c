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
	philo->time_death = 0;
	while (1)
	{
		philo->success = pthread_mutex_lock(&philo->info->fork[philo->l_fork]);
		philo->success2 = pthread_mutex_lock(&philo->info->fork[philo->r_fork]);
		if (philo->success == 0 && philo->success2 == 0)
		{
			pickup_forks(philo);
			eat(philo);
			pthread_mutex_unlock(&philo->info->fork[philo->l_fork]);
			pthread_mutex_unlock(&philo->info->fork[philo->r_fork]);
		}
		else if (philo->success != 0 || philo->success2 != 0)
		{
			print_event(philo->id, "is thinking");
		}
	}
}

void	eat(t_philo *philo)
{
	philo->time_death = 0;
	print_event(philo->id, "is eating");
	usleep(philo->info->time_eat * 1000);
	philo->time_death += philo->info->time_eat;
	print_event(philo->id, "is sleeping");
	usleep(philo->info->sleepin_ti * 1000);
	philo->time_death += philo->info->sleepin_ti;
	philo->success = 1;
	philo->success2 = 1;
}

void	pickup_forks(t_philo *philo)
{
	print_event(philo->id, "has taken left fork");
	print_event(philo->id, "has taken right fork");
}