/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bfaisy <bfaisy@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/15 14:42:08 by bfaisy            #+#    #+#             */
/*   Updated: 2023/12/18 21:44:16 by bfaisy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../def.h"

int	main(int ac, char **av)
{
	t_list			*head;
	pthread_mutex_t	globalmutex;
	int				nbr;

	if (ac != 5 && ac != 6)
		return (0);
	nbr = ft_atoi(av[1]);
	if (nbr == 0 || nbr == 1)
		return (0);
	if (pthread_mutex_init(&globalmutex, NULL) != 0)
		return (1);
	head = create_head(av, globalmutex, ac);
	if (!head)
	{
		pthread_mutex_destroy(&globalmutex);
		return (0);
	}
	if (head->time_to_die == 0 || head->time_to_eat == 0
		|| head->time_to_sleep == 0 || head->number_time_eat == 0)
	{
		free(head);
		return (free(head->died), 0);
	}
	pthread_mutex_lock(&globalmutex);
	return (end(head, av, nbr), 0);
}

void	createnode_and_link_and_execute(t_list *cur, t_list *head, int i,
	char **av)
{
	t_list	*next;

	next = malloc(sizeof(t_list));
	if (!next)
		freelist_and_mutex(head);
	next->id = i;
	if (pthread_mutex_init(&(next->mutex), NULL) != 0)
		return ;
	next->globalmutex = head->globalmutex;
	next->time_to_die = head->time_to_die;
	next->died = head->died;
	next->time_to_eat = head->time_to_eat;
	next->time_to_sleep = head->time_to_sleep;
	next->number_time_eat = head->number_time_eat;
	cur->next = next;
	next->previous = cur;
	next->next = head;
	next->start = head->start;
	if (next->previous->wait == 0)
		next->wait = 1;
	else
		next->wait = 0;
	pthread_create(&next->t, NULL, execute, next);
	if (i == ft_atoi(av[1]) - 1)
		pthread_mutex_unlock(&head->globalmutex);
}

t_list	*create_head(char **av, pthread_mutex_t globalmutex, int ac)
{
	t_list			*head;
	struct timeval	tv;

	head = malloc(sizeof(t_list));
	head->died = malloc(sizeof(int));
	if (!head || !head->died)
		return (NULL);
	head->wait = 0;
	*(head->died) = 0;
	head->globalmutex = globalmutex;
	gettimeofday(&tv, NULL);
	head->start = ((tv.tv_sec * 1000 + tv.tv_usec / 1000));
	head->time_to_die = ft_atoi(av[2]);
	head->time_to_eat = ft_atoi(av[3]);
	head->time_to_sleep = ft_atoi(av[4]);
	if (ac == 6)
		head->number_time_eat = ft_atoi(av[5]);
	else
		head->number_time_eat = -1;
	head->id = -1;
	return (head);
}

void	freelist_and_mutex(t_list *head)
{
	t_list	*cpy;

	cpy = 0;
	head = head->next;
	while (head->id != -1)
	{
		cpy = head;
		head = head->next;
		pthread_mutex_destroy(&(cpy->mutex));
		pthread_join(cpy->t, NULL);
		free(cpy);
	}
	pthread_mutex_destroy(&head->globalmutex);
	free(head->died);
	free(head);
}

void	end(t_list *head, char **av, int nbr)
{
	int			i;
	t_list		*cur;

	i = 0;
	cur = head;
	while (i != nbr)
	{
		createnode_and_link_and_execute(cur, head, i, av);
		cur = cur->next;
		i++;
	}
	i = 0;
	cur = head;
	while (i != nbr)
	{
		freelist_and_mutex(head);
		return ;
	}
}
