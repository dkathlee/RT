/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   long_arith.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dkathlee <dkathlee@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/14 09:15:51 by dkathlee          #+#    #+#             */
/*   Updated: 2020/01/28 16:54:12 by dkathlee         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

char		*long_pow(char *nbr, int pow)
{
	char	*res;
	char	*tmp;

	if (pow == 0)
		return (ft_strdup("1"));
	res = ft_strdup(nbr);
	while (pow > 1)
	{
		tmp = res;
		res = long_mul(res, nbr);
		ft_memdel((void**)&tmp);
		pow--;
	}
	return (res);
}

static void	long_mul_cycle(char *nb1, char *nb2, char *res)
{
	int		i;
	int		j;
	int		nb2len;
	int		tmp;
	int		carry;

	nb2len = ft_strlen(nb2);
	i = ft_strlen(nb1) - 1;
	while (i >= 0)
	{
		j = nb2len - 1;
		carry = 0;
		while (j >= 0 || carry)
		{
			tmp = (res[i + j + 1] - '0') + (nb1[i] - '0') *
								(j >= 0 ? (nb2[j] - '0') : 0) + carry;
			res[i + j + 1] = tmp % 10 + '0';
			carry = tmp / 10;
			j--;
		}
		i--;
	}
}

static char	*remove_leading_zeros(char **num)
{
	int		i;
	char	*res;

	i = 0;
	while ((*num)[i] == '0')
		i++;
	res = ft_strdup(*num + i);
	ft_memdel((void**)num);
	return (res);
}

char		*long_mul(char *nb1, char *nb2)
{
	char	*res;
	int		tmp;

	tmp = ft_strlen(nb2);
	res = ft_strnew(ft_strlen(nb1) + tmp);
	ft_memset(res, '0', ft_strlen(nb1) + tmp);
	long_mul_cycle(nb1, nb2, res);
	res = remove_leading_zeros(&res);
	return (res);
}
