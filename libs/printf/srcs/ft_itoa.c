/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dkathlee <dkathlee@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/06 11:02:17 by dkathlee          #+#    #+#             */
/*   Updated: 2019/12/26 10:09:12 by dkathlee         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_itoa(long long n)
{
	char				*tmp;
	char				*res;
	unsigned long long	t;

	if (n >= 0)
		res = ft_itoa_base(n, "0123456789");
	else
	{
		t = -n;
		tmp = ft_itoa_base(t, "0123456789");
		res = ft_strnew(ft_strlen(tmp) + 1);
		res[0] = '-';
		ft_strcpy(res + 1, tmp);
		ft_memdel((void**)&tmp);
	}
	return (res);
}
