/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aboumall <aboumall@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/19 17:15:38 by aayoub            #+#    #+#             */
/*   Updated: 2025/02/11 14:59:41 by aboumall         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minitalk.h"

static int	len_b = 0;
static int	msg_b = 0;
static size_t	len;
static char	*msg = NULL;
static size_t	msg_len = 0;
static char	c;
static t_bool eom = false;

void	ft_read_len(int sig, int s_pid)
{	
	len = (len << 1) | (sig == SIGUSR1);
	if (len_b < 64)
		len_b++;
	if (len_b == 64)
	{
		printf("len: %zu\n", len);
		len_b = 0;
		len = 0;
	}
	kill(s_pid, SIGUSR1);
}

void	ft_read_msg(int sig, int s_pid)
{	
	if (!msg)
		msg = ft_calloc(len, sizeof(char));
	c = (c << 1) | (sig == SIGUSR1);
	if (msg_b < 7)
		msg_b++;
	if (msg_b == 7)
	{
		msg[msg_len] = c;
		msg_len++;
		msg_b = 0;
		if (c == '\0')
			eom = true;
	}
	kill(s_pid, SIGUSR1);
}

void    ft_handle_sigusr(int sig, siginfo_t *info, void *context)
{
	int s_pid;

	(void)context;
	s_pid = info->si_pid;
	ft_read_len(sig, s_pid);
}

int main(void)
{
	struct sigaction	act;

	ft_printf("Server PID: %d\n", getpid());
	act.sa_sigaction = ft_handle_sigusr;
	act.sa_flags = SA_SIGINFO;
	sigaction(SIGUSR1, &act, NULL);
	sigaction(SIGUSR2, &act, NULL);
	while (true)
		pause();
	return (EXIT_SUCCESS);
}
