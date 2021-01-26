/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vec4_add.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dkathlee <dkathlee@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/18 07:49:31 by marvin            #+#    #+#             */
/*   Updated: 2020/09/11 15:23:36 by dkathlee         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vec_lib.h"

t_ivec4	ivec4_add_ivec4(t_ivec4 v1, t_ivec4 v2)
{
	return ((t_ivec4){v1.x + v2.x, v1.y + v2.y, v1.z + v2.z, v1.w + v2.w});
}

t_dvec4	dvec4_add_dvec4(t_dvec4 v1, t_dvec4 v2)
{
	return ((t_dvec4){v1.x + v2.x, v1.y + v2.y, v1.z + v2.z, v1.w + v2.w});
}

t_vec4	vec4_add_vec4(t_vec4 v1, t_vec4 v2)
{
	return ((t_vec4){v1.x + v2.x, v1.y + v2.y, v1.z + v2.z, v1.w + v2.w});
}
