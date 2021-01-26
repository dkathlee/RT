/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vec4_mul_n.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dkathlee <dkathlee@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/18 08:22:38 by marvin            #+#    #+#             */
/*   Updated: 2020/09/11 15:23:31 by dkathlee         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vec_lib.h"

t_ivec4	ivec4_mul_f(t_ivec4 v, float d)
{
	return ((t_ivec4){(int)(v.x * d), (int)(v.y * d),
						(int)(v.z * d), (int)(v.w * d)});
}

t_dvec4	dvec4_mul_d(t_dvec4 v, double d)
{
	return ((t_dvec4){v.x * d, v.y * d, v.z * d, v.w * d});
}

t_vec4	vec4_mul_f(t_vec4 v, float d)
{
	return ((t_vec4){v.x * d, v.y * d, v.z * d, v.w * d});
}
