/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bszikora <bszikora@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/27 16:23:20 by bszikora          #+#    #+#             */
/*   Updated: 2024/08/28 16:52:03 by bszikora         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H
# include <stdlib.h>
# include <unistd.h>
# include "../libft.h"

typedef struct s_gnl
{
	char	*buffer[2];
	char	*newline_pos;
	ssize_t	bytes_read;
	char	*line;
	char	*tmp;
	char	maybe;
}			t_gnl;

char		*ft_strchr(const char *s, int c);
//size_t		ft_strlen(const char *str);
char		*get_next_line(int fd);
//void		*ft_memmove(void *dst, const void *src, ssize_t len);
//char		*ft_strjoin(char *s1, char *s2);

#endif