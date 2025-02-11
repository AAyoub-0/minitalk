/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.server.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aboumall <aboumall@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/19 17:15:38 by aayoub            #+#    #+#             */
/*   Updated: 2025/02/11 17:40:12 by aboumall         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minitalk.h"

static	t_server	server;

void	ft_init_server(void)
{
	server.c = 0;
	server.eom = false;
	server.msg = NULL;
	server.msg_b = 0;
	server.len_b = 0;
	server.msg_len = 0;
	server.len = 0;
}

void	ft_read_len(int sig, int s_pid)
{	
	server.len = (server.len << 1) | (sig == SIGUSR1);
	server.len_b++;
	kill(s_pid, SIGUSR1);
}

void	ft_read_msg(int sig, int s_pid)
{	
	if (!server.msg)
	{
		server.msg = ft_calloc(server.len, sizeof(char));
		if (!server.msg)
		{
			ft_putstr_fd("Error\n", 2);
			exit (EXIT_FAILURE);
		}
	}
	server.c = (server.c << 1) | (sig == SIGUSR1);
	if (server.msg_b < 8)
		server.msg_b++;
	if (server.msg_b == 8)
	{
		server.msg[server.msg_len] = server.c;
		server.msg_len++;
		server.msg_b = 0;
		server.c = 0;
		if (server.c == '\0' && server.msg_len > server.len)
			server.eom = true;
	}
	kill(s_pid, SIGUSR1);
}

void    ft_handle_sigusr(int sig, siginfo_t *info, void *context)
{
	int s_pid;

	(void)context;
	s_pid = info->si_pid;
	if (server.len_b < 64)
		ft_read_len(sig, s_pid);
	else
		ft_read_msg(sig, s_pid);
	if (server.eom)
	{
		ft_printf("message received : %s\n", server.msg);
		free(server.msg);
		ft_init_server();
	}
}

int main(void)
{
	struct sigaction	act;

	ft_init_server();
	ft_printf("Server PID: %d\n", getpid());
	act.sa_sigaction = ft_handle_sigusr;
	act.sa_flags = SA_SIGINFO;
	sigaction(SIGUSR1, &act, NULL);
	sigaction(SIGUSR2, &act, NULL);
	while (true)
		pause();
	return (EXIT_SUCCESS);
}
