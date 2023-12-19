/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   died.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bfaisy <bfaisy@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/19 12:00:27 by bfaisy            #+#    #+#             */
/*   Updated: 2023/12/19 12:39:48 by bfaisy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../def.h"

int	check_if_died(t_list *cur, struct timeval time,
		struct timeval tv, long start)
{
	long	end;

	gettimeofday(&tv, NULL);
	end = (tv.tv_sec * 1000000 + tv.tv_usec);
	if ((end - start) > cur->time_to_die * 1000)
	{
		gettimeofday(&time, NULL);
		if (!*cur->died)
			printf("time : %ld, %d died\n", ((time.tv_sec * 1000
						+ time.tv_usec / 1000) - cur->start), cur->id);
		*(cur->died) = 1;
		return (1);
	}
	return (0);
}

int	sleep_sleep(t_list *cur, struct timeval time, struct timeval tv, long start)
{
	int	i;

	i = 0;
	while (i * 10 != cur->time_to_sleep)
	{
		if (check_if_died(cur, time, tv, start) == 1)
			return (1);
		usleep(1000 * 10);
		i++;
	}
	return (0);
}
