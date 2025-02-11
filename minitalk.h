/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minitalk.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aboumall <aboumall@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/19 17:07:53 by aayoub            #+#    #+#             */
/*   Updated: 2025/02/11 17:31:07 by aboumall         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINITALK_H
# define MINITALK_H

# include "libft/libft.h"
# include <signal.h>
# include <stdio.h>

typedef struct s_server
{
	char	c;
	t_bool	eom;
	char	*msg;
	int		len_b;
	int		msg_b;
	size_t	msg_len;
	size_t	len;
}			t_server;

#endif