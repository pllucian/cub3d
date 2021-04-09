/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycast4.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pllucian <pllucian@21-school.ru>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/23 23:33:22 by pllucian          #+#    #+#             */
/*   Updated: 2021/04/09 18:18:19 by pllucian         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void		move_forward(t_map *map, t_player *plr)
{
	if (map->map\
	[(int)(plr->pos_y)][(int)(plr->pos_x + plr->dir_x * MOVE_SPEED * 2)] == '0')
		plr->pos_x += plr->dir_x * MOVE_SPEED;
	if (map->map\
	[(int)(plr->pos_y + plr->dir_y * MOVE_SPEED * 2)][(int)plr->pos_x] == '0')
		plr->pos_y += plr->dir_y * MOVE_SPEED;
}

void		move_backward(t_map *map, t_player *plr)
{
	if (map->map\
	[(int)plr->pos_y][(int)(plr->pos_x - plr->dir_x * MOVE_SPEED * 2)] == '0')
		plr->pos_x -= plr->dir_x * MOVE_SPEED;
	if (map->map\
	[(int)(plr->pos_y - plr->dir_y * MOVE_SPEED * 2)][(int)(plr->pos_x)] == '0')
		plr->pos_y -= plr->dir_y * MOVE_SPEED;
}

void		move_left(t_map *map, t_player *plr)
{
	if (map->map\
	[(int)plr->pos_y][(int)(plr->pos_x + plr->dir_y * MOVE_SPEED * 2)] == '0')
		plr->pos_x += plr->dir_y * MOVE_SPEED;
	if (map->map\
	[(int)(plr->pos_y - plr->dir_x * MOVE_SPEED * 2)][(int)(plr->pos_x)] == '0')
		plr->pos_y -= plr->dir_x * MOVE_SPEED;
}

void		move_right(t_map *map, t_player *plr)
{
	if (map->map\
	[(int)plr->pos_y][(int)(plr->pos_x - plr->dir_y * MOVE_SPEED * 2)] == '0')
		plr->pos_x -= plr->dir_y * MOVE_SPEED;
	if (map->map\
	[(int)(plr->pos_y + plr->dir_x * MOVE_SPEED * 2)][(int)(plr->pos_x)] == '0')
		plr->pos_y += plr->dir_x * MOVE_SPEED;
}

void		rotate(t_player *plr)
{
	double old_dir_x;
	double old_plane_x;
	double rotate_speed;

	old_dir_x = plr->dir_x;
	old_plane_x = plr->plane_x;
	rotate_speed = ROTATE_SPEED;
	if (plr->key_left)
		rotate_speed = -ROTATE_SPEED;
	plr->dir_x = plr->dir_x * cos(rotate_speed) - \
		plr->dir_y * sin(rotate_speed);
	plr->dir_y = old_dir_x * sin(rotate_speed) + \
		plr->dir_y * cos(rotate_speed);
	plr->plane_x = plr->plane_x * cos(rotate_speed) - \
		plr->plane_y * sin(rotate_speed);
	plr->plane_y = old_plane_x * sin(rotate_speed) +
		plr->plane_y * cos(rotate_speed);
}
