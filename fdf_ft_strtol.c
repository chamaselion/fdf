/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf_ft_strtol.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bszikora <bszikora@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/31 14:32:03 by bszikora          #+#    #+#             */
/*   Updated: 2024/08/31 14:40:22 by bszikora         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

static long	handle_overflow(int sign)
{
	if (sign == 1)
		return (LONG_MAX);
	else
		return (LONG_MIN);
}

static long	convert_str_to_long(const char **s, int *overflow)
{
	long	result;
	int		digit;

	result = 0;
	while (**s)
	{
		if (ft_isdigit(**s))
			digit = **s - '0';
		else if (**s >= 'a' && **s <= 'f')
			digit = **s - 'a' + 10;
		else if (**s >= 'A' && **s <= 'F')
			digit = **s - 'A' + 10;
		else
			break ;
		if (result > (LONG_MAX - digit) / 16)
		{
			*overflow = 1;
			break ;
		}
		result = result * 16 + digit;
		(*s)++;
	}
	return (result);
}

static void	skip_initial_chars(const char **s, int *sign)
{
	while (ft_isspace(**s))
		(*s)++;
	if (**s == '-')
	{
		*sign = -1;
		(*s)++;
	}
	else if (**s == '+')
	{
		*sign = 1;
		(*s)++;
	}
	if (**s == '0' && ((*s)[1] == 'x' || (*s)[1] == 'X'))
		*s += 2;
}

long	ft_strtol(const char *str, char **endptr)
{
	const char	*s = str;
	long		result;
	int			sign;
	int			overflow;

	sign = 1;
	overflow = 0;
	skip_initial_chars(&s, &sign);
	result = convert_str_to_long(&s, &overflow);
	if (overflow)
		result = handle_overflow(sign);
	else
		result *= sign;
	if (endptr)
		*endptr = (char *)s;
	return (result);
}
