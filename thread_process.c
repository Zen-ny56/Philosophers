#include "philosophers.h"

void	thread_process(t_data *ap)
{
	int	i;

	i = 0;
	while (i < ap->num_philo)
	{
		pthread_create(&ap->philos[i], NULL, &routine, &ap->philos[i]);
		i++;
	}
}

void	routine(t_data *ap)
{
	int i;

	i = 0;
	while (i < ap->num_philo)
	{
		pthread_mutex_init(&ap->philos[i].lock , NULL);
		i++;
	}
	pthread_mutex_init(&ap->waiter, NULL);
	i = 0;
	while (1)
	{
		pthread_mutex_lock(&ap->waiter);
		if (ap->fork_taken[i] == false && ap->fork_taken[(i + 1) % ap->num_philo] == false)
		{
			pthread_mutex_lock(ap->philos[i].l_fork);
			ap->fork_taken[i] = true;
			pthread_mutex_lock(ap->philos[i].r_fork);
			ap->fork_taken[(i + 1) % ap->num_philo] = true;
		}
		pthread_mutex_unlock(&ap->waiter);
		eat(ap);
	}
}

void	eat(t_data *ap)
{
	int i;

	i = ap->philos->id;
	pthread_mutex_lock(&ap->philos[i].lock);
}