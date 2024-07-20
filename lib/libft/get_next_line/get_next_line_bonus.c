/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jtu <jtu@student.hive.fi>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/27 12:15:39 by jtu               #+#    #+#             */
/*   Updated: 2023/12/20 14:14:46 by jtu              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line_bonus.h"

static char	*ft_free(char **str)
{
	free(*str);
	*str = NULL;
	return (NULL);
}

static int	ft_free_strs(char *str1, char *str2)
{
	free(str1);
	free(str2);
	return (-1);
}

static int	ft_get_line(char **stash, char **line)
{
	char	*temp;
	int		i;

	i = 0;
	while ((*stash)[i] && (*stash)[i] != '\n')
		i++;
	if ((*stash)[i] == '\n')
	{
		*line = ft_substr(*stash, 0, i + 1);
		if (!(*line))
			return (-1);
		temp = ft_substr(*stash, i + 1, ft_strlen(*stash) - i - 1);
		if (!temp)
		{
			free(*line);
			return (-1);
		}
		free(*stash);
		*stash = temp;
		return (1);
	}
	return (0);
}

static int	read_to_stash(int fd, char **stash)
{
	int		read_len;
	char	*temp;
	char	*buf;

	buf = malloc(sizeof(char) * (BUFFER_SIZE + 1));
	if (!buf)
		return (-1);
	read_len = read(fd, buf, BUFFER_SIZE);
	while (read_len > 0)
	{
		buf[read_len] = '\0';
		if (!*stash)
			*stash = ft_strdup("");
		temp = *stash;
		*stash = ft_strjoin(temp, buf);
		if (!*stash)
			return (ft_free_strs(temp, buf));
		free(temp);
		if (ft_strchr(buf, '\n'))
			break ;
		read_len = read(fd, buf, BUFFER_SIZE);
	}
	free(buf);
	return (read_len);
}

char	*get_next_line(int fd)
{
	static char	*stash[OPEN_MAX];
	char		*line;
	int			status;

	line = NULL;
	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	status = read_to_stash(fd, &stash[fd]);
	if (!stash[fd] || !*stash[fd] || status < 0
		|| ft_get_line(&stash[fd], &line) < 0)
		return (ft_free(&stash[fd]));
	if (line)
		return (line);
	if (stash[fd] && *stash[fd] != '\0')
	{
		line = ft_strdup(stash[fd]);
		ft_free(&stash[fd]);
	}
	return (line);
}
