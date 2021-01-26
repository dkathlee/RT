/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   flags.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dkathlee <dkathlee@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/24 10:13:33 by dkathlee          #+#    #+#             */
/*   Updated: 2020/01/28 16:53:13 by dkathlee         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static void	set_plus(char **str, t_printf *p)
{
	char	*tmp;

	if (**str == '-')
		return ;
	tmp = ft_strnew(ft_strlen(*str) + 1);
	*tmp = p->flags.plus ? '+' : ' ';
	ft_strcpy(tmp + 1, *str);
	ft_memdel((void**)str);
	*str = tmp;
}

static void	set_hashtag(char **str, t_printf *p)
{
	char	*tmp;
	int		cl;

	cl = ft_strlen(*str);
	if (check_str(*str, '0') || (cl == 0 && p->type != type_octal)
							|| (**str == '0' && p->type == type_octal))
		return ;
	tmp = ft_strnew((p->type == type_octal) ? (cl + 1) : (cl + 2));
	tmp[0] = '0';
	tmp[1] = (p->type == type_hex_low) ? 'x' : 'X';
	ft_strcpy(tmp + ((p->type == type_octal) ? 1 : 2), *str);
	ft_memdel((void**)str);
	*str = tmp;
}

void		set_flags(char **str, t_printf *p)
{
	if (p->type == type_str || p->type == type_char)
		return ;
	if ((p->flags.plus || p->flags.space) &&
						(p->type & (type_float | type_int)) != 0)
		set_plus(str, p);
	if (p->flags.hashtag &&
			(p->type & (type_hex_high | type_hex_low | type_octal)) != 0)
		set_hashtag(str, p);
}

void		set_minus(char **str, int cl, t_printf *p)
{
	char	*tmp;

	tmp = ft_strnew(p->width);
	tmp = ft_strcpy(tmp, *str);
	ft_memset(tmp + cl, ' ', p->width - cl);
	ft_memdel((void**)str);
	*str = tmp;
}
