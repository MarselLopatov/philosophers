/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cdoria <cdoria@student.21-school.ru>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/12 15:15:50 by cdoria            #+#    #+#             */
/*   Updated: 2022/05/31 20:40:02 by cdoria           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <pthread.h>
# include <stdio.h>
# include <stdlib.h>
# include <limits.h>
# include <sys/time.h>
# include <semaphore.h>
# include <unistd.h>
# include <signal.h>

typedef struct s_philo
{
	struct s_info	*info;
	int				id;
	int				alive;
	long			last_eat;
	pid_t			pid;
	int				must_eat;
}					t_philo;

typedef struct s_info
{
	long		time;
	t_philo		*philo;
	sem_t		*message;
	sem_t		*death;
	sem_t		*forks;
	int			number_of_philosophers;
	long		time_to_die;
	int			time_to_eat;
	int			time_to_sleep;
}				t_info;

int				check_valid(int argc, char **argv);
int				ft_atoi(const char *str);
long			get_time(void);
void			ft_usleep(int ms);
int				init(t_info *info, int argc, char **argv);
void			philo_start(t_info *info);
void			philo_work(t_philo *philo);
void			*check_death(void *args);
void			message(t_philo *philo, const char *msg);

#endif