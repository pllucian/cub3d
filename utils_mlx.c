/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_mlx.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pllucian <pllucian@21-school.ru>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/19 18:14:15 by pllucian          #+#    #+#             */
/*   Updated: 2021/04/09 21:42:11 by pllucian         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void			my_mlx_pixel_put(t_img *img, int x, int y, int color)
{
	char	*dest;

	dest = img->addr + (y * img->line_len + x * (img->bits_pp / 8));
	*(unsigned int*)dest = color;
}

unsigned int	my_mlx_pixel_get(t_img *img, int x, int y)
{
	char	*dest;

	dest = img->addr + (y * img->line_len + x * (img->bits_pp / 8));
	return (*(unsigned int*)dest);
}
