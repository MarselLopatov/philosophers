/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_start.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cdoria <cdoria@student.21-school.ru>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/30 20:56:44 by cdoria            #+#    #+#             */
/*   Updated: 2022/06/07 20:34:28 by cdoria           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	spectate_pid(t_info *info)
{
	int	status;
	int	full;
	int	i;

	i = -1;
	full = 0;
	status = 0;
	while (1)
	{
		waitpid(-1, &status, 0);
		status = status >> 8;
		if (status == 4)
			break ;
		if (status == 5)
			full++;
		if (full == info->number_of_philosophers)
		{
			printf("philo are full\n");
			break ;
		}
	}
}

void	*check_death(void *args)
{
	t_philo	*philo;

	philo = (t_philo *)args;
	while (1)
	{
		if (philo->info->time_to_die <= get_time() - philo->last_eat)
		{
			philo->alive = 0;
			sem_wait(philo->info->death);
			message(philo, "philo is dead\n");
			sem_wait(philo->info->message);
			exit(4);
		}
	}
	return (NULL);
}

void	make_forks(t_info *info)
{
	pid_t	pid;
	int		i;

	i = 0;
	while (i < info->number_of_philosophers)
	{
		pid = fork();
		if (pid == 0)
			philo_work(&info->philo[i]);
		else
			info->philo[i].pid = pid;
		i++;
	}
}

void	philo_start(t_info *info)
{
	make_forks(info);
	spectate_pid(info);
}
