#include "philo.h"

int mark_as_full(t_table *table, int index)
{
	if (table->full_check[index])
		return 1;
	table->full_check[index] = 1;
	return 0;
}

void *ft_monitor(t_philo *philos)
{
	t_table *table;
	int i;
	int j;

	j = 0;
	while (1)
	{
		i = 0;
		while (i < philos[0].table->table_size)
		{
			table = philos[i].table;
			pthread_mutex_lock(&philos[i].meal_mutex);
			if (philos[i].is_full && !mark_as_full(table, i))
				j++;
			if (j == table->table_size)
			{
				pthread_mutex_lock(&table->full_mutex);
				table->is_all_eatean = 1;
				pthread_mutex_unlock(&table->full_mutex);
				pthread_mutex_unlock(&philos[i].meal_mutex);
				return NULL;
			}
			if (ft_gettime() - philos[i].last_eat_time > table->time_to_die)
			{
				pthread_mutex_lock(&table->death_mutex);
				ft_print(NULL, philos[i], IS_DEAD);
				table->is_dead = 1;
				pthread_mutex_unlock(&table->death_mutex);
				pthread_mutex_unlock(&philos[i].meal_mutex);
				return NULL;
			}
			pthread_mutex_unlock(&philos[i].meal_mutex);
			i++;
		}
		usleep(100);
	}
	return NULL;
}
