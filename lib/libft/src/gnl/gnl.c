/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gnl.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fiheaton <fiheaton@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/30 12:58:09 by fiheaton          #+#    #+#             */
/*   Updated: 2026/01/30 14:50:17 by fiheaton         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "gnl.h"

static int	save_buff(char **newline, char *buffer)
{
	char	*temp;

	temp = *newline;
	*newline = ft_strjoin(temp, buffer);
	free(temp);
	if (!(*newline))
		return (-1);
	return (0);
}

static	int	gnl(int fd, char **newline, char *buffer)
{
	int		i;

	i = 0;
	if (!(*newline))
		*newline = ft_strdup("");
	if (!(*newline))
		return (-1);
	while (!ft_strchr(*newline, '\n'))
	{
		i = read(fd, buffer, BUFFER_SIZE);
		if (i <= 0)
			break ;
		buffer[i] = '\0';
		if (save_buff(newline, buffer) == -1)
			return (-1);
	}
	if (!*newline || !**newline)
		return (0);
	return (1);
}

static int	save_line(int fd, char **nl, char **line)
{
	char	*pos;
	char	*temp;

	pos = ft_strchr(nl[fd], '\n');
	if (pos)
	{
		*line = ft_substr(nl[fd], 0, pos - nl[fd]);
		temp = nl[fd];
		nl[fd] = ft_strdup(temp + ft_strlen(*line) + 1);
		free(temp);
		if (!nl[fd])
			return (-1);
	}
	else
	{
		*line = ft_strdup(nl[fd]);
		free(nl[fd]);
		nl[fd] = NULL;
	}
	return (1);
}

int	get_next_line(int fd, char **line)
{
	char		buffer[BUFFER_SIZE + 1];
	static char	*newline[FD_MAX];
	int			ret;

	if (fd < 0 || fd >= FD_MAX || !line || BUFFER_SIZE <= 0)
		return (-1);
	ret = gnl(fd, &newline[fd], buffer);
	if (ret <= 0)
		return (ret);
	if (save_line(fd, newline, line) == -1)
		return (-1);
	return (1);
}
