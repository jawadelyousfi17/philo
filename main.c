#include "philo.h"

void f()
{
    system("leaks philo");
}

int main(int ac, char **av)
{

    // atexit(f);
    t_table *table;
    t_philo *philos;
    pthread_mutex_t *forks;

    if (ac != 5 && ac != 6)
        return (5);
    table = ft_init_table(ac, av);
    if (!table)
        return 5;
    forks = ft_init_forks(table);
    if (!forks)
     return (ft_destroy_table(table), 4);
    philos = ft_init_philos(table, forks, &ft_routine);
    if (!philos)
        return (3);
    ft_monitor(philos);
    ft_join_routines(philos);
    ft_destroy_forks(forks, philos->table->table_size);
    ft_destroy(philos, philos->table->table_size);
    return 0;
}

