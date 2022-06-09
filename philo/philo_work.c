/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_work.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cdoria <cdoria@student.21-school.ru>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/20 18:25:03 by cdoria            #+#    #+#             */
/*   Updated: 2022/06/08 21:35:35 by cdoria           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	message(t_philo *philo, const char *msg)
{
	pthread_mutex_lock(&philo->info->message);
	printf("%u %d %s", get_time() - philo->info->time, philo->id + 1, msg);
	pthread_mutex_unlock(&philo->info->message);
}

void	eating(t_philo *philo)
{
	pthread_mutex_lock(philo->left_fork);
	message(philo, "philo is taking left fork\n");
	pthread_mutex_lock(philo->right_fork);
	message(philo, "philo is taking right fork\n");
	message(philo, "philo is eating\n");
	pthread_mutex_lock(&philo->info->message);
	philo->last_eat = get_time();
	philo->must_eat--;
	if (philo->must_eat == 0)
		philo->info->full_counter--;
	pthread_mutex_unlock(&philo->info->message);
	ft_usleep(philo->info->time_to_eat);
	pthread_mutex_unlock(philo->left_fork);
	pthread_mutex_unlock(philo->right_fork);
}

void	sleeping(t_philo *philo)
{
	message(philo, "philo is sleeping\n");
	ft_usleep(philo->info->time_to_sleep);
}

void	think(t_philo *philo)
{
	message(philo, "philo thinks\n");
}

void	*philo_work(void *args)
{
	t_philo	*philo;

	philo = (t_philo *)args;
	while (philo->alive && philo->must_eat)
	{
		eating(philo);
		sleeping(philo);
		think(philo);
	}
	return (NULL);
}
