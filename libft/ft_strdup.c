/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pllucian <pllucian@21-school.ru>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/15 18:22:33 by pllucian          #+#    #+#             */
/*   Updated: 2021/03/09 12:32:47 by pllucian         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strdup(const char *s)
{
	char	*p;
	size_t	len;

	if (!s)
		return (NULL);
	len = ft_strlen(s);
	if (!(p = (char*)malloc(sizeof(char) * (len + 1))))
		return (NULL);
	ft_strlcpy(p, s, len + 1);
	return (p);
}
