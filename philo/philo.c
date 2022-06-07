/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cdoria <cdoria@student.21-school.ru>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/12 13:18:59 by cdoria            #+#    #+#             */
/*   Updated: 2022/05/31 20:43:58 by cdoria           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	clean_all(t_info *info)
{
	int	i;

	i = 0;
	usleep(100);
	pthread_mutex_destroy(&info->message);
	while (i < info->number_of_philosophers)
	{
		info->philo[i].alive = 0;
		if (&info->forks[i])
			pthread_mutex_destroy(&info->forks[i]);
		i++;
	}
	if (info->philo)
		free (info->philo);
	if (info->forks)
		free (info->forks);
	if (info->threads)
		free (info->threads);
}

int	main(int argc, char **argv)
{
	t_info	info;

	if (!check_valid(argc, argv))
	{
		printf("error\n");
		return (0);
	}
	if (!init(&info, argc, argv) || !philo_start(&info))
		printf("error\n");
	clean_all(&info);
	return (1);
}
