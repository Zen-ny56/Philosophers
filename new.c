#include "philosophers.h"

void	thread_process(t_data *ap)
{
	int	i;

	i = 0;
	init_personal_data(ap);
	ap->start = get_start_time();
	while (i < ap->num_philo)
	{
		ap->philos[i].last_meal_time = ap->start;
		i++;
	}
	i = 0;
	while (i < ap->num_philo)
	{
		pthread_create(&ap->philos[i].thread, NULL, &routine, &ap->philos[i]);
		pthread_create(&ap->philos[i].thread, NULL, &monitor, &ap->philos[i]);
		i++;
	}
	i = 0;
	while (i < ap->num_philo)
    {
        pthread_join(ap->philos[i].thread, NULL);
		pthread_join(ap->philos[i].monitor, NULL);
		printf("Joined thread %d\n", i);
        i++;
    }
}

void *monitor(void *arg)
{
    t_philo *philo = (t_philo *)arg;

    while (1)
    {
		pthread_mutex_lock(&philo->p_data);
        if (philo->last_meal_time > philo->info->death_time)
        {
			philo->info->dead_id = philo->id;
			printf("%zu %d has died", get_start_time() - philo->info->start, philo->info->dead_id);
		}
		pthread_mutex_unlock(&philo->p_data);
		if (philo->info->dead_id != 0)
			exit(0);
    }
	return (NULL);
}

void	*routine(void *arg)
{
	t_philo	*philo;

	philo = (t_philo *)arg;
	while (1)
	{
		get_a_table(philo);
		bon_appetit(philo);
	}
	return (NULL);
}

void	get_a_table(t_philo *philo)
{

	if (philo->id % 2 > 0)
	{
		if ((*(philo->ravailable) == true) && (*(philo->lavailable) == true))
		{
	    	pthread_mutex_lock(philo->r_fork);
			pthread_mutex_lock(philo->l_fork);
			*(philo->rflag) = philo->id;
			*(philo->lflag) = philo->id;
			*(philo->ravailable) = false;
			*(philo->lavailable) = false;
			philo->is_eating = true;
			print_event(philo, "has taken a fork");
			print_event(philo, "has taken a fork");
		}
	}
	else
	{
		if ((*(philo->lavailable) == true) && (*(philo->ravailable) == true))
		{
			pthread_mutex_lock(philo->l_fork);
			pthread_mutex_lock(philo->r_fork);
			*(philo->rflag) = philo->id;
			*(philo->lflag)= philo->id;
			*(philo->lavailable) = false;
			*(philo->ravailable) = false;
			philo->is_eating = true;
			print_event(philo, "has taken a fork");
			print_event(philo, "has taken a fork");
		}
	}
}

void	bon_appetit(t_philo *philo)
{
	if (philo->is_eating == true)
	{
		eat(philo);
		drop_forks(philo);
		ft_sleep(philo);
		print_event(philo, "is thinking");
	}
}

void	drop_forks(t_philo *philo)
{
	if (philo->id % 2 > 0)
	{
		philo->is_eating = false;
		*(philo->lavailable) = true;
		*(philo->ravailable) = true;
		pthread_mutex_unlock(philo->l_fork);
		pthread_mutex_unlock(philo->r_fork);
	}
	else if (philo->id % 2 == 0)
	{
		philo->is_eating = false;
		*(philo->ravailable) = true;
		*(philo->lavailable) = true;
		pthread_mutex_unlock(philo->r_fork);
		pthread_mutex_unlock(philo->l_fork);
	}
}
