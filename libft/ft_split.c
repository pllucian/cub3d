/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pllucian <pllucian@21-school.ru>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/16 22:11:42 by pllucian          #+#    #+#             */
/*   Updated: 2020/11/19 21:49:23 by pllucian         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static size_t	ft_strs_num(const char *s, char c)
{
	size_t		num;

	num = 0;
	while (*s)
	{
		while (*s == c)
			s++;
		if (*s)
		{
			num++;
			while (*s && *s != c)
				s++;
		}
	}
	return (num);
}

static void		ft_free_all(char **strs, size_t n)
{
	while (n--)
		free(strs[n]);
	free(strs);
}

static char		**ft_get_strs(const char *s, char c, size_t n)
{
	char		**strs;
	const char	*p;
	size_t		i;

	if (!(strs = (char**)malloc(sizeof(char*) * (n + 1))))
		return (NULL);
	i = 0;
	while (*(p = s) && i < n)
	{
		while (*p && *p == c)
			p++;
		if (*(s = p))
		{
			while (*p && *p != c)
				p++;
			if (!(strs[i++] = ft_substr(s, 0, p - s)))
			{
				ft_free_all(strs, i);
				return (NULL);
			}
			s = p;
		}
	}
	strs[i] = NULL;
	return (strs);
}

char			**ft_split(char const *s, char c)
{
	char		**strs;

	if (!s)
		return (NULL);
	strs = ft_get_strs(s, c, ft_strs_num(s, c));
	return (strs);
}
