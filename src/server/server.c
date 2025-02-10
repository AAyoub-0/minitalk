/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aboumall <aboumall@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/19 17:15:38 by aayoub            #+#    #+#             */
/*   Updated: 2025/02/10 17:38:24 by aboumall         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minitalk.h"

static char mes[1024];

void    handle_sigusr(int sig, siginfo_t *info, void *context)
{
	static char	c = 0;
	static int	i = 0;
	static int	m_i = 0;
	static int	len_b = 0;
	static size_t	len;
	int sender_pid;

	(void)context;
	sender_pid = info->si_pid;
	len = (len << 1) | (sig == SIGUSR1);
	printf("%d", (sig == SIGUSR1));
	if (len_b % 8 == 7)
		printf(" ");
	len_b++;
	if (len_b == 64)
	{
		printf("len : %zu\n", len);
		len_b = 0;
		len = 0;
	}
	kill(sender_pid, SIGUSR1);
}

int main(void)
{
	struct sigaction	act;

	ft_printf("Server PID: %d\n", getpid());
	act.sa_sigaction = handle_sigusr;
	act.sa_flags = SA_SIGINFO;
	sigaction(SIGUSR1, &act, NULL);
	sigaction(SIGUSR2, &act, NULL);
	while (true)
		pause();

	return (0);
}
