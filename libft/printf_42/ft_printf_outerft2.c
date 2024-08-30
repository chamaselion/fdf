/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_outerft2.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bszikora <bszikora@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/26 17:35:25 by bszikora          #+#    #+#             */
/*   Updated: 2024/03/27 15:37:07 by bszikora         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void	handle_hex(t_data_t *data, char *base)
{
	unsigned int	temp;

	temp = va_arg(data->al, unsigned int);
	data->rv += ft_putnbr_base(temp, base);
}

void	handle_percent(t_data_t *data)
{
	data->rv += ft_putchar('%');
}
