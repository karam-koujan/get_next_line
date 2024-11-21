/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kkoujan <kkoujan@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/20 12:24:48 by kkoujan           #+#    #+#             */
/*   Updated: 2024/11/21 17:00:25 by kkoujan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"
#include <stdio.h>

size_t	ft_strlen(const char *s)
{
	size_t	i;

	i = 0;
	while (s[i])
	{
		i++;
	}
	return (i);
}

char	*read_line(int fd, char *str)
{
	char	buff[BUFFER_SIZE];
	ssize_t	read_size;
	char	*res;

	read_size = read(fd, buff, BUFFER_SIZE - 1);
    if (read_size <= 0)
        return (free(str), NULL);
	buff[read_size] = '\0';
	res = ft_strjoin(str, buff);
	free(str);
	if (!res)
		return (NULL);
	return (res);
}

char	*remove_overflow(char	*str)
{
	int		i;
	char	*res;

	i = 0;
	while (str[i] && str[i] != '\n')
		i++;
	if (str[i] == '\n')
		i++;
	res = malloc((i + 1) * sizeof(char));
	if (!res)
		return (free(str), NULL);
	ft_strlcpy(res, str, i + 1);
	return (res);
}

char	*start_next_line(char	*str)
{
	int		i;
	char	*res;

	i = 0;
	while (str[i] && str[i] != '\n')
		i++;
	if (str[i] == '\n')
		i++;
	res = malloc((ft_strlen(str) - i + 1) * sizeof(char));
	if (!res)
		return (free(str), NULL);
	ft_strlcpy(res, str + i, i - ft_strlen(str) + 1);
	free(str);
	return (res);
}

char	*get_next_line(int fd)
{
	static char	*str;
	char		*res;

	if (fd < 0 || BUFFER_SIZE <= 0 || read(fd, 0, 0) < 0)
		return (NULL);
	if (str == NULL)
		str = ft_strdup("");
	while (str != NULL && !ft_strchr(str, '\n'))
	{
		str = read_line(fd, str);
		if (!str)
			return (NULL);
	}
	if (!str)
		return (NULL);
	res = remove_overflow(str);
	str = start_next_line(str);

	return (res);
}

