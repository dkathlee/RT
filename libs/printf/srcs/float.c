/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   float.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dkathlee <dkathlee@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/27 14:20:21 by dkathlee          #+#    #+#             */
/*   Updated: 2020/02/06 15:32:02 by dkathlee         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

char		*insert_point(char *nbr, int len, int exp, t_printf *p)
{
	char	*tmp;
	int		pr;
	int		itmp;

	pr = p->precision == -1 ? 7 : p->precision + 1;
	tmp = ft_strnew(len - 52 + pr + 1);
	if (exp >= 1023)
	{
		ft_memcpy(tmp, nbr, len - 52);
		tmp[len - 52] = '.';
		ft_memcpy(tmp + len - 51, nbr + len - 52, pr > 52 ? 52 : pr);
		ft_memset(tmp + len + 1, '0', pr - 52 <= 0 ? 0 : pr - 52);
	}
	else
	{
		ft_memcpy(tmp, "0.", 2);
		itmp = 52 + (1023 - exp) - len > pr ? pr : 52 + (1023 - exp) - len;
		ft_memset(tmp + 2, '0', itmp);
		if (pr - itmp > 0)
			ft_memcpy(tmp + 2 + itmp, nbr, pr - itmp > len ? len : pr - itmp);
		ft_memset(tmp + itmp + len + 2, '0', pr - len - itmp + 1 <= 0 ? 0 :
															pr - len - itmp);
	}
	return (tmp);
}

char		*insert_point_long(char *nbr, int len, int exp, t_printf *p)
{
	char	*tmp;
	int		pr;
	int		itmp;

	pr = p->precision == -1 ? 7 : p->precision + 1;
	tmp = ft_strnew(len - 63 + pr + 1);
	if (exp >= 16383)
	{
		ft_memcpy(tmp, nbr, len - 63);
		tmp[len - 63] = '.';
		ft_memcpy(tmp + len - 62, nbr + len - 63, pr > 63 ? 63 : pr);
		ft_memset(tmp + len + 1, '0', pr - 63 <= 0 ? 0 : pr - 63);
	}
	else
	{
		ft_memcpy(tmp, "0.", 2);
		itmp = 63 + (16383 - exp) - len > pr ? pr : 63 + (16383 - exp) - len;
		ft_memset(tmp + 2, '0', itmp);
		if (pr - itmp > 0)
			ft_memcpy(tmp + 2 + itmp, nbr, pr - itmp > len ? len : pr - itmp);
		ft_memset(tmp + itmp + len + 2, '0', pr - len - itmp + 1 <= 0 ? 0 :
															pr - len - itmp);
	}
	return (tmp);
}

static void	float_round1(char **nbr, int len, int i)
{
	char	tmp;

	while (((*nbr)[--len] >= '5' || (*nbr)[len] == '.') && len != -1)
	{
		if ((*nbr)[len] != '9')
			break ;
		if ((*nbr)[len] == '.')
			continue ;
		(*nbr)[len] = '0';
	}
	if (len == -1)
	{
		tmp = (*nbr)[++len];
		(*nbr)[len] = '1';
		while (++len != i)
		{
			(*nbr)[len] = tmp;
			tmp = (*nbr)[len + 1];
		}
	}
	else
		(*nbr)[len]++;
}

void		float_round(char **nbr, int len)
{
	int		i;

	i = --len;
	if ((*nbr)[len] >= '5')
		float_round1(nbr, len, i);
	(*nbr)[i] = 0;
}
