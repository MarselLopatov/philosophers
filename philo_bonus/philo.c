/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cdoria <cdoria@student.21-school.ru>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/28 19:40:05 by cdoria            #+#    #+#             */
/*   Updated: 2022/06/07 20:34:36 by cdoria           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	cleaner(t_info *info)
{
	int	i;

	i = 0;
	while (i < info->number_of_philosophers)
	{
		kill(info->philo[i].pid, 9);
		i++;
	}
	sem_close(info->forks);
	sem_unlink("fork");
	sem_close(info->message);
	sem_unlink("message");
	sem_close(info->death);
	sem_unlink("death");
}

int	main(int argc, char **argv)
{
	t_info	info;

	if (argc != 5 && argc != 6)
	{
		printf("valid error\n");
		exit (1);
	}	
	check_valid(argc, argv);
	init(&info, argc, argv);
	philo_start(&info);
	cleaner(&info);
	return (1);
}
