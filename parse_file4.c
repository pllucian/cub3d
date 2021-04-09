/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_file4.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pllucian <pllucian@21-school.ru>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/17 23:25:50 by pllucian          #+#    #+#             */
/*   Updated: 2021/04/09 23:13:30 by pllucian         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static int	check_map_char_closed(t_data *data, int c)
{
	int		y;
	int		x;

	y = 0;
	while (++y < data->map.y_max - 1)
	{
		x = 0;
		while (++x < data->map.x_max - 1)
		{
			if (data->map.map[y][x] == (char)c && \
				(data->map.map[y][x - 1] == ' ' || \
				data->map.map[y][x + 1] == ' ' || \
				data->map.map[y - 1][x] == ' ' || \
				data->map.map[y + 1][x] == ' ' || \
				data->map.map[y - 1][x - 1] == ' ' || \
				data->map.map[y - 1][x + 1] == ' ' || \
				data->map.map[y + 1][x - 1] == ' ' || \
				data->map.map[y + 1][x + 1] == ' '))
				return (1);
		}
	}
	return (0);
}

static int	check_map_inside(t_data *data)
{
	return (check_map_char_closed(data, '0') ||
		check_map_char_closed(data, '2') ||
		check_map_char_closed(data, 'N') ||
		check_map_char_closed(data, 'S') ||
		check_map_char_closed(data, 'W') ||
		check_map_char_closed(data, 'E'));
}

static int	check_map_border(t_data *data)
{
	int		error_map;
	int		y;
	int		x;

	error_map = 0;
	x = 0;
	while (data->map.map[0][x] && !error_map)
		(data->map.map[0][x] == ' ' || data->map.map[0][x] == '1') \
		? x++ : (error_map = 1);
	y = 1;
	while (data->map.map[y][0] && y < data->map.y_max - 1 && !error_map)
		((data->map.map[y][0] == ' ' || data->map.map[y][0] == '1') && \
		(data->map.map[y][data->map.x_max - 1] == ' ' || \
		data->map.map[y][data->map.x_max - 1] == '1')) \
		? y++ : (error_map = 1);
	x = 0;
	while (data->map.map[data->map.y_max - 1][x] && !error_map)
		(data->map.map[data->map.y_max - 1][x] == ' ' || \
		data->map.map[data->map.y_max - 1][x] == '1') \
		? x++ : (error_map = 1);
	return (error_map);
}

static int	check_map_chars(t_data *data)
{
	int		y;
	int		x;
	int		count;

	count = 0;
	y = -1;
	while (++y < data->map.y_max)
	{
		x = -1;
		while (++x < data->map.x_max)
		{
			if (!ft_strchr(" 012NSWE", data->map.map[y][x]) || count > 1)
				return (1);
			if (data->map.map[y][x] == '2')
				data->spr_sum++;
			if (ft_strchr("NSWE", data->map.map[y][x]))
			{
				count++;
				data->player.pos_y = y + 0.5;
				data->player.pos_x = x + 0.5;
				init_player(data, x, y);
			}
		}
	}
	return (count != 1 ? 1 : 0);
}

void		check_map(t_data *data)
{
	if (check_map_chars(data) || \
		check_map_border(data) || \
		check_map_inside(data))
		exit_error(data, EPERM, "Error\nInvalid map");
	init_sprites(data);
}
