/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aboumall <aboumall@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/12 15:42:52 by aboumall          #+#    #+#             */
/*   Updated: 2025/02/13 13:44:09 by aboumall         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minitalk.h"

volatile sig_atomic_t	g_ack_received = 0;

void	ft_handle_action(int sig)
{
	(void)sig;
	g_ack_received = 1;
}

t_bool	ft_ping_serv(int pid)
{
	g_ack_received = 0;
	kill(pid, SIGUSR2);
	sleep(2);
	if (!g_ack_received)
		return (false);
	return (true);
}

void	ft_send_len(int pid, size_t len)
{
	size_t	i;
	size_t	mask;

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

void	ft_send_eom(int pid)
{
	int		i;

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
