#include "philo.h"

t_table*	ft_init_table(int ac, char **av)
{
	t_table	*tmp_table;
	int err;

	err = 0;
	tmp_table = malloc(sizeof(t_table));
	if (!tmp_table)
		return (NULL);
	tmp_table->is_all_eatean = 0;
	tmp_table->is_dead = 0;
	tmp_table->start_time = ft_gettime();
	tmp_table->table_size = ft_atol(av[1], &err);
	tmp_table->time_to_die = ft_atol(av[2], &err);
	tmp_table->time_to_eat = ft_atol(av[3], &err);
	tmp_table->time_to_sleep = ft_atol(av[4], &err);
	tmp_table->number_of_meals = -1;
	tmp_table->full_check = malloc(tmp_table->table_size * sizeof(int));
	memset(tmp_table->full_check, 0, tmp_table->table_size * sizeof(int));
	if (ac == 6)
		tmp_table->number_of_meals = ft_atol(av[5], &err);
	if (err == -1)
		return (free(tmp_table), NULL);
	if (pthread_mutex_init(&tmp_table->death_mutex, NULL) != 0)
	{
		pthread_mutex_destroy(&tmp_table->death_mutex);
		return (free(tmp_table->full_check), free(tmp_table), NULL);
	}
	if (pthread_mutex_init(&tmp_table->print_mutex, NULL) != 0)
	{
		pthread_mutex_destroy(&tmp_table->death_mutex);
		pthread_mutex_destroy(&tmp_table->print_mutex);
		return (free(tmp_table->full_check), free(tmp_table), NULL);
	}
	if (pthread_mutex_init(&tmp_table->full_mutex, NULL) != 0)
	{
		pthread_mutex_destroy(&tmp_table->death_mutex);
		pthread_mutex_destroy(&tmp_table->print_mutex);
		return (free(tmp_table->full_check), free(tmp_table), NULL);
	}
	return (tmp_table);
}

pthread_mutex_t	*ft_init_forks(t_table *table)
{
	pthread_mutex_t	*forks;
	int				i;

	forks = malloc(sizeof(pthread_mutex_t) * table->table_size);
	if (!forks)
		return (NULL);
	i = 0;
	while (i < table->table_size)
	{
		if (pthread_mutex_init(&forks[i], NULL) != 0)
		{
			ft_destroy_forks(forks, i - 1);
			return (NULL);
		}
		i++;
	}
	return (forks);
}

t_philo *ft_init_philos(t_table *table, pthread_mutex_t *forks, void *(*ft_routine)(void *))
{
	t_philo	*philos;
	int		i;

	philos = malloc(sizeof(t_philo) * table->table_size);
	if (!philos)
		return (NULL);
	i = 0;
	while (i < table->table_size)
	{
		philos[i].id = i + 1;
		philos[i].eat_count = 0;
		philos[i].is_full = 0;
		philos[i].last_eat_time = ft_gettime();
		philos[i].table = table;
		philos[i].left_fork = &forks[i];
		philos[i].right_fork = &forks[(i + 1) % table->table_size];
		if (pthread_create(&philos[i].thread, NULL, ft_routine, &philos[i]) != 0)
		{
			ft_destroy(philos, i - 1);
			return NULL;
		}
		if (pthread_mutex_init(&philos[i].meal_mutex, NULL) != 0)
		{
			ft_destroy(philos, i - 1);
			return NULL;
		}
		i++;
	}
	return (philos);
}


int	ft_join_routines(t_philo *philos)
{
	int	i;

	i = 0;
	while (i < philos[0].table->table_size)
	{
		pthread_join(philos[i].thread, NULL);
		i++;
	}
	return 0;
}