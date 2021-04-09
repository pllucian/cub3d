/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycast2.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pllucian <pllucian@21-school.ru>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/22 10:54:46 by pllucian          #+#    #+#             */
/*   Updated: 2021/04/09 23:46:47 by pllucian         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void	get_wall_dist(t_player *plr)
{
	if (!plr->side)
	{
		plr->perp_wall_dist = \
		(plr->map_x - plr->pos_x + (1 - plr->step_x) / 2) / plr->ray_dir_x;
	}
	else
	{
		plr->perp_wall_dist = \
		(plr->map_y - plr->pos_y + (1 - plr->step_y) / 2) / plr->ray_dir_y;
	}
}

static void	dda_ray(t_player *plr, t_map *map)
{
	plr->hit = 0;
	while (!plr->hit)
	{
		if (plr->side_dist_x < plr->side_dist_y)
		{
			plr->side_dist_x += plr->delta_dist_x;
			plr->map_x += plr->step_x;
			plr->side = 0;
		}
		else
		{
			plr->side_dist_y += plr->delta_dist_y;
			plr->map_y += plr->step_y;
			plr->side = 1;
		}
		if (map->map[plr->map_y][plr->map_x] == '1')
			plr->hit = 1;
	}
}

static void	init_ray_step(t_player *plr)
{
	if (plr->ray_dir_x < 0)
	{
		plr->step_x = -1;
		plr->side_dist_x = (plr->pos_x - plr->map_x) * plr->delta_dist_x;
	}
	else
	{
		plr->step_x = 1;
		plr->side_dist_x = (plr->map_x + 1.0 - plr->pos_x) * plr->delta_dist_x;
	}
	if (plr->ray_dir_y < 0)
	{
		plr->step_y = -1;
		plr->side_dist_y = (plr->pos_y - plr->map_y) * plr->delta_dist_y;
	}
	else
	{
		plr->step_y = 1;
		plr->side_dist_y = (plr->map_y + 1.0 - plr->pos_y) * plr->delta_dist_y;
	}
}

static void	init_ray(t_player *plr, int width, int x)
{
	plr->camera_x = 2 * x / (double)width - 1;
	plr->ray_dir_x = plr->dir_x + plr->plane_x * plr->camera_x;
	plr->ray_dir_y = plr->dir_y + plr->plane_y * plr->camera_x;
	plr->map_x = (int)plr->pos_x;
	plr->map_y = (int)plr->pos_y;
	plr->delta_dist_x = fabs(1 / plr->ray_dir_x);
	plr->delta_dist_y = fabs(1 / plr->ray_dir_y);
	init_ray_step(plr);
}

void		render_wall_line(t_data *data, int x)
{
	init_ray(&data->player, data->map.res_x, x);
	dda_ray(&data->player, &data->map);
	get_wall_dist(&data->player);
	get_wall_height(data, &data->player, &data->map);
	draw_wall_line(data, &data->player, x);
}
