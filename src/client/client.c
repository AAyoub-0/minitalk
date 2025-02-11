/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aboumall <aboumall@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/19 17:15:42 by aayoub            #+#    #+#             */
/*   Updated: 2025/02/11 18:10:15 by aboumall         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minitalk.h"

volatile sig_atomic_t	g_ack_received = 0;

void	handle_action(int sig)
{
	(void)sig;
	g_ack_received = 1;
}

void	ft_send_len(int pid, size_t len)
{
	int		i;
	size_t	mask;
	char	c;

	i = 0;
	mask = (size_t)1 << (sizeof(size_t) * 8 - 1);
	while (i < sizeof(size_t) * 8)
	{
		g_ack_received = 0;
		if (len & mask)
			kill(pid, SIGUSR1);
		else
			kill(pid, SIGUSR2);
		mask >>= 1;
		i++;
		while (!g_ack_received)
			pause();
	}
}

void	ft_send_msg(int pid, char *msg)
{
	int		i;
	char	c;

	while (*msg)
	{
		i = 7;
		c = *msg;
		while (i >= 0)
		{
			g_ack_received = 0;
			if (c & (1 << i))
				kill(pid, SIGUSR1);
			else
				kill(pid, SIGUSR2);
			i--;
			while (!g_ack_received)
				pause();
		}
		msg++;
	}
}

void	ft_send(int pid, char *msg)
{
	size_t	len;
	int		i;

	len = ft_strlen(msg);
	if (len == 0)
		return ;
	ft_send_len(pid, len);
	ft_send_msg(pid, msg);
	i = 7;
	while (i >= 0)
	{
		g_ack_received = 0;
		kill(pid, SIGUSR2);
		i--;
		while (!g_ack_received)
			pause();
	}
}

int	main(int ac, char **av)
{
	struct sigaction	sa;

	if (ac != 3)
	{
		ft_printf("Usage: %s <server_pid> <message>\n", av[0]);
		return (EXIT_FAILURE);
	}
	sa.sa_handler = handle_action;
	sa.sa_flags = 0;
	sigaction(SIGUSR1, &sa, NULL);
	ft_printf("Sending message: %s\n", av[2]);
	ft_send(ft_atoi(av[1]), av[2]);
	return (EXIT_SUCCESS);
}
