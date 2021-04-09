/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycast7.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pllucian <pllucian@21-school.ru>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/28 13:55:02 by pllucian          #+#    #+#             */
/*   Updated: 2021/04/09 23:49:18 by pllucian         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void	sprite_pixel_put(t_data *data, int stripe, int *y, int *d)
{
	t_map			*map;
	t_player		*plr;
	unsigned int	color;

	map = &data->map;
	plr = &data->player;
	*d = (*y) * 256 - map->res_y * 128 + plr->sprite_height * 128;
	plr->sprite_tex_y = ((*d * plr->tex_height) / plr->sprite_height) / 256;
	color = my_mlx_pixel_get(&data->sp_img, \
	plr->sprite_tex_x, plr->sprite_tex_y);
	if ((color & 0x00FFFFFF) != 0)
		my_mlx_pixel_put(&data->map_img, stripe, *y, color);
}

static void	draw_sprite_line(t_data *data, t_map *map, \
							t_player *plr, double **z_buffer)
{
	int	stripe;
	int	y;
	int d;

	stripe = plr->draw_start_x;
	while (stripe < plr->draw_end_x)
	{
		plr->sprite_tex_x = \
		(int)(256 * (stripe - (plr->sprite_screen_x - plr->sprite_width / 2)) \
		* plr->tex_width / plr->sprite_width) / 256;
		if (plr->transform_y > 0 && stripe > 0 && stripe < map->res_x && \
			plr->transform_y < (*z_buffer)[stripe])
		{
			y = plr->draw_start_y;
			while (y < plr->draw_end_y)
			{
				sprite_pixel_put(data, stripe, &y, &d);
				y++;
			}
		}
		stripe++;
	}
}

static void	get_sprite_size(t_map *map, t_player *plr)
{
	plr->sprite_height = abs((int)(map->res_y / (plr->transform_y)));
	plr->draw_start_y = map->res_y / 2 - plr->sprite_height / 2;
	if (plr->draw_start_y < 0)
		plr->draw_start_y = 0;
	plr->draw_end_y = map->res_y / 2 + plr->sprite_height / 2;
	if (plr->draw_end_y >= map->res_y)
		plr->draw_end_y = map->res_y - 1;
	plr->sprite_width = abs((int)(map->res_x / (plr->transform_y))) - 1;
	plr->draw_start_x = plr->sprite_screen_x - plr->sprite_width / 2;
	if (plr->draw_start_x < 0)
		plr->draw_start_x = 0;
	plr->draw_end_x = plr->sprite_screen_x + plr->sprite_width / 2;
	if (plr->draw_end_x >= map->res_x)
		plr->draw_end_x = map->res_x - 1;
}

static void	init_sprite_render(t_map *map, t_sprite **spr, t_player *plr, int i)
{
	plr->sprite_x = spr[i]->pos_x - plr->pos_x;
	plr->sprite_y = spr[i]->pos_y - plr->pos_y;
	plr->inv_det = \
	1.0 / (plr->plane_x * plr->dir_y - plr->dir_x * plr->plane_y);
	plr->transform_x = \
	plr->inv_det * (plr->dir_y * plr->sprite_x - plr->dir_x * plr->sprite_y);
	plr->transform_y = plr->inv_det * \
	(-plr->plane_y * plr->sprite_x + plr->plane_x * plr->sprite_y);
	plr->sprite_screen_x = \
	(int)((map->res_x / 2) * (1 + plr->transform_x / plr->transform_y));
}

void		render_sprite_line(t_data *data, t_player *plr, \
								double **z_buffer, int i)
{
	init_sprite_render(&data->map, data->sprites, plr, i);
	get_sprite_size(&data->map, plr);
	draw_sprite_line(data, &data->map, plr, z_buffer);
}
