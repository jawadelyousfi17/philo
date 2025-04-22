#include "philo.h"

void	ft_destroy_table(t_table *table)
{
	pthread_mutex_destroy(&table->death_mutex);
	pthread_mutex_destroy(&table->print_mutex);
	pthread_mutex_destroy(&table->full_mutex);
	free(table->full_check);
	free(table);
}

void	ft_destroy(t_philo *philos, int index)
{
	t_table	*table;
	int		i;

	table = philos[0].table;
	ft_destroy_table(table);
	while (i < index)
	{
		pthread_mutex_destroy(&philos[i].meal_mutex);
		i++;
	}
	free(philos);
}

void	ft_destroy_forks(pthread_mutex_t *forks, int index)
{
	int i;

	i = 0;
	while (i < index)
	{
		pthread_mutex_destroy(&forks[i]);
		i++;
	}
	free(forks);
}