#include "philosophers.h"

void	init(char **argv, t_data *ap)
{
	ap->num_philo = atoi(argv[1]);
	ap->death_ti = (size_t)atoi(argv[2]);
	ap->eatin_ti = (size_t)atoi(argv[3]);
	ap->sleepin_ti = (size_t)atoi(argv[4]);
	if (argv[5] != NULL)
		ap->meal_times = atoi(argv[5]);
	else
		ap->meal_times = -1;
	ap->time_death = 0;
	ap->time_eat = 0;
}

void	alloc(t_data *ap)
{
	ap->ti = (pthread_t *)malloc(sizeof(pthread_t) * ap->num_philo);
	ap->fork = (pthread_mutex_t *)malloc(sizeof(pthread_mutex_t) * ap->num_philo);
	ap->philos = (t_philo *)malloc(sizeof(t_philo) * ap->num_philo);
}

void	mutex_init(t_data *ap)
{
	int	i;

	i = 0;
	while (i < ap->num_philo)
	{
		pthread_mutex_init(&ap->fork[i], NULL);
		i++;
	} 
	i = 0;
	while (i < ap->num_philo)
	{
		ap->philos[i].id = i + 1;
		i++;
	}
	i = 0;
	while (i < ap->num_philo)
	{
		ap->philos[i].l_fork = &ap->fork[i];
		ap->philos[i].r_fork = &ap->fork[(i + 1) % ap->num_philo];
		i++;
	}
}