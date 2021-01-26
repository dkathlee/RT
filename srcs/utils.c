/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/14 16:39:47 by dkathlee          #+#    #+#             */
/*   Updated: 2020/09/10 14:33:18 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

void		handle_error(char *msg)
{
	ft_putendl(msg);
	exit(1);
}

uint32_t	clamp_u32(uint32_t d, uint32_t min, uint32_t max)
{
	uint32_t	t;

	t = d < min ? min : d;
	return (t > max ? max : t);
}

t_vec4		json_parse_vec3(cJSON *value)
{
	cJSON	*vec_x;
	cJSON	*vec_y;
	cJSON	*vec_z;
	t_vec4	vec;

	vec = (t_vec4) { 0, 0, 0, 0 };
	vec_x = cJSON_GetArrayItem(value, 0);
	vec_y = cJSON_GetArrayItem(value, 1);
	vec_z = cJSON_GetArrayItem(value, 2);
	if (vec_x != NULL && vec_y != NULL && vec_z != NULL)
	{
		vec = (t_vec4){.x = vec_x->valuedouble,
					.y = vec_y->valuedouble, .z = vec_z->valuedouble, 0};
	}
	else
		handle_error("Wrong vector in .json!");
	return (vec);
}

t_vec2		json_parse_vec2(cJSON *value)
{
	cJSON	*vec_x;
	cJSON	*vec_y;
	t_vec2	vec;

	vec = (t_vec2) { 0, 0 };
	vec_x = cJSON_GetArrayItem(value, 0);
	vec_y = cJSON_GetArrayItem(value, 1);
	if (vec_x != NULL && vec_y != NULL)
	{
		vec = (t_vec2){.x = vec_x->valuedouble,
					.y = vec_y->valuedouble};
	}
	else
		handle_error("Wrong vector in .json!");
	return (vec);
}
