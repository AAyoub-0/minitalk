/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aboumall <aboumall@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/19 17:15:42 by aayoub            #+#    #+#             */
/*   Updated: 2025/01/28 19:43:21 by aboumall         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minitalk.h"

void    send_msg(int pid, char *msg)
{
    int i;
    char c;

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
    i = 7;
    c = '\0';
    while (i >= 0)
    {
        if (c & (1 << i))
            kill(pid, SIGUSR1);
        else
            kill(pid, SIGUSR2);
        i--;
        usleep(100);
    }
}

int main(int ac, char **av)
{
    if (ac != 3)
    {
        ft_printf("Usage: %s <server_pid> <message>\n", av[0]);
        return (1);
    }
    ft_printf("Sending message: %s\n", av[2]);
    send_msg(ft_atoi(av[1]), av[2]);
    return (0);
}