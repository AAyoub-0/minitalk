/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minitalk.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aboumall <aboumall@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/19 17:07:53 by aayoub            #+#    #+#             */
/*   Updated: 2025/02/13 14:03:17 by aboumall         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINITALK_H
# define MINITALK_H

# include "libft/libft.h"
# include <signal.h>

typedef struct s_server
{
	char	c;
	t_bool	eom;
	t_bool	ping;
	char	*msg;
	int		len_b;
	int		msg_b;
	size_t	msg_len;
	size_t	len;
}			t_server;

void		ft_handle_action(int sig);
t_bool		ft_ping_serv(int pid);
void		ft_send_len(int pid, size_t len);
void		ft_send_msg(int pid, char *msg);
void		ft_send_eom(int pid);

#endif