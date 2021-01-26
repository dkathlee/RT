/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vec4_scalar.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/18 08:11:03 by marvin            #+#    #+#             */
/*   Updated: 2020/08/18 08:11:05 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vec_lib.h"

float	ivec4_scalar(t_ivec4 v1, t_ivec4 v2)
{
	return ((float)(v1.x * v2.x + v1.y * v2.y + v1.z * v2.z + v1.w * v2.w));
}

double	dvec4_scalar(t_dvec4 v1, t_dvec4 v2)
{
	return (v1.x * v2.x + v1.y * v2.y + v1.z * v2.z + v1.w * v2.w);
}

float	vec4_scalar(t_vec4 v1, t_vec4 v2)
{
	return (v1.x * v2.x + v1.y * v2.y + v1.z * v2.z + v1.w * v2.w);
}
