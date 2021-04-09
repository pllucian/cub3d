/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycast0.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pllucian <pllucian@21-school.ru>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/19 22:11:42 by pllucian          #+#    #+#             */
/*   Updated: 2021/04/10 01:05:58 by pllucian         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int			exit_free(t_data *data)
{
	free_data(data);
	exit(0);
}

static void	init_texture(t_data *data, t_img *tex_img, char *file)
{
	if (!(tex_img->img = mlx_xpm_file_to_image(data->mlx, file, \
		&tex_img->width, &tex_img->height)))
		exit_free(data);
	tex_img->addr = mlx_get_data_addr(tex_img->img, &tex_img->bits_pp, \
	&tex_img->line_len, &tex_img->endian);
}

static void	init_textures(t_data *data)
{
	init_texture(data, &data->no_img, data->map.no_path);
	init_texture(data, &data->so_img, data->map.so_path);
	init_texture(data, &data->we_img, data->map.we_path);
	init_texture(data, &data->ea_img, data->map.ea_path);
	init_texture(data, &data->sp_img, data->map.sp_path);
}

void		raycast(t_data *data)
{
	if (!(data->mlx = mlx_init()))
		exit_free(data);
	mlx_get_screen_size(data->mlx, &data->screen_x, &data->screen_y);
	if (data->map.res_x > data->screen_x || data->map.res_x < 0)
		data->map.res_x = data->screen_x;
	if (data->map.res_y > data->screen_y || data->map.res_y < 0)
		data->map.res_y = data->screen_y;
	if (!(data->map_img.img = mlx_new_image(data->mlx, \
		data->map.res_x, data->map.res_y)))
		exit_free(data);
	data->map_img.addr = mlx_get_data_addr(data->map_img.img, \
	&data->map_img.bits_pp, &data->map_img.line_len, &data->map_img.endian);
	init_textures(data);
	if (data->save)
		render(data);
	if (!(data->win = mlx_new_window(data->mlx, \
		data->map.res_x, data->map.res_y, "cub3D")))
		exit_free(data);
	mlx_hook(data->win, 33, 1L << 17, exit_free, data);
	mlx_hook(data->win, 2, 1L << 0, key_press, data);
	mlx_hook(data->win, 3, 1L << 1, key_release, data);
	mlx_loop_hook(data->mlx, render, data);
	mlx_loop(data->mlx);
}
