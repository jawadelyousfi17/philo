#include "philo.h"



void ft_print(char *message, t_philo philo, int flag)
{
	t_table		*table;
	long long	time;
	static int	var;

	table = philo.table;
	pthread_mutex_lock(&table->print_mutex);
	if (flag == IS_DEAD)
	{
		var = 1;
		printf("%lld %d is dead\n",ft_gettime() - table->start_time, philo.id);
		pthread_mutex_unlock(&table->print_mutex);
		return ;
	}
	if (var)
	{
			pthread_mutex_unlock(&table->print_mutex);
			return ;
	}
	time = ft_gettime() - table->start_time;
	printf("%lld %d is %s\n", time, philo.id, message);
	pthread_mutex_unlock(&table->print_mutex);
	return ;
}

