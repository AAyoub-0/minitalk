/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aboumall <aboumall@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/14 14:14:05 by aboumall          #+#    #+#             */
/*   Updated: 2025/01/15 13:15:57 by aboumall         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../libft.h"

static size_t	int_len(int n)
{
	size_t	size;

	size = 0;
	if (n == 0)
		return (1);
	if (n < 0)
	{
		n = -n;
		size++;
	}
	while (n > 0)
	{
		n = n / 10;
		size++;
	}
	return (size);
}

static char	*convert_int(char *res, int n, int is_neg)
{
	int		r;
	int		i;
	size_t	size;

	r = 0;
	size = int_len(n) + is_neg;
	i = size - is_neg;
	if (n < 10 && n >= 0)
	{
		res[0 + is_neg] = (n + '0');
		res[1 + is_neg] = '\0';
		return (res);
	}
	while (i > 0)
	{
		r = n % 10;
		n = n / 10;
		res[i - !is_neg] = (r + '0');
		i--;
	}
	res[size] = '\0';
	return (res);
}

char	*ft_itoa(int n)
{
	size_t	size;
	char	*res;
	int		is_neg;

	if (n == -2147483648)
		return (ft_strdup("-2147483648"));
	is_neg = 0;
	size = int_len(n);
	res = (char *)malloc((size + 1) * sizeof(char));
	if (!res)
		return (NULL);
	if (n < 0)
	{
		res[0] = '-';
		is_neg = 1;
		n = -n;
	}
	res = convert_int(res, n, is_neg);
	return (res);
}
