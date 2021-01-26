/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dkathlee <dkathlee@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/03 16:57:14 by marvin            #+#    #+#             */
/*   Updated: 2020/09/11 15:21:50 by dkathlee         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_H
# define FT_PRINTF_H
# include <stdarg.h>
# include <stddef.h>
# include "libft.h"
# include "get_next_line.h"
# include <stdint.h>

typedef enum
{
	sp_none, sp_hh, sp_h, sp_l, sp_ll, sp_L, sp_j, sp_z, sp_t
}	t_spec;
typedef enum
{
	type_none, type_int = 1, type_char = 2, type_unsigned = 4, type_octal = 8,
	type_hex_low = 16, type_hex_high = 32, type_float = 64, type_pointer = 128,
	type_percent = 256, type_str = 512
}	t_type;
typedef union
{
	double					f;
	struct
	{
		unsigned long long	mantisa : 52;
		unsigned int		exponent : 11;
		unsigned int		sign : 1;
	}						parts;
}							t_double;
typedef union
{
	long double				f;
	struct
	{
		unsigned long long	mantisa : 63;
		char				q : 1;
		unsigned int		exponent : 15;
		unsigned int		sign : 1;
	}						parts;
}							t_ldouble;
typedef struct				s_flags
{
	t_uint8					minus;
	t_uint8					plus;
	t_uint8					space;
	t_uint8					hashtag;
	t_uint8					zero;
}							t_flags;
typedef struct				s_printf
{
	int						print_num;
	char					*print;
	t_flags					flags;
	t_spec					spec;
	t_type					type;
	int						width;
	int						precision;
	va_list					args;
}							t_printf;
char						*get_str_from_arg(t_printf *p);
void						set_flags(char **str, t_printf *p);
void						reset(t_printf *p);
int							is_flag(char c);
int							is_spec(char c);
int							is_type(char c);
int							check_str(char *str, char c);
void						check_wildcart(const char **f, t_printf *p);
void						check_flags_and_specs(const char **f, t_printf *p);
void						set_precision(char **str, t_printf *p);
int							set_width(char **str, t_printf *p);
void						set_minus(char **str, int cl, t_printf *p);
char						*float_to_str(t_double f, t_printf *p);
char						*lfloat_to_str(t_ldouble f, t_printf *p);
char						*long_mul(char *nb1, char *nb2);
char						*long_pow(char *nbr, int pow);
char						*insert_point(char *nbr, int len, int exp,
															t_printf *p);
char						*insert_point_long(char *nbr, int len, int exp,
															t_printf *p);
void						float_round(char **nbr, int len);
t_double					get_float(t_printf *p);
t_ldouble					get_lfloat(t_printf *p);
long						get_char(t_printf *p);
char						*char_to_str(int c);
char						*str_w(wchar_t *str, t_printf *p);
int							ft_printf(const char *format, ...);
#endif
