/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pllucian <pllucian@21-school.ru>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/14 12:23:04 by pllucian          #+#    #+#             */
/*   Updated: 2021/03/30 23:25:30 by pllucian         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static char	*get_tail(char *memory)
{
	char	*ptr_n;
	char	*tmp;

	if (!memory)
		return (NULL);
	ptr_n = NULL;
	if ((ptr_n = ft_strchr(memory, '\n')))
	{
		tmp = memory;
		memory = ft_strdup(++ptr_n);
		free(tmp);
	}
	else
	{
		free(memory);
		return (NULL);
	}
	return (memory);
}

static char	*get_head(char *memory)
{
	char	*line;
	char	*ptr_n;

	if (!memory)
		return (NULL);
	ptr_n = NULL;
	if ((ptr_n = ft_strchr(memory, '\n')))
	{
		*ptr_n = '\0';
		line = ft_strdup(memory);
		*ptr_n = '\n';
	}
	else
		line = ft_strdup(memory);
	return (line);
}

int			get_next_line(int fd, char **line)
{
	static char	*memory;
	char		*buffer;
	int			read_size;
	char		*tmp;

	read_size = 1;
	if ((read(fd, 0, 0) == -1) || !line)
		return (-1);
	if (!(buffer = malloc(sizeof(char) * 65)))
		return (-1);
	while (!(ft_strchr(memory, '\n')) && read_size)
	{
		read_size = read(fd, buffer, 64);
		buffer[read_size] = '\0';
		tmp = memory;
		memory = ft_strjoin(memory, buffer);
		free(tmp);
	}
	free(buffer);
	*line = get_head(memory);
	memory = get_tail(memory);
	return (read_size ? 1 : 0);
}
