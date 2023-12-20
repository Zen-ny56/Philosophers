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
		check_death(philo);
		if (philo->info->is_dead == true)
		{
			print_event(philo, "died");
			exit(0);
		}
		get_a_table(philo);
		r_u_on_the_list(philo);	
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
		*(philo->rflag) = philo->id;
		*(philo->lflag) = philo->id;
		print_event(philo, "has taken a fork");
		print_event(philo, "has taken a fork");
	}
	else
	{
		pthread_mutex_lock(philo->l_fork);
		pthread_mutex_lock(philo->r_fork);
		*(philo->rflag) = philo->id;
		*(philo->lflag)= philo->id;
		print_event(philo, "has taken a fork");
		print_event(philo, "has taken a fork");
	}
}

void	r_u_on_the_list(t_philo *philo)
{
	if (*(philo->lflag) == philo->id && *(philo->rflag) == philo->id)
		philo->is_eating = true;
	// else
	// {
	// 	if (*(philo->lflag ) != philo->id)
	// 	{
	// 		pthread_mutex_unlock(philo->l_fork);
	// 		*(philo->lflag) = 0;
	// 	}	
	// 	else if (*(philo->rflag) != philo->id)
	// 	{
	// 		pthread_mutex_unlock(philo->r_fork);
	// 		*(philo->rflag) = 0;
	// 	}
	// 	philo->is_eating = false;
	// }
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
		pthread_mutex_unlock(philo->l_fork);
		pthread_mutex_unlock(philo->r_fork);
	}
	else if (philo->id % 2 == 0)
	{
		pthread_mutex_unlock(philo->r_fork);
		pthread_mutex_unlock(philo->l_fork);
	}
}
