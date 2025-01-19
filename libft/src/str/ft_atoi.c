/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aboumall <aboumall@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/07 15:27:51 by aboumall          #+#    #+#             */
/*   Updated: 2025/01/15 13:15:57 by aboumall         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../libft.h"

static int	is_toolarge(long int result, int n)
{
	if (result > (LONG_MAX - (n - '0')) / 10)
		return (-1);
	if (-result > (LONG_MAX - (n - '0')) / 10)
		return (0);
	return (1);
}

static int	is_valid(int n)
{
	if (n == '-' || n == '+' || !ft_isdigit(n))
		return (0);
	return (1);
}

int	ft_atoi(const char *nptr)
{
	ssize_t	result;
	int		i;
	int		sign;

	i = 0;
	result = 0;
	sign = 1;
	while ((nptr[i] >= 9 && nptr[i] <= 13) || nptr[i] == ' ')
		i++;
	if (nptr[i] == '-' || nptr[i] == '+')
	{
		if (nptr[i] == '-')
			sign *= -1;
		if (!is_valid(nptr[i + 1]))
			return (0);
		i++;
	}
	while (nptr[i] >= '0' && nptr[i] <= '9')
	{
		if (is_toolarge(result, nptr[i]) <= 0)
			return (is_toolarge(result, nptr[i]));
		result = result * 10 + nptr[i] - '0';
		i++;
	}
	return (result * sign);
}

int	ft_atoi_cursor(char *nptr, int *cursor, int *error)
{
	ssize_t	result;
	int		i;
	int		sign;

	i = 0;
	result = 0;
	sign = 1;
	while ((nptr[i] >= 9 && nptr[i] <= 13) || nptr[i] == ' ')
		i++;
    if (nptr[i] == '-')
        sign *= -1;
    i++;
	while (nptr[i] >= '0' && nptr[i] <= '9')
	{
        if (is_toolarge(result, nptr[i]) <= 0)
        {
            (*error) = 1;
			return (0);
        }
		result = result * 10 + nptr[i] - '0';
		i++;
	}
    (*cursor) = (*cursor) + i;
	return (result * sign);
}
