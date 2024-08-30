/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bszikora <bszikora@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/26 17:39:15 by bszikora          #+#    #+#             */
/*   Updated: 2024/04/04 16:17:17 by bszikora         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	edgecase(int nb)
{
	if (nb == INT_MIN)
	{
		if (write(1, "-2147483648", 11) == -1)
			return (-1);
		return (11);
	}
	return (0);
}

int	ft_putnbr(int nb)
{
	int	counter_ptnbr;
	int	res_putnbr;

	counter_ptnbr = 0;
	res_putnbr = edgecase(nb);
	if (res_putnbr == 11)
		return (11);
	if (res_putnbr == -1)
		return (-1);
	if (nb < 0)
	{
		counter_ptnbr += ft_putchar('-');
		nb = -nb;
		if (counter_ptnbr == -1)
			return (-1);
	}
	if (nb >= 10)
	{
		res_putnbr = ft_putnbr(nb / 10);
		if (res_putnbr == -1)
			return (-1);
	}
	res_putnbr += ft_putchar(nb % 10 + '0');
	return ((counter_ptnbr += res_putnbr));
}
