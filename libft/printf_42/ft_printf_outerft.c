/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_outerft.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bszikora <bszikora@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/26 17:18:01 by bszikora          #+#    #+#             */
/*   Updated: 2024/03/29 14:21:37 by bszikora         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void	handle_char(t_data_t *data)
{
	int	result;

	data->tmp = (char)va_arg(data->al, int);
	result = ft_putchar(data->tmp);
	if (result == -1)
		data->rv = -1;
	else
		data->rv++;
}

void	handle_string(t_data_t *data)
{
	char	*str;

	str = va_arg(data->al, char *);
	if (str == NULL)
		str = "(null)";
	data->rv += ft_putstr(str);
}

void	handle_pointer(t_data_t *data)
{
	void	*temp;
	int		result;

	temp = va_arg(data->al, void *);
	if (temp == NULL)
	{
		result = ft_putstr("0x0");
	}
	else
	{
		result = ft_putstr("0x");
		if (result != -1)
		{
			data->rv += result;
			result = ft_putnbr_base((uintptr_t)temp, "0123456789abcdef");
		}
	}
	if (result == -1)
		data->rv = -1;
	else
		data->rv += result;
}

void	handle_int(t_data_t *data)
{
	data->rv += ft_putnbr(va_arg(data->al, int));
}

void	handle_uint(t_data_t *data)
{
	data->nbrb = va_arg(data->al, unsigned int);
	data->rv += ft_putnbr_base(data->nbrb, "0123456789");
}
