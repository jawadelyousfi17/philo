#include "philo.h"

long long ft_gettime(void)
{
    struct timeval tv;
    long long time;

    gettimeofday(&tv, NULL);
    time = (tv.tv_sec * 1000) + (tv.tv_usec / 1000);
    return (time);
}

void ft_usleep(long long time, t_table *table)
{
    long long start = ft_gettime();
    while ((ft_gettime() - start) < time)
    {
        if (!cheack_death(table))
            return ;
        usleep(100);
    }
    return;
}