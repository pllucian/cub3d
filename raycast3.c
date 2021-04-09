/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycast3.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pllucian <pllucian@21-school.ru>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/22 13:34:35 by pllucian          #+#    #+#             */
/*   Updated: 2021/04/09 23:47:13 by pllucian         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void	draw_wall_line_side(t_data *data, t_img *tex_img, int x, int y)
{
	t_player		*plr;
	unsigned int	color;

	plr = &data->player;
	plr->tex_y = (int)plr->tex_pos & (plr->tex_height - 1);
	plr->tex_pos += plr->step;
	color = my_mlx_pixel_get(tex_img, plr->tex_x, plr->tex_y);
	my_mlx_pixel_put(&data->map_img, x, y, color);
}

void		draw_wall_line(t_data *data, t_player *plr, int x)
{
	int		y;

	y = (int)plr->draw_start - 1;
	while (++y < plr->draw_end)
	{
		if (!plr->side)
		{
			if (plr->step_x > 0)
				draw_wall_line_side(data, &data->ea_img, x, y);
			else
				draw_wall_line_side(data, &data->we_img, x, y);
		}
		else
		{
			if (plr->step_y > 0)
				draw_wall_line_side(data, &data->so_img, x, y);
			else
				draw_wall_line_side(data, &data->no_img, x, y);
		}
	}
}

static void	get_tex_size(t_player *plr, t_img *tex)
{
	plr->tex_width = tex->width;
	plr->tex_height = tex->height;
}

static void	get_tex_side(t_data *data, t_player *plr)
{
	if (!plr->side)
	{
		if (plr->step_x > 0)
			get_tex_size(plr, &data->ea_img);
		else
			get_tex_size(plr, &data->we_img);
	}
	else
	{
		if (plr->step_y > 0)
			get_tex_size(plr, &data->so_img);
		else
			get_tex_size(plr, &data->no_img);
	}
}

void		get_wall_height(t_data *data, t_player *plr, t_map *map)
{
	plr->line_height = (int)(map->res_y / plr->perp_wall_dist);
	plr->draw_start = map->res_y / 2 - plr->line_height / 2;
	if (plr->draw_start < 0)
		plr->draw_start = 0;
	plr->draw_end = map->res_y / 2 + plr->line_height / 2;
	if (plr->draw_end >= map->res_y)
		plr->draw_end = map->res_y - 1;
	if (!plr->side)
		plr->wall_x = plr->pos_y + plr->perp_wall_dist * plr->ray_dir_y;
	else
		plr->wall_x = plr->pos_x + plr->perp_wall_dist * plr->ray_dir_x;
	plr->wall_x -= floor((plr->wall_x));
	get_tex_side(data, plr);
	plr->tex_x = (int)(plr->wall_x * (double)plr->tex_width);
	if (!plr->side && plr->ray_dir_x > 0)
		plr->tex_x = plr->tex_width - plr->tex_x - 1;
	if (plr->side && plr->ray_dir_y < 0)
		plr->tex_x = plr->tex_width - plr->tex_x - 1;
	plr->step = 1.0 * plr->tex_height / plr->line_height;
	plr->tex_pos = \
	(plr->draw_start - map->res_y / 2 + plr->line_height / 2) * plr->step;
}
