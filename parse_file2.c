/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_file2.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pllucian <pllucian@21-school.ru>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/11 13:41:05 by pllucian          #+#    #+#             */
/*   Updated: 2021/04/10 00:03:59 by pllucian         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static int	get_ea_path(char *line, char **elements, t_data *data)
{
	int		fd;

	if (MAP_EA & data->map.check)
		return (52);
	data->map.ea_path = ft_strdup(elements[1]);
	data->map.check = data->map.check | MAP_EA;
	if ((fd = open(data->map.ea_path, O_RDWR)) < 0)
	{
		free(line);
		exit_error(data, errno, data->map.ea_path);
	}
	close(fd);
	return (0);
}

static int	get_we_path(char *line, char **elements, t_data *data)
{
	int		fd;

	if (MAP_WE & data->map.check)
		return (52);
	data->map.we_path = ft_strdup(elements[1]);
	data->map.check = data->map.check | MAP_WE;
	if ((fd = open(data->map.we_path, O_RDWR)) < 0)
	{
		free(line);
		exit_error(data, errno, data->map.we_path);
	}
	close(fd);
	return (0);
}

static int	get_so_path(char *line, char **elements, t_data *data)
{
	int		fd;

	if (MAP_SO & data->map.check)
		return (52);
	data->map.so_path = ft_strdup(elements[1]);
	data->map.check = data->map.check | MAP_SO;
	if ((fd = open(data->map.so_path, O_RDWR)) < 0)
	{
		free(line);
		exit_error(data, errno, data->map.so_path);
	}
	close(fd);
	return (0);
}

static int	get_no_path(char *line, char **elements, t_data *data)
{
	int		fd;

	if (MAP_NO & data->map.check)
		return (52);
	data->map.no_path = ft_strdup(elements[1]);
	data->map.check = data->map.check | MAP_NO;
	if ((fd = open(data->map.no_path, O_RDWR)) < 0)
	{
		free(line);
		exit_error(data, errno, data->map.no_path);
	}
	close(fd);
	return (0);
}

int			get_textures_paths(char *line, char **elements, t_data *data)
{
	int		error_texture;

	if (ft_arraylen(elements) != 2)
		return (51);
	error_texture = 0;
	if (!ft_strncmp(elements[0], "NO", 3))
		error_texture = get_no_path(line, elements, data);
	else if (!ft_strncmp(elements[0], "SO", 3))
		error_texture = get_so_path(line, elements, data);
	else if (!ft_strncmp(elements[0], "WE", 3))
		error_texture = get_we_path(line, elements, data);
	else if (!ft_strncmp(elements[0], "EA", 3))
		error_texture = get_ea_path(line, elements, data);
	else if (!ft_strncmp(elements[0], "S", 2))
		error_texture = get_sp_path(line, elements, data);
	return (error_texture);
}
