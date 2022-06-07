/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_work.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cdoria <cdoria@student.21-school.ru>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/30 21:23:02 by cdoria            #+#    #+#             */
/*   Updated: 2022/05/31 20:51:11 by cdoria           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	message(t_philo *philo, const char *msg)
{
	sem_wait(philo->info->message);
	printf("%ld %d %s", get_time() - philo->info->time, philo->id + 1, msg);
	sem_post(philo->info->message);
}

void	eating(t_philo *philo)
{
	sem_wait(philo->info->forks);
	message(philo, "philo is taking left fork\n");
	sem_wait(philo->info->forks);
	message(philo, "philo is taking right fork\n");
	message(philo, "philo is eating\n");
	sem_wait(philo->info->message);
	philo->last_eat = get_time();
	philo->must_eat--;
	sem_post(philo->info->message);
	ft_usleep(philo->info->time_to_eat);
	sem_post(philo->info->forks);
	sem_post(philo->info->forks);
	if (philo->must_eat == 0)
		exit (5);
}

void	sleeping(t_philo *philo)
{
	message(philo, "philos is sleeping\n");
	ft_usleep(philo->info->time_to_sleep);
}

void	think(t_philo *philo)
{
	message(philo, "philo thinks\n");
}

void	philo_work(t_philo *philo)
{
	pthread_t	thread;

	if (pthread_create(&thread, NULL, check_death, philo))
		return ;
	if (pthread_detach(thread))
		return ;
	while (philo->alive && philo->must_eat)
	{
		eating(philo);
		sleeping(philo);
		think(philo);
	}
}
