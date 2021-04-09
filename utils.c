/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pllucian <pllucian@21-school.ru>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/09 14:41:06 by pllucian          #+#    #+#             */
/*   Updated: 2021/04/01 01:48:45 by pllucian         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int			ft_str_isdigit(char *str)
{
	while (*str)
	{
		if (!ft_isdigit(*str++))
			return (0);
	}
	return (1);
}

size_t		ft_arraylen(char **array)
{
	size_t		len;

	if (!array)
		return (0);
	len = 0;
	while (*array++)
		len++;
	return (len);
}

void		ft_freearray(void **array)
{
	void	**tmp;

	tmp = array;
	while (*tmp)
		free(*tmp++);
	free(array);
}
