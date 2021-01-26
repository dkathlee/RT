/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_wildcart.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dkathlee <dkathlee@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/11 15:19:17 by dkathlee          #+#    #+#             */
/*   Updated: 2020/09/11 15:19:39 by dkathlee         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void		check_wildcart(const char **f, t_printf *p)
{
	if (**f == '*' && *(*f + 1))
	{
		p->width = va_arg(p->args, int);
		if (p->width < 0)
		{
			p->flags.minus = TRUE;
			p->width = -(p->width);
		}
	}
	else if (**f == '.' && *(*f + 1) == '*')
	{
		p->precision = va_arg(p->args, int);
		if (p->precision < 0)
			p->precision = -1;
		(*f)++;
	}
}
