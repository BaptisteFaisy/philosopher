/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   def.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bfaisy <bfaisy@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/15 13:56:38 by bfaisy            #+#    #+#             */
/*   Updated: 2023/12/18 21:49:06 by bfaisy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef DEF_H
# define DEF_H

# include <unistd.h>
# include <pthread.h>
# include <stdio.h>
# include <stdlib.h>
# include <sys/time.h>

typedef struct s_list
{
	pthread_t		t;
	struct s_list	*next;
	struct s_list	*previous;
	pthread_mutex_t	mutex;
	pthread_mutex_t	globalmutex;
	int				id;
	int				time_to_die;
	int				time_to_eat;
	int				time_to_sleep;
	int				number_time_eat;
	long			start;
	int				wait;
	int				*died;
	int				i;
}	t_list;

void	freelist_and_mutex(t_list *head);
void	ft_putstr(char *str);
long	ft_atoi(const char *str);
void	createnode_and_link_and_execute(t_list *cur, t_list *head,
			int i, char **av);
void	freelist(t_list *head);
t_list	*create_head(char **av, pthread_mutex_t globalmutex, int ac);
void	*execute(void *cur);
void	end(t_list *head, char **av, int nbr);
int		end_thread(struct timeval tv, long start, t_list *cur, long end);
void	endv2(t_list *cur, struct timeval time);
long	startv2(t_list *cur, struct timeval time, struct timeval tv,
			long start);

#endif
