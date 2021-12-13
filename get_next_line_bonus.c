/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hharit <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/06 17:16:40 by hharit            #+#    #+#             */
/*   Updated: 2021/12/06 21:39:38 by hharit           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line_bonus.h"

int	check_nl(char *str)
{
	if (!str)
		return (0);
	while (*str && *str != '\n')
		str++;
	if (*str == '\n')
		return (1);
	return (0);
}

char	*ft_line(char *save)
{
	char	*line;
	int		len;

	len = 0;
	if (!save || !*save)
		return (NULL);
	while (save[len] && save[len] != '\n')
		len++;
	line = (char *)malloc(sizeof(char) * (len + 2));
	if (!line)
		return (NULL);
	len = 0;
	while (save[len] && save[len] != '\n')
	{
		line[len] = save[len];
		len++;
	}
	if (save[len] == '\n')
		line[len++] = '\n';
	line[len] = '\0';
	return (line);
}

char	*rest(char *save)
{
	char	*rest;
	int		len;
	int		i;

	len = 0;
	i = 0;
	while (save[len] && save[len] != '\n')
		len++;
	if (save[len] && save[len] == '\n')
		len++;
	else
	{
		free(save);
		return (NULL);
	}
	rest = ft_strdup(&save[len]);
	free(save);
	return (rest);
}

int	check_len(int len, char *buf)
{
	if (len == -1)
	{
		free(buf);
		return (0);
	}
	return (1);
}

char	*get_next_line(int fd)
{
	static char	*save[1024];
	char		*buf;
	char		*line;
	int			len;

	len = 1;
	if (fd < 0)
		return (NULL);
	buf = (char *)malloc(sizeof(char) * BUFFER_SIZE + 1);
	if (!buf)
		return (NULL);
	while (!check_nl(save[fd]) && len > 0)
	{
		len = read(fd, buf, BUFFER_SIZE);
		if (!check_len(len, buf))
			return (NULL);
		buf[len] = '\0';
		save[fd] = ft_strjoin(save[fd], buf);
	}
	line = ft_line(save[fd]);
	save[fd] = rest(save[fd]);
	free(buf);
	return (line);
}
