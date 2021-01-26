/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   objects_parser.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/17 13:49:28 by celva             #+#    #+#             */
/*   Updated: 2021/01/17 13:49:28 by celva            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

void		parse_sphere_values(cJSON *json_object, t_object *object)
{
	cJSON *value;

	if ((value =
		cJSON_GetObjectItemCaseSensitive(json_object, "position")) != NULL)
		object->position = json_parse_vec3(value);
	else
		handle_error("Error! Sphere has no position!");
	if ((value =
		cJSON_GetObjectItemCaseSensitive(json_object, "radius")) != NULL)
		object->f_radius = value->valuedouble;
	else
		handle_error("Error! Sphere has no radius!");
}

void		parse_cone_values(cJSON *json_cone, t_object *cone)
{
	cJSON *value;

	if ((value =
		cJSON_GetObjectItemCaseSensitive(json_cone, "position")) != NULL)
		cone->position = json_parse_vec3(value);
	else
		handle_error("Error! Cone has no position!");
	if ((value =
		cJSON_GetObjectItemCaseSensitive(json_cone, "direction")) != NULL)
		cone->direction = json_parse_vec3(value);
	else
		handle_error("Error! Cone has no direction!");
	if ((value =
		cJSON_GetObjectItemCaseSensitive(json_cone, "radius")) != NULL)
		cone->f_radius = value->valuedouble;
	else
		handle_error("Error! Cone has no radius!");
	if ((value =
		cJSON_GetObjectItemCaseSensitive(json_cone, "height")) != NULL)
		cone->f_height = value->valuedouble;
	else
		handle_error("Error! Cone has no height!");
}

void		parse_plane_values(cJSON *json_object, t_object *object)
{
	cJSON *value;

	if ((value =
		cJSON_GetObjectItemCaseSensitive(json_object, "position")) != NULL)
		object->position = json_parse_vec3(value);
	else
		handle_error("Error! Plane has no position!");
	if ((value =
		cJSON_GetObjectItemCaseSensitive(json_object, "direction")) != NULL)
		object->direction = json_parse_vec3(value);
	else
		handle_error("Error! Plane has no direction!");
}

void		parse_cylinder_values(cJSON *json_object, t_object *object)
{
	cJSON *value;

	if ((value =
		cJSON_GetObjectItemCaseSensitive(json_object, "position")) != NULL)
		object->position = json_parse_vec3(value);
	else
		handle_error("Error! Cylinder has no position!");
	if ((value =
		cJSON_GetObjectItemCaseSensitive(json_object, "direction")) != NULL)
		object->direction = json_parse_vec3(value);
	else
		handle_error("Error! Cylinder has no direction!");
	if ((value =
		cJSON_GetObjectItemCaseSensitive(json_object, "radius")) != NULL)
		object->f_radius = value->valuedouble;
	else
		handle_error("Error! Cylinder has no radius!");
}

void		parse_camera_values(cJSON *camera, t_rt *r)
{
	cJSON *value;

	if ((value =
		cJSON_GetObjectItemCaseSensitive(camera, "position")) != NULL)
		r->camera.position = json_parse_vec3(value);
	else
		handle_error("Error! Camera has no position!");
	if ((value =
		cJSON_GetObjectItemCaseSensitive(camera, "forward")) != NULL)
		r->camera.forward = json_parse_vec3(value);
	else
		handle_error("Error! Camera has no forward!");
	if ((value =
		cJSON_GetObjectItemCaseSensitive(camera, "up")) != NULL)
		r->camera.up = json_parse_vec3(value);
	else
		handle_error("Error! Camera has no up!");
	if ((value =
		cJSON_GetObjectItemCaseSensitive(camera,
										"background_color")) != NULL)
		r->camera.background_color = json_parse_vec3(value);
	else
		r->camera.background_color = (t_vec4) { 1.0, 1.0, 1.0, 1.0};
}
