#include <stdlib.h>
#include <stdio.h>
#include <pthread.h>
#include <unistd.h>
#include <sys/time.h>
#include <string.h>

#define IS_DEAD 1
#define IS_ALIVE 2

typedef struct s_table
{
	int is_all_eatean;
	int is_dead;
	int table_size;
	long time_to_eat;
	long time_to_sleep;
	long time_to_die;
	long number_of_meals;
	long long start_time;
	int	*full_check;
	pthread_mutex_t death_mutex;
	pthread_mutex_t print_mutex;
	pthread_mutex_t full_mutex;
} t_table;

typedef struct s_philo 
{
	int id;
	int eat_count;
	long long last_eat_time;
	int is_full;
	pthread_t thread;
	pthread_mutex_t *left_fork;
	pthread_mutex_t *right_fork;
	pthread_mutex_t meal_mutex;
	t_table	*table;
} t_philo;


t_table			*ft_init_table(int ac, char **av);
t_philo			*ft_init_philos(t_table *table, pthread_mutex_t *forks, void *(*ft_routine)(void *));
pthread_mutex_t	*ft_init_forks(t_table *table);
void			*ft_routine(void *arg);
void			ft_print(char *message, t_philo philo, int flag);
void			ft_usleep(long long time, t_table *table);
void			*ft_monitor(t_philo *philos);
int				ft_join_routines(t_philo *philos);
void			*cheack_death(t_table *table);

void			ft_destroy_table(t_table *table);
void			ft_destroy(t_philo *philos, int index);
void			ft_destroy_forks(pthread_mutex_t *forks, int index);

long long		ft_gettime(void);
long			ft_atol(char *s, int *err);