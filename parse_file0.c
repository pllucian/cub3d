/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_file0.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pllucian <pllucian@21-school.ru>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/08 12:21:51 by pllucian          #+#    #+#             */
/*   Updated: 2021/04/09 22:25:12 by pllucian         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void	check_error_map(char *line, t_data *data, int err)
{
	free(line);
	err == 1 ? exit_error(data, EPERM, "Error\nEmpty line on the map") : 0;
	err == 2 ? exit_error(data, EPERM, "Error\nInvalid element") : 0;
	err == 31 ? exit_error(data, EPERM, "Error\nInvalid resolution") : 0;
	err == 32 ? exit_error(data, EPERM, "Error\nDuplicate resolution") : 0;
	err == 41 ? exit_error(data, EPERM, "Error\nInvalid color") : 0;
	err == 42 ? exit_error(data, EPERM, "Error\nDuplicate color") : 0;
	err == 51 ? exit_error(data, EPERM, "Error\nToo many texture paths") : 0;
	err == 52 ? exit_error(data, EPERM, "Error\nDuplicate texture path") : 0;
}

static void	parse_line(char *line, t_data *data)
{
	char	**elements;
	int		error_map;

	error_map = 0;
	elements = ft_split(line, ' ');
	if (!*line && !data->map.map_lst)
		;
	else if (!*line && data->map.map_lst)
		error_map = 1;
	else if (*line && !*elements && data->map.check != MAP_ALL)
		error_map = 2;
	else if (!ft_strncmp(*elements, "R", 2))
		error_map = get_resolution(elements, data);
	else if (!ft_strncmp(*elements, "F", 2) || !ft_strncmp(*elements, "C", 2))
		error_map = get_colors_f_c(elements, data);
	else if (!ft_strncmp(*elements, "NO", 3) || \
		!ft_strncmp(*elements, "SO", 3) || !ft_strncmp(*elements, "WE", 3) || \
		!ft_strncmp(*elements, "EA", 3) || !ft_strncmp(*elements, "S", 2))
		error_map = get_textures_paths(line, elements, data);
	else if (data->map.check == MAP_ALL)
		ft_lstadd_back(&data->map.map_lst, ft_lstnew(ft_strdup(line)));
	else
		error_map = 2;
	ft_freearray((void**)elements);
	error_map ? check_error_map(line, data, error_map) : 0;
}

void		parse_file(char *file, t_data *data)
{
	int		fd;
	char	*line;

	if ((fd = open(file, O_RDWR)) < 0)
		exit_error(data, errno, file);
	while (get_next_line(fd, &line))
	{
		parse_line(line, data);
		free(line);
	}
	parse_line(line, data);
	free(line);
	get_map(data);
}
