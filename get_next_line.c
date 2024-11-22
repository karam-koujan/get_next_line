/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kkoujan <kkoujan@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/20 12:24:48 by kkoujan           #+#    #+#             */
/*   Updated: 2024/11/22 23:33:15 by kkoujan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

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

ssize_t	read_line(int fd, char **str)
{
	char	*buff;
	ssize_t	read_size;
	char	*tmp;

	buff = malloc((BUFFER_SIZE + 1) * sizeof(char));
	if (!buff)
		return (free(*str), *str = NULL, -1);
	read_size = read(fd, buff, BUFFER_SIZE);
	if (read_size <= 0)
		return (free(buff), read_size);
	buff[read_size] = '\0';
	tmp = ft_strjoin(*str, buff);
	if (!tmp)
		return (free(*str), free(buff), *str = NULL, -1);
	free(*str);
	free(buff);
	*str = tmp;
	return (read_size);
}

char	*remove_overflow(char	*str)
{
	int		i;
	char	*res;

	i = 0;
	while (str[i] && str[i] != '\n')
		i++;
	if (!str[i])
		return (ft_strdup(str));
	if (str[i] == '\n')
		i++;
	res = malloc((i + 1) * sizeof(char));
	if (!res)
		return (NULL);
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
	if (!str[i])
		return (free(str), NULL);
	if (str[i] == '\n')
		i++;
	res = ft_strdup(str + i);
	if (!res)
		return (free(str), NULL);
	free(str);
	return (res);
}

char	*get_next_line(int fd)
{
	static char	*str;
	char		*res;
	ssize_t		read_size;

	if (fd < 0 || BUFFER_SIZE <= 0 || BUFFER_SIZE >= INT_MAX \
	|| read(fd, NULL, 0) < 0)
		return (free(str), str = NULL, NULL);
	while (!ft_strchr(str, '\n'))
	{
		read_size = read_line(fd, &str);
		if (read_size < 0)
			return (free(str), str = NULL, NULL);
		if (read_size == 0)
			break ;
	}
	if (!str || !*str)
		return (free(str), str = NULL, NULL);
	res = remove_overflow(str);
	if (!res)
		return (free(str), str = NULL, NULL);
	str = start_next_line(str);
	return (res);
}
