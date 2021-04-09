/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycast1.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pllucian <pllucian@21-school.ru>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/09 23:40:35 by pllucian          #+#    #+#             */
/*   Updated: 2021/04/09 23:46:12 by pllucian         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void	render_walls(t_data *data)
{
	double	*z_buffer;
	int		x;

	x = -1;
	z_buffer = ft_calloc(data->map.res_x + 1, sizeof(double));
	while (++x < data->map.res_x)
	{
		render_wall_line(data, x);
		z_buffer[x] = data->player.perp_wall_dist;
	}
	render_sprites(data, &z_buffer);
	free(z_buffer);
}

static void	render_background(t_data *data)
{
	int y;
	int x;

	y = -1;
	while (++y < data->map.res_y)
	{
		x = -1;
		while (++x < data->map.res_x)
		{
			if (y < data->map.res_y / 2)
				my_mlx_pixel_put(&data->map_img, x, y, data->map.c_color);
			else
				my_mlx_pixel_put(&data->map_img, x, y, data->map.f_color);
		}
	}
}

int			render(t_data *data)
{
	render_background(data);
	render_walls(data);
	if (data->save)
		save_to_bmp(data);
	move_player(&data->map, &data->player);
	mlx_put_image_to_window(data->mlx, data->win, data->map_img.img, 0, 0);
	return (0);
}
