/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vec4_cross.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/18 07:55:34 by marvin            #+#    #+#             */
/*   Updated: 2020/08/18 08:08:22 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vec_lib.h"

t_dvec4	dvec4_cross(t_dvec4 v1, t_dvec4 v2)
{
	return ((t_dvec4){v1.y * v2.z - v1.z * v2.y,
						v1.z * v2.x - v1.x * v2.z,
						v1.x * v2.y - v1.y * v2.x, 1});
}

t_ivec4	ivec4_cross(t_ivec4 v1, t_ivec4 v2)
{
	return ((t_ivec4){v1.y * v2.z - v1.z * v2.y,
						v1.z * v2.x - v1.x * v2.z,
						v1.x * v2.y - v1.y * v2.x, 1});
}

t_vec4	vec4_cross(t_vec4 v1, t_vec4 v2)
{
	return ((t_vec4){(double)v1.y * (double)v2.z - (double)v1.z * (double)v2.y,
				(double)v1.z * (double)v2.x - (double)v1.x * (double)v2.z,
				(double)v1.x * (double)v2.y - (double)v1.y * (double)v2.x, 1});
}
