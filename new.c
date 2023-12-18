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
	while (1)
	{	
		/* if (philo->meals_eaten == 0)
		{
			get_a_table(philo);
			registration(philo);
			bon_appetit(philo);
			pthread_mutex_lock(&philo->info->write);
			printf("here\n");
			pthread_mutex_unlock(&philo->info->write);
		}
		else
		{
			if (philo->lflag != philo->id && philo->rflag != philo->id)
			{
				get_a_table(philo);
				bon_appetit(philo);
			}
		} */
		// if (philo->lflag == philo->id && philo->rflag == philo->id)
		// {
		// 	print_event(philo, "is thinking");
		// 	while (philo->lflag == philo->id && philo->rflag == philo->id)
		// 		usleep(100);
		// }
		get_a_table(philo);
		// if (philo->lflag == &philo->id && philo->rflag == &philo->id)
		// {
		// 	drop_forks(philo);
		// }
		// philo->lflag = &philo->id;
		// philo->rflag = &philo->id;
		bon_appetit(philo);
	}
	return (NULL);
}

void	get_a_table(t_philo *philo)
{

	if (philo->id % 2 > 0)
	{
	    pthread_mutex_lock(philo->r_fork);
		pthread_mutex_lock(philo->l_fork);
		print_event(philo, "has taken a fork");
		print_event(philo, "has taken a fork");
	}
	else
	{
		pthread_mutex_lock(philo->l_fork);
		pthread_mutex_lock(philo->r_fork);
		print_event(philo, "has taken a fork");
		print_event(philo, "has taken a fork");
	}
}

void	bon_appetit(t_philo *philo)
{
	eat(philo);
	drop_forks(philo);
	ft_sleep(philo);
	//print_event(philo, "is thinking");
}

void	drop_forks(t_philo *philo)
{
	if (philo->id % 2 > 0)
	{
		pthread_mutex_unlock(philo->l_fork);
		pthread_mutex_unlock(philo->r_fork);
	}
	else if (philo->id % 2 == 0)
	{
		pthread_mutex_unlock(philo->r_fork);
		pthread_mutex_unlock(philo->l_fork);
	}
}
