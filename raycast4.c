/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycast4.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pllucian <pllucian@21-school.ru>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/22 15:46:15 by pllucian          #+#    #+#             */
/*   Updated: 2021/04/09 23:47:51 by pllucian         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int			key_press(int key, t_data *data)
{
	if (key == KEY_ESC)
		exit_free(data);
	if (key == KEY_W)
		data->player.key_w = 1;
	if (key == KEY_A)
		data->player.key_a = 1;
	if (key == KEY_S)
		data->player.key_s = 1;
	if (key == KEY_D)
		data->player.key_d = 1;
	if (key == KEY_LEFT)
		data->player.key_left = 1;
	if (key == KEY_RIGHT)
		data->player.key_right = 1;
	return (0);
}

int			key_release(int key, t_data *data)
{
	if (key == KEY_W)
		data->player.key_w = 0;
	if (key == KEY_A)
		data->player.key_a = 0;
	if (key == KEY_S)
		data->player.key_s = 0;
	if (key == KEY_D)
		data->player.key_d = 0;
	if (key == KEY_LEFT)
		data->player.key_left = 0;
	if (key == KEY_RIGHT)
		data->player.key_right = 0;
	return (0);
}

void		move_player(t_map *map, t_player *plr)
{
	if (plr->key_w)
		move_forward(map, plr);
	if (plr->key_s)
		move_backward(map, plr);
	if (plr->key_a)
		move_left(map, plr);
	if (plr->key_d)
		move_right(map, plr);
	if (plr->key_left || plr->key_right)
		rotate(plr);
}
