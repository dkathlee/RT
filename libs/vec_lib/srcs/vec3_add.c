/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vec3_add.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dkathlee <dkathlee@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/05 15:05:23 by dkathlee          #+#    #+#             */
/*   Updated: 2020/09/11 15:23:00 by dkathlee         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vec_lib.h"

t_ivec3	ivec3_add_ivec3(t_ivec3 v1, t_ivec3 v2)
{
	return ((t_ivec3){v1.x + v2.x, v1.y + v2.y, v1.z + v2.z});
}

t_dvec3	dvec3_add_dvec3(t_dvec3 v1, t_dvec3 v2)
{
	return ((t_dvec3){v1.x + v2.x, v1.y + v2.y, v1.z + v2.z});
}

t_vec3	vec3_add_vec3(t_vec3 v1, t_vec3 v2)
{
	return ((t_vec3){v1.x + v2.x, v1.y + v2.y, v1.z + v2.z});
}
