/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aboumall <aboumall@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/11 18:07:52 by aboumall          #+#    #+#             */
/*   Updated: 2025/02/18 13:13:58 by aboumall         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minitalk.h"

static t_server	g_s;

void	ft_init_server(void)
{
	g_s.c = 0;
	g_s.eom = false;
	g_s.ping = false;
	g_s.msg = NULL;
	g_s.msg_b = 0;
	g_s.len_b = 0;
	g_s.msg_len = 0;
	g_s.len = 0;
}

void	ft_read_len(int sig, int s_pid)
{
	g_s.len = (g_s.len << 1) | (sig == SIGUSR1);
	g_s.len_b++;
	kill(s_pid, SIGUSR1);
}

void	ft_read_msg(int sig, int s_pid)
{
	if (!g_s.msg)
	{
		g_s.msg = ft_calloc(g_s.len + 1, sizeof(char));
		if (!(g_s.msg))
			exit(EXIT_FAILURE);
	}
	g_s.c = (g_s.c << 1) | (sig == SIGUSR1);
	if (g_s.msg_b < 8)
		g_s.msg_b++;
	if (g_s.msg_b == 8)
	{
		g_s.msg[g_s.msg_len] = g_s.c;
		g_s.msg_len++;
		g_s.msg_b = 0;
		g_s.c = 0;
		if (g_s.c == '\0' && g_s.msg_len > g_s.len)
			g_s.eom = true;
	}
	kill(s_pid, SIGUSR1);
}

void	ft_handle_sigusr(int sig, siginfo_t *info, void *context)
{
	int	s_pid;

	(void)context;
	s_pid = info->si_pid;
	if (!g_s.ping)
	{
		g_s.ping = true;
		kill(s_pid, SIGUSR1);
		return ;
	}
	if (g_s.len_b < 64)
		ft_read_len(sig, s_pid);
	else
		ft_read_msg(sig, s_pid);
	if (g_s.eom)
	{
		ft_printf("message received : %s\n", g_s.msg);
		free(g_s.msg);
		ft_init_server();
	}
}

int	main(void)
{
	struct sigaction	act;

	ft_init_server();
	ft_printf("server PID: %d\n", getpid());
	ft_memset(&act, 0, sizeof(act));
	act.sa_sigaction = ft_handle_sigusr;
	act.sa_flags = SA_SIGINFO;
	sigemptyset(&act.sa_mask);
	sigaction(SIGUSR1, &act, NULL);
	sigaction(SIGUSR2, &act, NULL);
	while (true)
		pause();
	return (EXIT_SUCCESS);
}
