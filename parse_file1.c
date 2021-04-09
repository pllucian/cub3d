/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_file1.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pllucian <pllucian@21-school.ru>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/17 23:07:21 by pllucian          #+#    #+#             */
/*   Updated: 2021/04/09 22:18:51 by pllucian         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static int	get_rgb(char **elements, char **color, t_data *data)
{
	int		r;
	int		g;
	int		b;

	r = ft_atoi(color[0]);
	g = ft_atoi(color[1]);
	b = ft_atoi(color[2]);
	if (r < 0 || r > 255 || g < 0 || g > 255 || b < 0 || b > 255)
		return (41);
	if (**elements == 'F')
	{
		if (MAP_F & data->map.check)
			return (42);
		data->map.f_color = (r << 16 | g << 8 | b);
		data->map.check = data->map.check | MAP_F;
	}
	else
	{
		if (MAP_C & data->map.check)
			return (42);
		data->map.c_color = (r << 16 | g << 8 | b);
		data->map.check = data->map.check | MAP_C;
	}
	return (0);
}

static int	check_color(char **elements, char **color, t_data *data)
{
	if (ft_arraylen(color) != 3 || !ft_str_isdigit(color[0]) || \
		!ft_str_isdigit(color[1]) || !ft_str_isdigit(color[2]))
		return (41);
	else
		return (get_rgb(elements, color, data));
}

static int	check_commas(char *all_elements)
{
	int		count;
	char	*tmp;

	count = 0;
	tmp = all_elements;
	while (*tmp)
		*tmp++ == ',' ? count++ : 0;
	if (count > 2)
	{
		free(all_elements);
		return (41);
	}
	return (0);
}

int			get_colors_f_c(char **elements, t_data *data)
{
	char	**color;
	int		error_color;
	size_t	len;
	char	*all_elements;
	char	*tmp;

	if ((len = ft_arraylen(elements)) < 2 || len > 4)
		return (41);
	error_color = 0;
	all_elements = ft_strdup("");
	while (len - 1)
	{
		tmp = all_elements;
		all_elements = ft_strjoin(elements[--len], tmp);
		free(tmp);
	}
	len = ft_strlen(all_elements);
	if (check_commas(all_elements))
		return (41);
	color = ft_split(all_elements, ',');
	error_color = check_color(elements, color, data);
	free(all_elements);
	ft_freearray((void**)color);
	return (error_color);
}

int			get_resolution(char **elements, t_data *data)
{
	if (MAP_R & data->map.check)
		return (32);
	if (ft_arraylen(elements) != 3 || \
		!ft_str_isdigit(elements[1]) || !ft_str_isdigit(elements[2]))
		return (31);
	data->map.res_x = ft_atoi(elements[1]);
	data->map.res_y = ft_atoi(elements[2]);
	if (!data->map.res_x || !data->map.res_y)
		return (31);
	data->map.check = data->map.check | MAP_R;
	return (0);
}
