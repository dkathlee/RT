/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa_base.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dkathlee <dkathlee@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/25 10:24:57 by dkathlee          #+#    #+#             */
/*   Updated: 2019/12/26 10:08:45 by dkathlee         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	calc_len(unsigned long long nb, int base)
{
	int	res;

	res = 0;
	while (nb != 0)
	{
		nb /= base;
		res++;
	}
	return (res);
}

char		*ft_itoa_base(unsigned long long nb, const char *base_str)
{
	int		base;
	int		i;
	char	*res;

	if (nb == 0)
	{
		res = ft_strnew(1);
		res[0] = '0';
		return (res);
	}
	base = ft_strlen(base_str);
	i = calc_len(nb, base) - 1;
	res = ft_strnew(i + 1);
	while (nb != 0)
	{
		res[i--] = base_str[nb % base];
		nb /= base;
	}
	return (res);
}
