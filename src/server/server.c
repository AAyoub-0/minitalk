/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aayoub <aayoub@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/19 17:15:38 by aayoub            #+#    #+#             */
/*   Updated: 2025/01/19 20:57:35 by aayoub           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minitalk.h"

void    handle_sigusr(int sig, siginfo_t *info, void *context)
{
    static char c = 0;
    static int i = 0;

    (void)context;
    c |= (sig == SIGUSR1) << i;
    i++;
    if (i == 8)
    {
        if (c == '\0')
        {
            ft_printf("\n");
            kill(info->si_pid, SIGUSR1);
        }
        else
            ft_printf("%c", c);
        c = 0;
        i = 0;
    }
}

int main(void)
{
    struct sigaction act;
    
    ft_printf("Server PID: %d\n", getpid());
    act.sa_sigaction = handle_sigusr;
    act.sa_flags = SA_SIGINFO;
    sigaction(SIGUSR1, &act, NULL);
    sigaction(SIGUSR2, &act, NULL);
    while (true)
        pause();
    return (0);
}