/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pllucian <pllucian@21-school.ru>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/06 14:04:53 by pllucian          #+#    #+#             */
/*   Updated: 2021/04/09 23:00:40 by pllucian         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void		exit_error(t_data *data, int error, const char *messege)
{
	errno = error;
	perror(messege);
	free_data(data);
	exit(-1);
}

void		free_data(t_data *data)
{
	data->map.no_path ? free(data->map.no_path) : 0;
	data->map.so_path ? free(data->map.so_path) : 0;
	data->map.we_path ? free(data->map.we_path) : 0;
	data->map.ea_path ? free(data->map.ea_path) : 0;
	data->map.sp_path ? free(data->map.sp_path) : 0;
	data->map.map_lst ? ft_lstclear(&data->map.map_lst, free) : 0;
	data->map.map ? ft_freearray((void**)data->map.map) : 0;
	data->sprites ? ft_freearray((void**)data->sprites) : 0;
	if (data->mlx)
	{
		data->map_img.img ? mlx_destroy_image(data->mlx, data->map_img.img) : 0;
		data->no_img.img ? mlx_destroy_image(data->mlx, data->no_img.img) : 0;
		data->so_img.img ? mlx_destroy_image(data->mlx, data->so_img.img) : 0;
		data->we_img.img ? mlx_destroy_image(data->mlx, data->we_img.img) : 0;
		data->ea_img.img ? mlx_destroy_image(data->mlx, data->ea_img.img) : 0;
		data->sp_img.img ? mlx_destroy_image(data->mlx, data->sp_img.img) : 0;
		data->win ? mlx_destroy_window(data->mlx, data->win) : 0;
		mlx_destroy_display(data->mlx);
		free(data->mlx);
	}
}

static void	init_data(t_data *data)
{
	data->map.res_x = 0;
	data->map.res_y = 0;
	data->map.no_path = NULL;
	data->map.so_path = NULL;
	data->map.we_path = NULL;
	data->map.ea_path = NULL;
	data->map.sp_path = NULL;
	data->map.f_color = 0;
	data->map.c_color = 0;
	data->map.check = MAP_NONE;
	data->map.map_lst = NULL;
	data->map.map = NULL;
	data->map.x_max = 0;
	data->map.y_max = 0;
	data->spr_sum = 0;
	data->sprites = NULL;
	data->mlx = NULL;
	data->win = NULL;
	data->map_img.img = NULL;
	data->no_img.img = NULL;
	data->so_img.img = NULL;
	data->we_img.img = NULL;
	data->ea_img.img = NULL;
	data->sp_img.img = NULL;
}

static void	check_args(t_data *data, int argc, char **argv)
{
	if (argc < 2)
		exit_error(data, EINVAL, \
		"The first argument must be a scene description file");
	else if (ft_strncmp(ft_strrchr(argv[1], '.'), ".cub", 5))
		exit_error(data, EINVAL, \
		"The filename doesn't end with the `.cub` extension");
	else if (argc > 2 && ft_strncmp(argv[2], "--save", 7))
		exit_error(data, EINVAL, \
		"The second argument can be only `--save`");
	else if (argc > 3)
		exit_error(data, E2BIG, "Too many arguments");
}

int			main(int argc, char **argv)
{
	t_data	data;

	data.save = 0;
	init_data(&data);
	check_args(&data, argc, argv);
	if (argc > 2)
		data.save = 1;
	parse_file(argv[1], &data);
	raycast(&data);
	return (0);
}
