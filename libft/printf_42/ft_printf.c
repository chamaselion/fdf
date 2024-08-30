/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bszikora <bszikora@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/26 17:16:37 by bszikora          #+#    #+#             */
/*   Updated: 2024/04/04 16:13:38 by bszikora         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void	handle_fs(const char *f, t_data_t *data)
{
	if (f[data->c] == 'c')
		handle_char(data);
	else if (f[data->c] == 's')
		handle_string(data);
	else if (f[data->c] == 'p')
		handle_pointer(data);
	else if (f[data->c] == 'd' || f[data->c] == 'i')
		handle_int(data);
	else if (f[data->c] == 'u')
		handle_uint(data);
	else if (f[data->c] == 'x')
		handle_hex(data, "0123456789abcdef");
	else if (f[data->c] == 'X')
		handle_hex(data, "0123456789ABCDEF");
	else if (f[data->c] == '%')
		handle_percent(data);
}

int	ft_printf(const char *f, ...)
{
	t_data_t	data;

	data.error = 0;
	data.rv = 0;
	data.c = 0;
	va_start(data.al, f);
	while (f[data.c])
	{
		if (f[data.c] == '%')
		{
			data.c++;
			handle_fs(f, &data);
			if (data.rv == -1)
				return (-1);
		}
		else
		{
			data.error = ft_putchar(f[data.c]);
			if (data.error == -1)
				return (-1);
			data.rv++;
		}
		data.c++;
	}
	return (va_end(data.al), data.rv);
}
