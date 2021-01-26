/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vec3_mul_n.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dkathlee <dkathlee@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/05 15:06:32 by dkathlee          #+#    #+#             */
/*   Updated: 2020/09/11 15:23:11 by dkathlee         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vec_lib.h"

t_ivec3	ivec3_mul_f(t_ivec3 v, float d)
{
	return ((t_ivec3){(int)(v.x * d), (int)(v.y * d), (int)(v.z * d)});
}

t_dvec3	dvec3_mul_d(t_dvec3 v, double d)
{
	return ((t_dvec3){v.x * d, v.y * d, v.z * d});
}

t_vec3	vec3_mul_f(t_vec3 v, float d)
{
	return ((t_vec3){v.x * d, v.y * d, v.z * d});
}
