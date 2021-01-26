/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rotation.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dkathlee <dkathlee@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/01 19:35:49 by celva             #+#    #+#             */
/*   Updated: 2020/09/11 16:14:32 by dkathlee         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

void				rotation_axis(t_vec4 *t, t_vec4 axis, double angle)
{
	t_dvec4	res;
	float	c;
	float	s;

	c = cos(angle);
	s = sin(angle);
	res.x = t->x * (c + axis.x * axis.x * (1 - c)) + t->y *
					(axis.y * axis.x * (1 - c) + axis.z * s) + t->z *
					(axis.z * axis.x * (1 - c) - axis.y * s);
	res.y = t->x * (axis.x * axis.y * (1 - c) - axis.z * s) + t->y *
					(c + axis.y * axis.y * (1 - c)) + t->z *
					(axis.z * axis.y * (1 - c) + axis.x * s);
	res.z = t->x * (axis.x * axis.z * (1 - c) + axis.y * s) + t->y *
					(axis.y * axis.z * (1 - c) - axis.x * s) + t->z *
					(c + axis.z * axis.z * (1 - c));
	*t = (t_vec4) { .x = res.x, .y = res.y, .z = res.z, .w = 0 };
}
