/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kkoujan <kkoujan@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/20 12:25:27 by kkoujan           #+#    #+#             */
/*   Updated: 2024/11/21 14:31:07 by kkoujan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char	*ft_strchr(const char *s, int c)
{
	char	*p;

	p = (char *)s;
	c = (char)c;
	while (*p)
	{
		if (*p == c)
		{
			return (p);
		}
		p++;
	}
	if (*p == c)
	{
		return (p);
	}
	return (0);
}

size_t	ft_strlcpy(char *dst, const char *src, size_t dstsize)
{
	size_t	i;
	size_t	src_len;

	i = 0;
	src_len = ft_strlen(src);
	if (dstsize == 0)
		return (src_len);
	while (i < src_len && i < dstsize - 1)
	{
		dst[i] = src[i];
		i++;
	}
	dst[i] = '\0';
	return (src_len);
}

size_t	ft_strlcat(char *dst, const char *src, size_t dstsize)
{
	size_t	dst_len;
	size_t	src_len;
	size_t	i;

	dst_len = ft_strlen(dst);
	src_len = ft_strlen(src);
	i = dst_len;
	if (dstsize == 0)
	{
		return (src_len);
	}
	if (dst_len >= dstsize)
	{
		return (src_len + dstsize);
	}
	while (i < dst_len + src_len && i < dstsize - 1)
	{
		dst[i] = src[i - dst_len];
		i++;
	}
	dst[i] = '\0';
	return (src_len + dst_len);
}

char	*ft_strdup(const char *s1)
{
	char	*s;

	s = malloc((ft_strlen(s1) + 1) * sizeof(char));
	if (s == NULL)
	{
		return (NULL);
	}
	ft_strlcpy(s, s1, ft_strlen(s1) + 1);
	return (s);
}

char	*ft_strjoin(char const *s1, char const *s2)
{
	char	*s;

	if (s1 == NULL && s2 == NULL)
		return (NULL);
	if (s1 == NULL && s2 != NULL)
		return (ft_strdup(s2));
	if (s1 != NULL && s2 == NULL)
		return (ft_strdup(s1));
	s = (char *)malloc((ft_strlen(s1) + ft_strlen(s2) + 1) * sizeof(char));
	if (s == NULL)
		return (NULL);
	ft_strlcpy(s, s1, ft_strlen(s1) + 1);
	ft_strlcat(s, s2, ft_strlen(s1) + ft_strlen(s2) + 1);
	return (s);
}
