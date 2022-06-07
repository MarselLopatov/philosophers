/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_start.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cdoria <cdoria@student.21-school.ru>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/20 14:23:29 by cdoria            #+#    #+#             */
/*   Updated: 2022/06/07 15:56:09 by cdoria           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	check_full(t_info *info)
{
	if (info->full_counter == 0)
	{
		printf("philo are full\n");
		return (0);
	}
	return (1);
}

int	spectate(t_info *info)
{
	int	i;

	while (1)
	{
		i = 0;
		while (i < info->number_of_philosophers)
		{
			pthread_mutex_lock(&info->message);
			if (!check_full(info))
				return (1);
			if ((unsigned int)info->time_to_die
				<= get_time() - info->philo[i].last_eat)
			{
				pthread_mutex_unlock(&info->message);
				info->philo->alive = 0;
				message(&info->philo[i], "philo is dead\n");
				pthread_mutex_lock(&info->message);
				return (1);
			}
			pthread_mutex_unlock(&info->message);
			i++;
		}
	}
	return (1);
}

int	philo_start(t_info *info)
{
	int	i;

	i = 0;
	while (i < info->number_of_philosophers)
	{
		if (pthread_create(&info->threads[i], NULL, \
			philo_work, &info->philo[i]))
			return (0);
		if (pthread_detach(info->threads[i]))
			return (0);
		usleep(100);
		i++;
	}
	spectate(info);
	return (1);
}
