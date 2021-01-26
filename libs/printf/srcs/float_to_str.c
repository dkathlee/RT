/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   float_to_str.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dkathlee <dkathlee@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/06 13:16:09 by dkathlee          #+#    #+#             */
/*   Updated: 2020/02/06 15:19:35 by dkathlee         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static void	float_to_str1(int sign, char **tmp2)
{
	char	*tmp;

	float_round(tmp2, ft_strlen(*tmp2));
	if (sign == 1)
	{
		tmp = *tmp2;
		*tmp2 = ft_strnew(ft_strlen(*tmp2) + 1);
		(*tmp2)[0] = '-';
		ft_strcpy(*tmp2 + 1, tmp);
		ft_memdel((void**)&tmp);
	}
}

char		*float_to_str(t_double f, t_printf *p)
{
	char	*tmp;
	char	*tmp2;
	char	*tmp3;
	int		itmp;

	tmp2 = ft_itoa_base(f.parts.mantisa, "0123456789");
	tmp = long_mul(tmp2, "2220446049250313080847263336181640625");
	ft_memdel((void**)&tmp2);
	itmp = 52 - ft_strlen(tmp);
	tmp2 = ft_strnew(ft_strlen(tmp) + itmp + 1);
	tmp2[0] = '1';
	ft_memset(tmp2 + 1, '0', itmp);
	ft_strcpy(tmp2 + itmp + 1, tmp);
	ft_memdel((void**)&tmp);
	if (f.parts.exponent >= 1023)
		tmp3 = long_pow("2", f.parts.exponent - 1023);
	else
		tmp3 = long_pow("5", 1023 - f.parts.exponent);
	tmp = long_mul(tmp2, tmp3);
	ft_memdel((void**)&tmp3);
	ft_memdel((void**)&tmp2);
	tmp2 = insert_point(tmp, ft_strlen(tmp), f.parts.exponent, p);
	ft_memdel((void**)&tmp);
	float_to_str1(f.parts.sign, &tmp2);
	return (tmp2);
}

char		*lfloat_to_str(t_ldouble f, t_printf *p)
{
	char	*tmp;
	char	*tmp2;
	char	*tmp3;
	int		itmp;

	tmp2 = ft_itoa_base(f.parts.mantisa, "0123456789");
	tmp = long_mul(tmp2, "108420217248550443400745280086994171142578125");
	ft_memdel((void**)&tmp2);
	itmp = 63 - ft_strlen(tmp);
	tmp2 = ft_strnew(ft_strlen(tmp) + itmp + 1);
	tmp2[0] = '1';
	ft_memset(tmp2 + 1, '0', itmp);
	ft_strcpy(tmp2 + itmp + 1, tmp);
	ft_memdel((void**)&tmp);
	if (f.parts.exponent >= 16383)
		tmp3 = long_pow("2", f.parts.exponent - 16383);
	else
		tmp3 = long_pow("5", 16383 - f.parts.exponent);
	tmp = long_mul(tmp2, tmp3);
	ft_memdel((void**)&tmp3);
	ft_memdel((void**)&tmp2);
	tmp2 = insert_point_long(tmp, ft_strlen(tmp), f.parts.exponent, p);
	ft_memdel((void**)&tmp);
	float_to_str1(f.parts.sign, &tmp2);
	return (tmp2);
}

t_double	get_float(t_printf *p)
{
	t_double	res;

	if (p->spec == sp_L)
		res.f = (double)va_arg(p->args, long double);
	else
		res.f = va_arg(p->args, double);
	return (res);
}

t_ldouble	get_lfloat(t_printf *p)
{
	t_ldouble	res;

	if (p->spec == sp_L)
		res.f = va_arg(p->args, long double);
	else
		res.f = va_arg(p->args, double);
	return (res);
}
