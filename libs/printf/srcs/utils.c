/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dkathlee <dkathlee@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/24 10:17:24 by dkathlee          #+#    #+#             */
/*   Updated: 2020/02/06 16:07:02 by dkathlee         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void	reset(t_printf *p)
{
	p->flags = (t_flags){FALSE, FALSE, FALSE, FALSE, FALSE};
	p->precision = -1;
	p->width = -1;
	p->spec = sp_none;
	p->type = type_none;
}

int		is_flag(char c)
{
	if (c == '+' || c == '-' || c == ' ' || c == '0' || c == '#')
		return (TRUE);
	return (FALSE);
}

int		is_spec(char c)
{
	if (c == 'h' || c == 'l' || c == 'L' || c == 'j' || c == 'z' || c == 't')
		return (TRUE);
	return (FALSE);
}

int		is_type(char c)
{
	if (c == 'd' || c == 'i' || c == 'u' || c == 'o' || c == 'x' || c == 'X'
		|| c == 'f' || c == 'F' || c == 'c' || c == 's' || c == 'p' || c == '%'
		|| c == 'D' || c == 'I' || c == 'U')
		return (TRUE);
	return (FALSE);
}

int		check_str(char *str, char c)
{
	if (!*str)
		return (FALSE);
	while (*str)
		if (*str++ != c)
			return (FALSE);
	return (TRUE);
}
