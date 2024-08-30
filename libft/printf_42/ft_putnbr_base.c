/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr_base.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bszikora <bszikora@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/30 14:44:48 by bszikora          #+#    #+#             */
/*   Updated: 2024/03/29 13:33:12 by bszikora         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	ft_putnbr_base(uintptr_t nbr, char *base)
{
	size_t	base_len;
	int		count;

	count = 0;
	base_len = ft_strlen(base);
	if (nbr >= base_len)
	{
		count += ft_putnbr_base(nbr / base_len, base);
		if (count == -1)
			return (-1);
		count += ft_putchar(base[nbr % base_len]);
		if (count == -1)
			return (-1);
	}
	else
	{
		count += ft_putchar(base[nbr]);
		if (count == -1)
			return (-1);
	}
	return (count);
}
