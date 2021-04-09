/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   save_to_bmp.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pllucian <pllucian@21-school.ru>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/31 01:05:11 by pllucian          #+#    #+#             */
/*   Updated: 2021/04/09 23:51:44 by pllucian         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void	set_bmp_header(int fd, t_data *data)
{
	int		field;

	write(fd, "BM", 2);
	field = 14 + 40 + 4 * data->map.res_x * data->map.res_y;
	write(fd, &field, 4);
	field = 0;
	write(fd, &field, 4);
	field = 54;
	write(fd, &field, 4);
	field = 40;
	write(fd, &field, 4);
	write(fd, &data->map.res_x, 4);
	write(fd, &data->map.res_y, 4);
	field = 1;
	write(fd, &field, 2);
	write(fd, &data->map_img.bits_pp, 2);
	field = 0;
	write(fd, &field, 4);
	write(fd, &field, 4);
	write(fd, &field, 4);
	write(fd, &field, 4);
	write(fd, &field, 4);
	write(fd, &field, 4);
}

void		save_to_bmp(t_data *data)
{
	int				fd;
	int				y;
	int				x;
	unsigned int	color;

	if ((fd = open("cub3D.bmp", O_CREAT | O_RDWR | O_TRUNC, 0755)) < 0)
	{
		free_data(data);
		exit_error(data, errno, "cub3D.bmp");
	}
	set_bmp_header(fd, data);
	y = data->map.res_y;
	while (--y >= 0)
	{
		x = -1;
		while (++x < data->map.res_x)
		{
			color = my_mlx_pixel_get(&data->map_img, x, y);
			write(fd, &color, 4);
		}
	}
	close(fd);
	exit_free(data);
}
