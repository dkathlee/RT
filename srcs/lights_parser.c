/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lights_parser.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/17 13:58:02 by celva             #+#    #+#             */
/*   Updated: 2021/01/17 13:58:02 by celva            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

void		parse_point_values(cJSON *json_object, t_object *light)
{
	cJSON *value;

	if ((value =
		cJSON_GetObjectItemCaseSensitive(json_object, "intensity")) != NULL)
		light->l_intensity = value->valuedouble;
	else
		handle_error("Error! Light point has no intensity!");
	if ((value =
		cJSON_GetObjectItemCaseSensitive(json_object, "position")) != NULL)
		light->position = json_parse_vec3(value);
	else
		handle_error("Error! Light point has no position!");
}

void		parse_directional_values(cJSON *json_object, t_object *light)
{
	cJSON *value;

	if ((value =
		cJSON_GetObjectItemCaseSensitive(json_object, "intensity")) != NULL)
		light->l_intensity = value->valuedouble;
	else
		handle_error("Error! Light point has no intensity!");
	if ((value =
		cJSON_GetObjectItemCaseSensitive(json_object, "direction")) != NULL)
		light->direction = json_parse_vec3(value);
	else
		handle_error("Error! Light point has no direction!");
}

void		parse_ambient_values(cJSON *json_object, t_object *light)
{
	cJSON *value;

	if ((value =
		cJSON_GetObjectItemCaseSensitive(json_object, "intensity")) != NULL)
		light->l_intensity = value->valuedouble;
	else
		handle_error("Error! Light point has no intensity!");
}
