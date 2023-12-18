/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bfaisy <bfaisy@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/16 11:29:24 by bfaisy            #+#    #+#             */
/*   Updated: 2023/12/18 21:46:16 by bfaisy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../def.h"

void	*execute(void *arg)
{
	t_list			*cur;
	struct timeval	tv;
	struct timeval	time;
	long			start;

	cur = (t_list *)arg;
	cur->i = 0;
	pthread_mutex_lock(&(cur->globalmutex));
	pthread_mutex_unlock(&(cur->globalmutex));
	if (cur->wait == 0)
		usleep(cur->time_to_eat * 1000);
	time.tv_sec = 0;
	gettimeofday(&tv, NULL);
	start = (tv.tv_sec * 1000000 + tv.tv_usec);
	while (!*cur->died && cur->i != cur->number_time_eat)
	{
		gettimeofday(&tv, NULL);
		start = (tv.tv_sec * 1000000 + tv.tv_usec);
		if (startv2(cur, time, tv, start) == -1)
			return (NULL);
		cur->i++;
	}
	return (NULL);
}

long	ft_atoi(const char *str)
{
	long	i;
	long	number;
	int		sign;

	i = 0;
	number = 0;
	sign = 1;
	while (str[i] && (str[i] == 32 || (str[i] >= 9 && str[i] <= 13)))
		i++;
	if (str[i] == '-' || str[i] == '+')
	{
		if (str[i] == '-')
			sign = -1;
		i++;
	}
	while (str[i] >= '0' && str[i] <= '9')
	{
		number = (number * 10) + (str[i] - '0');
		i++;
	}
	return (number * sign);
}

void	endv2(t_list *cur, struct timeval time)
{
	if (!*cur->died)
		printf("time : %ld, %d is eating \n", (time.tv_sec * 1000 + time.tv_usec
				/ 1000) - cur->start, cur->id);
	usleep(cur->time_to_eat * 1000);
	pthread_mutex_unlock(&(cur->mutex));
	pthread_mutex_unlock(&(cur->next->mutex));
	gettimeofday(&time, NULL);
	if (!*cur->died)
		printf("time : %ld, %d is sleeping\n",
			(time.tv_sec * 1000 + time.tv_usec / 1000) - cur->start, cur->id);
	usleep(cur->time_to_sleep * 1000);
	gettimeofday(&time, NULL);
	if (!*cur->died)
		printf("time : %ld, %d is thinking\n",
			((time.tv_sec * 1000 + time.tv_usec / 1000) - cur->start), cur->id);
}

long	startv2(t_list *cur, struct timeval time, struct timeval tv, long start)
{
	long				end;

	pthread_mutex_lock(&(cur->mutex));
	gettimeofday(&time, NULL);
	if (!*cur->died)
		printf("time : %ld, %d has taken a fork\n", ((time.tv_sec
					* 1000 + time.tv_usec / 1000) - cur->start), cur->id);
	pthread_mutex_lock(&(cur->next->mutex));
	gettimeofday(&tv, NULL);
	end = (tv.tv_sec * 1000000 + tv.tv_usec);
	if ((end - start) > cur->time_to_die * 10)
	{
		gettimeofday(&time, NULL);
		if (!*cur->died)
			printf("time : %ld, %d died\n", ((time.tv_sec * 1000
						+ time.tv_usec / 1000) - cur->start), cur->id);
		*(cur->died) = 1;
		return (-1);
	}
	endv2(cur, time);
	return (0);
}
