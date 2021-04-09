/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycast6.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pllucian <pllucian@21-school.ru>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/24 01:13:19 by pllucian          #+#    #+#             */
/*   Updated: 2021/04/09 23:48:58 by pllucian         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void	sort_sprites(t_sprite **spr, int first, int last)
{
	t_sprite	*tmp;
	int			left;
	int			right;
	int			pivot;

	if ((left = first) < last)
	{
		right = last;
		pivot = (first + last) / 2;
		while (left < right)
		{
			while (spr[left]->spr_dist > spr[pivot]->spr_dist)
				left++;
			while (spr[right]->spr_dist < spr[pivot]->spr_dist)
				right--;
			if (left <= right)
			{
				tmp = spr[left];
				spr[left++] = spr[right];
				spr[right--] = tmp;
			}
		}
		sort_sprites(spr, first, right);
		sort_sprites(spr, left, last);
	}
}

static void	get_spr_dist(t_sprite **spr, t_player *plr, int spr_sum)
{
	int		i;

	i = -1;
	while (++i < spr_sum)
	{
		spr[i]->spr_dist = \
		((plr->pos_x - spr[i]->pos_x) * (plr->pos_x - spr[i]->pos_x) + \
		(plr->pos_y - spr[i]->pos_y) * (plr->pos_y - spr[i]->pos_y));
	}
}

void		render_sprites(t_data *data, double **buffer)
{
	int		i;

	get_spr_dist(data->sprites, &data->player, data->spr_sum);
	sort_sprites(data->sprites, 0, data->spr_sum - 1);
	i = -1;
	while (++i < data->spr_sum)
	{
		render_sprite_line(data, &data->player, buffer, i);
	}
}
