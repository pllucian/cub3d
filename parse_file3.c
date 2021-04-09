/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_file3.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pllucian <pllucian@21-school.ru>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/15 12:57:20 by pllucian          #+#    #+#             */
/*   Updated: 2021/04/10 00:04:22 by pllucian         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void		init_sprites(t_data *data)
{
	int		y;
	int		x;
	int		i;

	if (data->spr_sum > 0)
		data->sprites = ft_calloc(data->spr_sum + 1, sizeof(t_sprite*));
	i = -1;
	y = -1;
	while (++y < data->map.y_max)
	{
		x = -1;
		while (++x < data->map.x_max)
		{
			if (data->map.map[y][x] == '2')
			{
				data->sprites[++i] = ft_calloc(1, sizeof(t_sprite));
				data->sprites[i]->pos_y = y + 0.5;
				data->sprites[i]->pos_x = x + 0.5;
			}
		}
	}
}

static void	init_keys(t_player *plr)
{
	plr->key_w = 0;
	plr->key_a = 0;
	plr->key_s = 0;
	plr->key_d = 0;
	plr->key_left = 0;
	plr->key_right = 0;
}

void		init_player(t_data *data, int x, int y)
{
	data->player.dir_y = 0;
	data->player.dir_x = 0;
	data->player.plane_y = 0;
	data->player.plane_x = 0;
	if (data->map.map[y][x] == 'N')
	{
		data->player.dir_y = -1;
		data->player.plane_x = 0.66;
	}
	else if (data->map.map[y][x] == 'S')
	{
		data->player.dir_y = 1;
		data->player.plane_x = -0.66;
	}
	else if (data->map.map[y][x] == 'W')
	{
		data->player.dir_x = -1;
		data->player.plane_y = -0.66;
	}
	else if (data->map.map[y][x] == 'E')
	{
		data->player.dir_x = 1;
		data->player.plane_y = 0.66;
	}
	init_keys(&data->player);
}

void		get_map(t_data *data)
{
	t_list	*tmp;
	int		i;

	data->map.y_max = ft_lstsize(data->map.map_lst);
	data->map.map = ft_calloc(data->map.y_max + 1, sizeof(char*));
	tmp = data->map.map_lst;
	data->map.x_max = 0;
	while (tmp)
	{
		i = ft_strlen(tmp->content);
		i > data->map.x_max ? (data->map.x_max = i) : 0;
		tmp = tmp->next;
	}
	tmp = data->map.map_lst;
	i = 0;
	while (tmp)
	{
		data->map.map[i] = ft_calloc(data->map.x_max + 1, sizeof(char));
		ft_memset(data->map.map[i], ' ', data->map.x_max);
		ft_memcpy(data->map.map[i++], tmp->content, ft_strlen(tmp->content));
		tmp = tmp->next;
	}
	ft_lstclear(&data->map.map_lst, free);
	data->map.map_lst = NULL;
	check_map(data);
}

int			get_sp_path(char *line, char **elements, t_data *data)
{
	int		fd;

	if (MAP_S & data->map.check)
		return (52);
	data->map.sp_path = ft_strdup(elements[1]);
	data->map.check = data->map.check | MAP_S;
	if ((fd = open(data->map.sp_path, O_RDWR)) < 0)
	{
		free(line);
		exit_error(data, errno, data->map.sp_path);
	}
	close(fd);
	return (0);
}
