/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aboumall <aboumall@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/14 18:10:39 by aboumall          #+#    #+#             */
/*   Updated: 2025/01/15 13:39:12 by aboumall         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../libft.h"

void	ft_putnbr_fd(int n, int fd)
{
	if (n == -2147483648)
	{
		ft_putstr_fd("-2147483648", fd);
		return ;
	}
	if (n < 0)
	{
		ft_putchar_fd('-', fd);
		n = -n;
	}
	if (n < 10)
	{
		ft_putchar_fd(n + '0', fd);
		return ;
	}
	ft_putnbr_fd(n / 10, fd);
	ft_putnbr_fd(n % 10, fd);
}

void	ft_print_array_int(int *array, int size)
{
	int	i;

	if (size == 0)
	{
		ft_printf("Array[%p] { NULL }\n", array);
		return ;
	}
	i = 0;
	ft_printf("Array[%p] { ", array);
	while (i < size)
	{
		ft_printf("%d", array[i]);
		if (i < size - 1)
			ft_printf(", ");
		i++;
	}
	ft_printf(" }\n");
}
