/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vec_mod.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dkathlee <dkathlee@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/05 15:01:31 by dkathlee          #+#    #+#             */
/*   Updated: 2020/08/05 15:13:26 by dkathlee         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vec_lib.h"

float			ivec3_mod(t_ivec3 v)
{
	return (sqrt((float)(v.x * v.x + v.y * v.y + v.z * v.z)));
}

double			dvec3_mod(t_dvec3 v)
{
	return (sqrt(v.x * v.x + v.y * v.y + v.z * v.z));
}

float			vec3_mod(t_vec3 v)
{
	return (sqrt(v.x * v.x + v.y * v.y + v.z * v.z));
}
