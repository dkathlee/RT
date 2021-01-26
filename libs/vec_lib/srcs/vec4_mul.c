/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vec4_mul.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dkathlee <dkathlee@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/18 08:09:55 by marvin            #+#    #+#             */
/*   Updated: 2020/09/11 15:23:25 by dkathlee         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vec_lib.h"

t_ivec4	ivec4_mul_ivec4(t_ivec4 v1, t_ivec4 v2)
{
	return ((t_ivec4){v1.x * v2.x, v1.y * v2.y, v1.z * v2.z, v1.w * v2.w});
}

t_dvec4	dvec4_mul_dvec4(t_dvec4 v1, t_dvec4 v2)
{
	return ((t_dvec4){v1.x * v2.x, v1.y * v2.y, v1.z * v2.z, v1.w * v2.w});
}

t_vec4	vec4_mul_vec4(t_vec4 v1, t_vec4 v2)
{
	return ((t_vec4){v1.x * v2.x, v1.y * v2.y, v1.z * v2.z, v1.w * v2.w});
}
