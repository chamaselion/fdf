/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bszikora <bszikora@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/27 16:27:00 by bszikora          #+#    #+#             */
/*   Updated: 2024/04/15 17:10:52 by bszikora         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

static void	ft_norminettebs(unsigned char *pdst, const unsigned char *psrc,
		ssize_t len)
{
	ssize_t	i;

	i = 0;
	while (i < len)
	{
		pdst[i] = psrc[i];
		i++;
	}
}

void	*ft_memmove(void *dst, const void *src, ssize_t len)
{
	unsigned char	*pdst;
	unsigned char	*psrc;
	ssize_t			i;

	pdst = (unsigned char *)dst;
	psrc = (unsigned char *)src;
	i = 0;
	if (pdst == psrc)
		return (dst);
	if (pdst < psrc)
	{
		ft_norminettebs(pdst, psrc, len);
	}
	else
	{
		i = len;
		while (i > 0)
		{
			pdst[i - 1] = psrc[i - 1];
			i--;
		}
	}
	return (dst);
}

char	*ft_strchr(const char *s, int c)
{
	char	ch;
	int		i;

	ch = (char)c;
	i = 0;
	while (s[i] != '\0')
	{
		if (s[i] == ch)
		{
			return ((char *)&s[i]);
		}
		i++;
	}
	if (ch == '\0')
	{
		return ((char *)&s[i]);
	}
	return (0);
}

int	ft_strlen(const char *str)
{
	int	c;

	c = 0;
	while (str[c] != '\0')
	{
		c++;
	}
	return (c);
}

char	*ft_strjoin(char *s1, char *s2)
{
	char	*r;
	size_t	c;
	size_t	c1;

	c = 0;
	c1 = 0;
	if (!s1 || !s2)
		return (free(s1), NULL);
	r = (char *)malloc(sizeof(char) * (ft_strlen(s1) + ft_strlen(s2) + 1));
	if (!r)
		return (free(s1), NULL);
	while (s1[c] != '\0')
	{
		r[c] = s1[c];
		c++;
	}
	while (s2[c1] != '\0')
	{
		r[c + c1] = s2[c1];
		c1++;
	}
	r[c + c1] = '\0';
	free(s1);
	return (r);
}