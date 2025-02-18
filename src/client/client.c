/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aboumall <aboumall@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/19 17:15:42 by aayoub            #+#    #+#             */
/*   Updated: 2025/02/18 14:07:14 by aboumall         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minitalk.h"

t_bool	ft_check_args(int ac, char **av)
{
	int	i;

	if (ac != 3)
	{
		ft_printf("Usage: %s <server_pid> <message>\n", av[0]);
		return (false);
	}
	i = 0;
	while (av[1][i])
	{
		if (!ft_isdigit(av[1][i]))
		{
			ft_printf("Error\n<server_pid> must be of type int\n");
			return (false);
		}
		i++;
	}
	return (true);
}

void	ft_send(int pid, char *msg)
{
	size_t	len;

	len = ft_strlen(msg);
	if (len == 0)
		return ;
	ft_send_len(pid, len);
	ft_send_msg(pid, msg);
	ft_send_eom(pid);
}

int	main(int ac, char **av)
{
	struct sigaction	sa;
	int					pid;

	if (!ft_check_args(ac, av))
		return (EXIT_FAILURE);
	pid = ft_atoi(av[1]);
	ft_memset(&sa, 0, sizeof(sa));
	sa.sa_handler = ft_handle_action;
	sa.sa_flags = 0;
	sigemptyset(&sa.sa_mask);
	if (sigaction(SIGUSR1, &sa, NULL) == -1)
	{
		ft_putendl_fd("Error\nsigaction SIGUSR1\n", 2);
		return (EXIT_FAILURE);
	}
	if (!ft_ping_serv(pid))
	{
		ft_printf("Error\nServer not responding\n");
		return (EXIT_FAILURE);
	}
	ft_printf("Sending message: %s\n", av[2]);
	ft_send(pid, av[2]);
	return (EXIT_SUCCESS);
}
