/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pllucian <pllucian@21-school.ru>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/19 13:39:17 by pllucian          #+#    #+#             */
/*   Updated: 2021/01/20 14:27:52 by pllucian         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_len(int n)
{
	int		len;

	len = 1;
	if (n < 0)
		len++;
	while (n /= 10)
		len++;
	return (len);
}

char		*ft_itoa(int n)
{
	long	n1;
	int		sign;
	int		len;
	char	*str;

	n1 = (long)n;
	sign = 1;
	if (n < 0)
		sign = -1;
	len = ft_len(n);
	if (!(str = (char*)(malloc(sizeof(char) * (len + 1)))))
		return (NULL);
	str[len--] = '\0';
	while ((sign < 0) ? len : len + 1)
	{
		str[len--] = (n1 * sign) % 10 + '0';
		n1 /= 10;
	}
	if (sign < 0)
		str[0] = '-';
	return (str);
}
