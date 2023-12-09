#include "philosophers.h"

void	thread_process(t_data *ap)
{
	int	i;

	i = 0;
	init_personal_data(ap);
	ap->start = get_start_time();
	while (i < ap->num_philo)
	{
		pthread_create(&ap->philos[i].thread, NULL, &routine, &ap->philos[i]);
		i++;
	}
	i = 0;
	while (i < ap->num_philo)
    {
        pthread_join(ap->philos[i].thread, NULL);
		printf("Joined thread %d\n", i);
        i++;
    }
}

void	*routine(void *arg)
{
	t_philo	*philo;

	philo = (t_philo *)arg;
	check_values(philo);
	check_death(philo);
	pickup_forks(philo);
	if (philo->is_eating == true)
	{
		drop_forks(philo);
		ft_sleep(philo);
	}
		return (NULL);
}

void	pickup_forks(t_philo *philo)
{
	if (philo->id % 2 > 0)
	{
		pthread_mutex_lock(philo->l_fork);
		print_event(philo, "has taken left fork");
		pthread_mutex_lock(philo->r_fork);
		print_event(philo, "has taken right fork");
		eat(philo);
	}
	else
	{
		pthread_mutex_lock(philo->r_fork);
		print_event(philo, "has taken right fork");
		pthread_mutex_lock(philo->l_fork);
		print_event(philo, "has taken left fork");
		eat(philo);
	}
}

void	drop_forks(t_philo *philo)
{
	pthread_mutex_unlock(philo->l_fork);
	pthread_mutex_unlock(philo->r_fork);
	pthread_mutex_lock(&philo->info->lock);
	philo->last_meal_time = get_elapsed_time(philo->info);
	philo->ate_last = true;
	pthread_mutex_unlock(&philo->info->lock);
}

void	check_values(t_philo *philo)
{
	(void)philo;
	return ;
}