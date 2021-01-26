/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   scene_reader_json.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/23 20:29:13 by marvin            #+#    #+#             */
/*   Updated: 2020/11/23 20:29:13 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

static void	set_defaults(t_object *object)
{
	object->f_reflection = 0.0f;
	object->f_refraction = 1.517f;
	object->f_transparency = 0.0f;
	object->f_tiling = (t_vec2){ .x = 1, .y = 1 };
	object->f_offset = (t_vec2){ .x = 0, .y = 0 };
}

static void	set_values_figures(cJSON *object, t_object *cur_object)
{
	if (cur_object->type == obj_sphere)
		parse_sphere_values(object, cur_object);
	else if (cur_object->type == obj_cone)
		parse_cone_values(object, cur_object);
	else if (cur_object->type == obj_plane)
		parse_plane_values(object, cur_object);
	else if (cur_object->type == obj_cylinder)
		parse_cylinder_values(object, cur_object);
}

static void	parse_figures(cJSON *json, t_rt *r)
{
	cJSON		*object;
	t_object	*cur_object;
	cJSON		*type;

	object = cJSON_GetObjectItemCaseSensitive(json, "figures");
	if (object == NULL)
		handle_error("No figures in file!");
	r->n_fig = cJSON_GetArraySize(object);
	r->sbo_figures = ft_memalloc(sizeof(t_object) * r->n_fig);
	r->texture_files = ft_memalloc(sizeof(char*) * r->n_fig);
	object = object->child;
	cur_object = r->sbo_figures;
	while (object)
	{
		if ((type =
			cJSON_GetObjectItemCaseSensitive(object, "type")) == NULL ||
			(cur_object->type = (parse_type(type->valuestring))) == obj_null)
			handle_error("No type for object!");
		set_defaults(cur_object);
		set_values_figures(object, cur_object);
		parse_optional_parameters(object, cur_object, r);
		object = object->next;
		cur_object++;
	}
}

static void	parse_lights(t_rt *r, cJSON *json)
{
	cJSON		*object;
	t_object	*cur_object;
	cJSON		*type;

	object = cJSON_GetObjectItemCaseSensitive(json, "lights");
	object == NULL ? handle_error("No lights in file!") : 0;
	r->n_lig = cJSON_GetArraySize(object);
	r->sbo_lights = ft_memalloc(sizeof(t_object) * r->n_lig);
	object = object->child;
	cur_object = r->sbo_lights;
	while (object)
	{
		if ((type =
			cJSON_GetObjectItemCaseSensitive(object, "type")) == NULL ||
			(cur_object->type = (parse_type(type->valuestring))) == obj_null)
			handle_error("No type for light!");
		if (cur_object->type == light_point)
			parse_point_values(object, cur_object);
		else if (cur_object->type == light_directional)
			parse_directional_values(object, cur_object);
		else
			parse_ambient_values(object, cur_object);
		object = object->next;
		cur_object++;
	}
}

void		read_scene(char *fname, t_rt *r)
{
	int32_t		fd;
	char		buffer[64 * Kb];
	cJSON		*json;
	cJSON		*tmp;

	if (ft_strcmp(fname + ft_strlen(fname) - 5, ".json") != 0)
		handle_error("It is not .json file!");
	fd = open(fname, O_RDONLY);
	if (fd == -1)
		handle_error("Wrong file!");
	read(fd, buffer, 64 * Kb);
	json = cJSON_Parse(buffer);
	if (json == NULL || buffer[0] != '{')
		handle_error("Wrong .json file!");
	parse_figures(json, r);
	if ((tmp = cJSON_GetObjectItemCaseSensitive(json, "camera")) == NULL)
		handle_error("Error! File has no camera!");
	parse_camera_values(tmp, r);
	r->camera.right = vec4_cross(r->camera.up, r->camera.forward);
	parse_lights(r, json);
	cJSON_Delete(json);
}
