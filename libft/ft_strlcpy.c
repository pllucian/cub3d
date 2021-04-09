/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pllucian <pllucian@21-school.ru>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/11 16:10:49 by pllucian          #+#    #+#             */
/*   Updated: 2021/03/09 12:33:45 by pllucian         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcpy(char *dest, const char *src, size_t size)
{
	char		*d;
	const char	*s;
	size_t		n;

	d = dest;
	s = src;
	n = size;
	if (!s)
		return (0);
	if (n)
		while (--n && (*d++ = *s++))
			;
	if (!n && size)
		*d = '\0';
	return (ft_strlen(src));
}
