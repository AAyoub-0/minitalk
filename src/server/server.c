/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aboumall <aboumall@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/11 18:07:52 by aboumall          #+#    #+#             */
/*   Updated: 2025/02/12 15:22:12 by aboumall         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minitalk.h"

static t_server	g_server;

void	ft_init_server(void)
{
	g_server.c = 0;
	g_server.eom = false;
	g_server.msg = NULL;
	g_server.msg_b = 0;
	g_server.len_b = 0;
	g_server.msg_len = 0;
	g_server.len = 0;
}

void	ft_read_len(int sig, int s_pid)
{
	g_server.len = (g_server.len << 1) | (sig == SIGUSR1);
	g_server.len_b++;
	kill(s_pid, SIGUSR1);
}

void	ft_read_msg(int sig, int s_pid)
{
	if (!g_server.msg)
	{
		g_server.msg = ft_calloc(g_server.len, sizeof(char));
		if (!(g_server.msg))
			exit(EXIT_FAILURE);
	}
	g_server.c = (g_server.c << 1) | (sig == SIGUSR1);
	if (g_server.msg_b < 8)
		g_server.msg_b++;
	if (g_server.msg_b == 8)
	{
		g_server.msg[g_server.msg_len] = g_server.c;
		g_server.msg_len++;
		g_server.msg_b = 0;
		g_server.c = 0;
		if (g_server.c == '\0' && g_server.msg_len > g_server.len)
			g_server.eom = true;
	}
	kill(s_pid, SIGUSR1);
}

void	ft_handle_sigusr(int sig, siginfo_t *info, void *context)
{
	int	s_pid;

	(void)context;
	s_pid = info->si_pid;
	if (g_server.len_b < 64)
		ft_read_len(sig, s_pid);
	else
		ft_read_msg(sig, s_pid);
	if (g_server.eom)
	{
		ft_printf("message received : %s\n", g_server.msg);
		free(g_server.msg);
		ft_init_server();
	}
}

int	main(void)
{
	struct sigaction	act;

	ft_init_server();
	ft_printf("server PID: %d\n", getpid());
	act.sa_sigaction = ft_handle_sigusr;
	act.sa_flags = SA_SIGINFO;
	sigaction(SIGUSR1, &act, NULL);
	sigaction(SIGUSR2, &act, NULL);
	while (true)
		pause();
	return (EXIT_SUCCESS);
}
