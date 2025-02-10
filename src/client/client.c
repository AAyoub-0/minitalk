/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aboumall <aboumall@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/19 17:15:42 by aayoub            #+#    #+#             */
/*   Updated: 2025/02/10 17:25:22 by aboumall         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minitalk.h"

volatile sig_atomic_t ack_received = 0;

void handle_action(int sig)
{
	(void)sig;
	ack_received = 1;
}

void	ft_send_len(int pid, size_t len)
{
	int	i;
	size_t	mask;
	char	c;

	i = 0;
	mask = (size_t)1 << (sizeof(size_t) * 8 - 1);
	printf("len: %zu\n", len);
	while (i < sizeof(size_t) * 8)
	{
		ack_received = 0;
		if (len & mask)
		{
			kill(pid, SIGUSR1);
			printf("1");
		}
		else
		{			
			kill(pid, SIGUSR2);
			printf("0");
		}
		if (i % 8 == 7)
			printf(" ");
		mask >>= 1;
		i++;
		usleep(100);
	}
	printf("\n");
}

void	ft_send_eom(int pid)
{
	int	i;
	char	c;
	
	i = 7;
	c = '\0';
	while (i >= 0)
	{
		kill(pid, SIGUSR2);
		i--;
		usleep(100);
	}
}

void	ft_send_msg(int pid, char *msg)
{
	int	i;
	char	c;

	while (*msg)
	{
		i = 0;
		c = *msg;
		while (i < 8)
		{
			if (c & 1)
				kill(pid, SIGUSR1);
			else
				kill(pid, SIGUSR2);
			c >>= 1;
			i++;
			usleep(100);
		}
		msg++;
	}
}

void    ft_send(int pid, char *msg)
{
	size_t	len;
	struct sigaction sa;

	sa.sa_handler = handle_action;
	sa.sa_flags = 0;
	sigaction(SIGUSR1, &sa, NULL);
	len = ft_strlen(msg);
	if (len == 0)
		return ;
	ft_send_len(pid, len);
	// ft_send_msg(pid, msg);
	// ft_send_eom(pid);
}

int main(int ac, char **av)
{
	if (ac != 3)
	{
		ft_printf("Usage: %s <server_pid> <message>\n", av[0]);
		return (1);
	}
	ft_printf("Sending message: %s\n", av[2]);
	ft_send(ft_atoi(av[1]), av[2]);
	return (0);
}