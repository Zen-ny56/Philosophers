#include "philosophers.h"

void	init(char **argv, t_data *ap)
{
	ap->num_philo = atoi(argv[1]);
	ap->death_time = (size_t)atoi(argv[2]);
	ap->eatin_time = (size_t)atoi(argv[3]);
	ap->sleepin_time = (size_t)atoi(argv[4]);
	if (argv[5] != NULL)
		ap->max_meals = atoi(argv[5]);
	else
		ap->max_meals = -1;
	ap->started = false;
	ap->dead_id = 0;
	ap->full_philos = 0;
	ap->terminate = 0;
}

void	alloc(t_data *ap)
{
	ap->available = (bool *)malloc(sizeof(bool) * ap->num_philo);
	if (ap->available == NULL)
		return ;
	ap->fork = (int *)malloc(sizeof(int) * ap->num_philo);
	if (ap->fork == NULL)
		return ;
	ap->fork_lock = (pthread_mutex_t *)malloc(sizeof(pthread_mutex_t) * ap->num_philo);
	if (ap->fork_lock == NULL)
		return ;
	ap->philos = (t_philo *)malloc(sizeof(t_philo) * ap->num_philo);
	if (ap->philos == NULL)
		return ;
	ap->check = (pthread_mutex_t *)malloc(sizeof(pthread_mutex_t) * 1);
	if (ap->check == NULL)
		return ;
}

void	mutex_init(t_data *ap)
{
	int	i;

	i = 0;
	pthread_mutex_init(&ap->lock, NULL);
	pthread_mutex_init(&ap->write, NULL);
	while (i < ap->num_philo)
	{
		ap->fork[i] = 0;
		ap->available[i] = true;
		pthread_mutex_int(&ap->check[i], NULL);
		ap->philos[i].checkp = &ap->check[i];
		pthread_mutex_init(&ap->fork_lock[i], NULL);
		i++;
	}
	while (i < ap->num_philo)
	{
		ap->philos[i].l_lock = &ap->fork_lock[i];
		ap->philos[i].r_lock = &ap->fork_lock[(i + 1) % ap->num_philo];
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
		ap->philos[i].meals_eaten = 0;
		ap->philos[i].last_meal_time = 0;
		ap->philos[i].is_dead = false;
		ap->philos[i].full = false;
		i++;
	}
}