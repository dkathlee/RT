/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vec4_sub.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/18 08:11:52 by marvin            #+#    #+#             */
/*   Updated: 2020/08/18 08:17:51 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vec_lib.h"

t_ivec4		ivec4_sub_ivec4(t_ivec4 v1, t_ivec4 v2)
{
	return ((t_ivec4){v1.x - v2.x, v1.y - v2.y, v1.z - v2.z, v1.w - v2.w});
}

t_dvec4		dvec4_sub_dvec4(t_dvec4 v1, t_dvec4 v2)
{
	return ((t_dvec4){v1.x - v2.x, v1.y - v2.y, v1.z - v2.z, v1.w - v2.w});
}

t_vec4		vec4_sub_vec4(t_vec4 v1, t_vec4 v2)
{
	return ((t_vec4){v1.x - v2.x, v1.y - v2.y, v1.z - v2.z, v1.w - v2.w});
}
