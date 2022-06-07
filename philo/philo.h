/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cdoria <cdoria@student.21-school.ru>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/12 15:15:50 by cdoria            #+#    #+#             */
/*   Updated: 2022/05/31 19:26:25 by cdoria           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <pthread.h>
# include <stdio.h>
# include <stdlib.h>
# include <limits.h>
# include <sys/time.h>

# include <unistd.h>

typedef struct s_philo
{
	struct s_info	*info;
	int				id;
	int				alive;
	int				must_eat;
	unsigned int	last_eat;
	pthread_mutex_t	*left_fork;
	pthread_mutex_t	*right_fork;
}					t_philo;

typedef struct s_info
{
	unsigned int	time;
	pthread_t		*threads;
	t_philo			*philo;
	pthread_mutex_t	message;
	int				full_counter;
	pthread_mutex_t	*forks;
	int				number_of_philosophers;
	int				time_to_die;
	int				time_to_eat;
	int				time_to_sleep;
}					t_info;

int				check_valid(int argc, char **argv);
int				ft_atoi(const char *str);
int				init(t_info *info, int argc, char **argv);
int				philo_start(t_info *info);
void			*philo_work(void *args);
void			ft_usleep(int ms);
unsigned int	get_time(void);
void			message(t_philo *philo, const char *msg);

#endif