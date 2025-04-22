#include "philo.h"

void *cheack_death(t_table *table)
{
	pthread_mutex_lock(&table->death_mutex);
	if (table->is_dead)
		return (pthread_mutex_unlock(&table->death_mutex), NULL);
	pthread_mutex_unlock(&table->death_mutex);
	return (void *)1;
}

void *ft_routine(void *arg)
{
	t_philo *philo;
	t_table *table;

	philo = (t_philo *)arg;
	table = philo[0].table;
	if (philo->id % 2)
		usleep(500);
	while (1)
	{
		if (!cheack_death(table))
			return NULL;
		pthread_mutex_lock(&table->full_mutex);
		if (table->is_all_eatean)
			return (pthread_mutex_unlock(&table->full_mutex), NULL);
		pthread_mutex_unlock(&table->full_mutex);

		pthread_mutex_lock(philo->left_fork);
		pthread_mutex_lock(philo->right_fork);
		ft_print("has taken a fork", *philo, IS_ALIVE);
		ft_print("has taken a fork", *philo, IS_ALIVE);
		ft_print("is eating", *philo, IS_ALIVE);
		pthread_mutex_lock(&philo->meal_mutex);
		philo->last_eat_time = ft_gettime();
		philo->eat_count++;
		if (philo->eat_count == table->number_of_meals)
		{
			philo->is_full = 1;
		}
		pthread_mutex_unlock(&philo->meal_mutex);
		ft_usleep(philo->table->time_to_eat, table);
		pthread_mutex_unlock(philo->left_fork);
		pthread_mutex_unlock(philo->right_fork);
		ft_print("is sleeping", *philo, IS_ALIVE);
		ft_usleep(philo->table->time_to_sleep, table);
		ft_print("is thinking", *philo, IS_ALIVE);
	}
	return NULL;
}