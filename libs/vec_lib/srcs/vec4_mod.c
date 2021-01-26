/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vec4_mod.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/18 08:09:03 by marvin            #+#    #+#             */
/*   Updated: 2020/08/18 08:09:05 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vec_lib.h"

float			ivec4_mod(t_ivec4 v)
{
	return (sqrt((float)(v.x * v.x + v.y * v.y + v.z * v.z + v.w * v.w)));
}

double			dvec4_mod(t_dvec4 v)
{
	return (sqrt(v.x * v.x + v.y * v.y + v.z * v.z + v.w * v.w));
}

float			vec4_mod(t_vec4 v)
{
	return (sqrt(v.x * v.x + v.y * v.y + v.z * v.z + v.w * v.w));
}
