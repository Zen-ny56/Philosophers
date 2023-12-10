#include "philosophers.h"

void	init(char **argv, t_data *ap)
{
	ap->num_philo = atoi(argv[1]);
	ap->death_time = (size_t)atoi(argv[2]);
	ap->eatin_time = (size_t)atoi(argv[3]);
	ap->sleepin_time = (size_t)atoi(argv[4]);
	if (argv[5] != NULL)
		ap->meal_times = atoi(argv[5]);
	else
		ap->meal_times = -1;
	ap->time_death = 0;
	ap->time_eat = 0;
	ap->is_even = -1;
}

void	alloc(t_data *ap)
{
	//ap->ti = (pthread_t *)malloc(sizeof(pthread_t) * ap->num_philo);
	ap->fork = (pthread_mutex_t *)malloc(sizeof(pthread_mutex_t) * ap->num_philo);
	ap->philos = (t_philo *)malloc(sizeof(t_philo) * ap->num_philo);
}

void	mutex_init(t_data *ap)
{
	int	i;

	i = 0;
	pthread_mutex_init(&ap->lock, NULL);
	pthread_mutex_init(&ap->write, NULL);
	pthread_mutex_init(&ap->philos->front_desk, NULL);
	pthread_mutex_init(&ap->picking_first, NULL);
	while (i < ap->num_philo)
	{
		pthread_mutex_init(&ap->fork[i], NULL);
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

void	init_personal_data(t_data *ap)
{
	int	i;

	i = 0;
	while (i < ap->num_philo)
	{
		ap->philos[i].id = i + 1;
		ap->philos[i].info = ap;
		i++;
	}
	i = 0;
	while (i < ap->num_philo)
	{
		ap->philos[i].ate_last = false;
		i++;
	}
	i = 0;
	while (i < ap->num_philo)
	{
		ap->philos[i].ate_last = false;
		i++;
	}
	i = 0;
	while (i < ap->num_philo)
	{
		ap->philos[i].meals_eaten = 0;
		i++;
	}
	i = 0;
	while (i < ap->num_philo)
	{
		ap->philos[i].last_meal_time = 0;
		i++;
	}
	i = 0;
	while (i < ap->num_philo)
	{
		ap->philos[i].is_dead = false;
		i++;
	}
	i = 0;
	while (i < ap->num_philo)
	{
		ap->philos[i].is_sleeping = false;
		i++;
	}
	i = 0;
	while (i < ap->num_philo)
	{
		ap->philos[i].taken_forks = false;
		i++;
	}
	i = 0;
	while (i < ap->num_philo)
	{
		ap->philos[i].pickup_forks = false;
		i++;
	}
}
