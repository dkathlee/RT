/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   percent.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dkathlee <dkathlee@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/24 10:22:41 by dkathlee          #+#    #+#             */
/*   Updated: 2020/02/06 14:51:43 by dkathlee         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static char	*set_precision1(char **str, t_printf *p, int cl, char zn)
{
	char	*tmp;

	tmp = NULL;
	if (p->precision > cl && p->type == type_pointer)
	{
		tmp = ft_strnew(p->precision + 2);
		ft_strncpy(tmp, *str, 2);
		ft_memset(tmp + 2, '0', p->precision - cl + 2);
		ft_strncpy(tmp + p->precision + 4 - cl, *str + 2, cl - 2);
	}
	else if (p->precision > cl - (zn ? 1 : 0) && p->type != type_str)
	{
		tmp = ft_strnew(zn ? (p->precision + 1) : p->precision);
		if (zn)
			tmp[0] = **str;
		ft_memset(zn ? (tmp + 1) : tmp, '0', p->precision - cl + (zn ? 1 : 0));
		zn ? ft_strcpy(tmp + p->precision - cl + 2, *str + 1) :
				ft_strcpy(tmp + p->precision - cl, *str);
	}
	else if (p->precision == 0 && **str == '0' && p->type != type_pointer)
		tmp = ft_strnew(0);
	return (tmp);
}

void		set_precision(char **str, t_printf *p)
{
	char	*tmp;
	int		cl;
	char	zn;

	if ((p->type & (type_char | type_percent | type_float))
							|| p->precision == -1)
		return ;
	cl = ft_strlen(*str);
	cl = (cl == 0) ? 1 : cl;
	zn = (**str == '-') ? TRUE : FALSE;
	if (p->type == type_str && cl > p->precision && p->precision != -1)
	{
		tmp = ft_strnew(p->precision);
		ft_strncpy(tmp, *str, p->precision);
	}
	else if ((tmp = set_precision1(str, p, cl, zn)) == NULL)
		return ;
	ft_memdel((void**)str);
	*str = tmp;
}

static void	set_width1(char **str, t_printf *p, int cur_len)
{
	char	*tmp;

	tmp = ft_strnew(p->width);
	if ((**str == '+' || **str == '-' || p->flags.space) && p->flags.zero &&
	p->precision == -1 && (p->type & (type_float | type_int | type_unsigned)))
	{
		tmp[0] = **str;
		ft_memset(tmp + 1, '0', p->width - cur_len);
		ft_strcpy(tmp + p->width - cur_len + 1, *str + 1);
	}
	else if (**str == '0' && ft_tolower(*(*str + 1)) == 'x' && p->flags.zero
		&& (p->type & (type_hex_high | type_hex_low)) && p->precision == -1)
	{
		ft_strncpy(tmp, *str, 2);
		ft_memset(tmp + 2, '0', p->width - cur_len);
		ft_strcpy(tmp + p->width - cur_len + 2, *str + 2);
	}
	else
	{
		ft_memset(tmp, (p->flags.zero && p->precision == -1) ?
								'0' : ' ', p->width - cur_len);
		ft_strcpy(tmp + p->width - cur_len, *str);
	}
	ft_memdel((void**)str);
	*str = tmp;
}

int			set_width(char **str, t_printf *p)
{
	int		cur_len;

	cur_len = ft_strlen(*str);
	cur_len = (cur_len == 0 && p->type == type_char) ? 1 : cur_len;
	if (cur_len >= p->width)
		return (cur_len);
	if (p->flags.minus)
		set_minus(str, cur_len, p);
	else
		set_width1(str, p, cur_len);
	return (p->width);
}
