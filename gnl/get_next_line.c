/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clauren <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/13 15:54:24 by clauren           #+#    #+#             */
/*   Updated: 2020/07/15 02:13:41 by clauren          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

int		cut(char **get, char **line, int c)
{
	char	*tmp;
	int		end;
	size_t	pos;

	pos = ft_strpos(*get, c);
	end = (c == '\0') ? 1 : -1;
	if (!(*line = ft_substr(*get, 0, pos + end)))
		return (-1);
	if (end == 1)
	{
		free(*get);
		*get = NULL;
		return (0);
	}
	if (!(tmp = ft_substr(*get, pos, ft_strlen(*get) - pos)))
		return (-1);
	free(*get);
	*get = tmp;
	return (1);
}

int		get_next_line(int fd, char **line)
{
	static char	*rack;
	char		*tmp;
	char		buff[BUFFER_SIZE + 1];
	size_t		readed;

	if ((!rack && !(rack = ft_strdup("")))
		|| (read(fd, 0, 0) == -1))
		return (-1);
	readed = 1;
	while (readed && !ft_strpos(rack, '\n'))
	{
		readed = read(fd, buff, BUFFER_SIZE);
		buff[readed] = '\0';
		if (!(tmp = ft_strjoin(rack, buff)))
			return (-1);
		free(rack);
		rack = tmp;
	}
	if (readed)
		return (cut(&rack, line, '\n'));
	else
		return (cut(&rack, line, '\0'));
}
