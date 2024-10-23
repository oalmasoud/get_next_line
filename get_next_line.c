/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oalmasou <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/16 23:07:43 by oalmasou          #+#    #+#             */
/*   Updated: 2024/10/16 23:12:42 by oalmasou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char	*ft_get_line(char *rest)
{
	char	*line;
	int		i;

	if (!rest)
		return (NULL);
	i = 0;
	while (rest[i] && rest[i] != '\n')
		i++;
	line = malloc(sizeof(char) * (i + 2));
	if (!line)
		return (NULL);
	i = -1;
	while (rest[++i] && rest[i] != '\n')
		line[i] = rest[i];
	if (rest[i] == '\n')
	{
		line[i] = '\n';
		i++;
	}
	line[i] = '\0';
	return (line);
}

char	*ft_get_rest(char *rest, char *line)
{
	char	*rest1;
	int		i;
	int		j;

	i = ft_strlen(line);
	if (!rest[i])
		return (free(rest), NULL);
	j = 0;
	while (rest[i++])
		j++;
	rest1 = malloc(sizeof(char) * (j + 1));
	if (!rest)
		return (NULL);
	i = ft_strlen(line);
	j = 0;
	while (rest[i])
		rest1[j++] = rest[i++];
	rest1[j] = '\0';
	return (free(rest), rest1);
}

char	*file_to_read(int fd, char *rest)
{
	char	*buff;
	int		readed;

	readed = 1;
	while (!newline_exist(rest) && readed != 0)
	{
		buff = malloc(sizeof(char) * (BUFFER_SIZE + 1));
		if (!buff)
			return (NULL);
		readed = (int)read(fd, buff, BUFFER_SIZE);
		if ((!rest && readed == 0) || readed == -1)
			return (free(buff), NULL);
		buff[readed] = '\0';
		rest = ft_strjoin(rest, buff);
	}
	return (rest);
}

char	*get_next_line(int fd)
{
	static char	*rest;
	char		*line;
	char		*temp;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	temp = file_to_read(fd, rest);
	if (!temp)
	{
		if (rest)
			free(rest);
		rest = NULL;
		return (NULL);
	}
	rest = temp;
	line = ft_get_line(rest);
	rest = ft_get_rest(rest, line);
	return (line);
}
