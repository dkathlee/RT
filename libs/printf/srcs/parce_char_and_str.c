/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parce_char_and_str.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/06 15:20:32 by dkathlee          #+#    #+#             */
/*   Updated: 2020/09/16 19:58:15 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

long		get_char(t_printf *p)
{
	long	res;

	if (p->type == type_percent)
		return ('%');
	if (p->spec == sp_l)
		res = (unsigned int)va_arg(p->args, unsigned int);
	else
		res = (char)va_arg(p->args, int);
	return (res);
}

static char	*char_to_str1(int c)
{
	char	*res;

	res = ft_strnew(4);
	res[0] = (c >> 18) + 240;
	res[1] = ((c >> 12) & 63) + 128;
	res[2] = ((c >> 6) & 63) + 128;
	res[3] = ((c & 63) + 128);
	return (res);
}

char		*char_to_str(int c)
{
	char	*res;

	if (c <= 127)
	{
		res = ft_strnew(1);
		res[0] = c;
	}
	if (c > 127 && c <= 2047)
	{
		res = ft_strnew(2);
		res[0] = (c >> 6) + 192;
		res[1] = ((c & 63) + 128);
	}
	if (c > 2047 && c <= 65535)
	{
		res = ft_strnew(3);
		res[0] = (c >> 12) + 224;
		res[1] = ((c >> 6) & 63) + 128;
		res[2] = ((c & 63) + 128);
	}
	if (c >= 65536)
		res = char_to_str1(c);
	return (res);
}

char		*str_w(wchar_t *str, t_printf *p)
{
	char	*res;
	char	*tmp;
	char	*tmp1;

	if ((res = ft_memalloc(1)) == NULL)
		exit(1);
	while (*str != '\0')
	{
		tmp = char_to_str((int)*str);
		if (((int)(ft_strlen(res) + ft_strlen(tmp)) > p->precision)
												&& p->precision != -1)
			break ;
		tmp1 = ft_strjoin(res, tmp);
		ft_memdel((void**)&res);
		res = tmp1;
		ft_memdel((void**)&tmp);
		str++;
	}
	return (res);
}
