/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aboumall <aboumall@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/19 17:15:38 by aayoub            #+#    #+#             */
/*   Updated: 2025/01/28 19:55:31 by aboumall         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minitalk.h"

#include <stdlib.h>

char    *str_append(char *str, char c)
{
    int size;
    char *new;

    size = ft_strlen(str);
    new = ft_realloc(str, size + 2);
    if (!new)
        return (NULL);
    new[size] = c;
    return (new);
}

static char mes[1024];

void    handle_sigusr(int sig, siginfo_t *info, void *context)
{
    static char c = 0;
    static int i = 0;
    static int m_i = 0;

    (void)context;
    c |= (sig == SIGUSR1) << i;
    i++;
    if (i == 8)
    {
        if (c == '\0')
        {
            ft_printf("%s\n", mes);
            kill(info->si_pid, SIGUSR1);
            m_i = 0;
        }
        else
        {
            mes[m_i++] = c;
            mes[m_i] = '\0';
        }
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

    // char *str;
    // str = ft_strdup("");
    // printf("str: %s\n", str);
    // str = str_append(str, 'H');
    // printf("str: %s\n", str);
    // str = str_append(str, 'e');
    // printf("str: %s\n", str);
    // str = str_append(str, 'l');
    // printf("str: %s\n", str);
    // str = str_append(str, 'l');
    // printf("str: %s\n", str);
    // str = str_append(str, 'o');
    // printf("str: %s\n", str);
    // str = str_append(str, '!');
    // printf("str: %s\n", str);
    // free (str);

    return (0);
}