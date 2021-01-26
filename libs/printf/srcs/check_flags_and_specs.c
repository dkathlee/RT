/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_flags_and_specs.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dkathlee <dkathlee@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/06 14:07:47 by dkathlee          #+#    #+#             */
/*   Updated: 2020/09/11 15:19:36 by dkathlee         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static void	parcing_format1(const char **f, t_printf *p)
{
	if (ft_isupper(**f) && **f != 'X')
	{
		if (**f == 'C' || **f == 'S')
			p->spec = sp_l;
		else
			p->spec = (**f == 'F') ? sp_L : sp_ll;
	}
	if (p->type != type_none)
		(*f)++;
}

void		parcing_format(const char **f, t_printf *p)
{
	if (**f == 'd' || **f == 'i' || **f == 'D' || **f == 'I')
		p->type = type_int;
	else if (**f == 'u' || **f == 'U')
		p->type = type_unsigned;
	else if (**f == 'o' || **f == 'O')
		p->type = type_octal;
	else if (**f == 'x')
		p->type = type_hex_low;
	else if (**f == 'X')
		p->type = type_hex_high;
	else if (**f == 'f')
		p->type = type_float;
	else if (**f == 'c' || **f == 'C')
		p->type = type_char;
	else if (**f == 's' || **f == 'S')
		p->type = type_str;
	else if (**f == 'p')
		p->type = type_pointer;
	else if (**f == '%')
		p->type = type_percent;
	parcing_format1(f, p);
}

static void	check_flags1(const char *f, t_printf *p)
{
	if (*f == 'j' && p->spec < sp_j)
		p->spec = sp_j;
	else if (*f == 'z' && p->spec < sp_z)
		p->spec = sp_z;
	else if (*f == 't' && p->spec < sp_t)
		p->spec = sp_t;
	else if (*f == 'L')
		p->spec = sp_L;
}

void		check_flags(const char *f, t_printf *p)
{
	if (*f == '#')
		p->flags.hashtag = TRUE;
	else if (*f == '-')
		p->flags.minus = TRUE;
	else if (*f == '+')
		p->flags.plus = TRUE;
	else if (*f == ' ')
		p->flags.space = TRUE;
	else if (*f == '0')
		p->flags.zero = TRUE;
	if (*f == 'h' && *(f + 1) == 'h' && p->spec < sp_hh)
		p->spec = sp_hh;
	else if (*f == 'h' && *(f + 1) != 'h' && *(f - 1) != 'h' && p->spec < sp_h)
		p->spec = sp_h;
	else if (*f == 'l' && *(f + 1) != 'l' && p->spec < sp_l)
		p->spec = sp_l;
	else if (*f == 'l' && *(f + 1) == 'l' && p->spec < sp_ll)
		p->spec = sp_ll;
	else
		check_flags1(f, p);
}

void		check_flags_and_specs(const char **f, t_printf *p)
{
	while (**f && (is_flag(**f) || is_spec(**f) ||
				ft_isdigit(**f) || **f == '.' || **f == '*'))
	{
		check_flags(*f, p);
		check_wildcart(f, p);
		if (**f > '0' && **f <= '9')
		{
			p->width = ft_atoi(*f);
			while (ft_isdigit(**f))
				(*f)++;
		}
		else if (**f == '.')
		{
			(*f)++;
			p->precision = (p->precision == -1) ? ft_atoi(*f) : p->precision;
			while (ft_isdigit(**f))
				(*f)++;
		}
		else
			(*f)++;
	}
	parcing_format(f, p);
}
