/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bszikora <bszikora@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/26 17:19:24 by bszikora          #+#    #+#             */
/*   Updated: 2024/08/28 17:56:17 by bszikora         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_H
# define FT_PRINTF_H

# include <limits.h>
# include <stdarg.h>
# include <stdint.h>
# include <stdio.h>
# include <string.h>
# include <unistd.h>
# include "../libft.h"

typedef struct t_data_t
{
	va_list			al;
	size_t			c;
	void			*temp;
	int				temp1;
	int				temp2;
	int				rv;
	int				error;
	char			tmp;
	unsigned int	nbrb;
	int				counter;
}					t_data_t;

void				handle_hex(t_data_t *data, char *base);
void				handle_percent(t_data_t *data);
void				handle_char(t_data_t *data);
void				handle_string(t_data_t *data);
void				handle_pointer(t_data_t *data);
void				handle_int(t_data_t *data);
void				handle_uint(t_data_t *data);
int					ft_putnbr_base(unsigned long int nbr, char *base);
int					ft_putnbr(int nb);
int					ft_putstr(char *str);
int					ft_putchar(char c);
int					ft_printf(const char *f, ...);

#endif