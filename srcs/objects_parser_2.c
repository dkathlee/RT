/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   objects_parser_2.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/18 22:08:49 by marvin            #+#    #+#             */
/*   Updated: 2021/01/18 22:08:49 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

int					parse_type(char *type)
{
	if (ft_strcmp(type, "sphere") == 0)
		return (obj_sphere);
	else if (ft_strcmp(type, "plane") == 0)
		return (obj_plane);
	else if (ft_strcmp(type, "cone") == 0)
		return (obj_cone);
	else if (ft_strcmp(type, "cylinder") == 0)
		return (obj_cylinder);
	else if (ft_strcmp(type, "point") == 0)
		return (light_point);
	else if (ft_strcmp(type, "directional") == 0)
		return (light_directional);
	else if (ft_strcmp(type, "ambient") == 0)
		return (light_ambient);
	return (obj_null);
}

static int32_t		texture_index(char *texture_fname, t_rt *r)
{
	uint32_t	index;

	if (ft_strcmp(texture_fname, "chess") == 0)
		return (-1);
	if (ft_strcmp(texture_fname, "perlin") == 0)
		return (-2);
	if (ft_strcmp(texture_fname, "wave") == 0)
		return (-3);
	index = 0;
	while (index < r->n_textures)
	{
		if (ft_strcmp(r->texture_files[index], texture_fname) == 0)
			return (index);
		index++;
	}
	return (index);
}

void				parse_texture(cJSON *json_object, t_object *object, t_rt *r)
{
	cJSON	*value;

	if ((value =
		cJSON_GetObjectItemCaseSensitive(json_object, "texture")) == NULL)
	{
		object->texture.index = -4;
		return ;
	}
	object->texture.index = texture_index(value->valuestring, r);
	if (object->texture.index == (int32_t)r->n_textures)
	{
		r->texture_files[r->n_textures] =
						ft_strjoin("images/", value->valuestring);
		r->n_textures++;
	}
}

void				parse_optional_parameters(cJSON *json_object,
												t_object *object,
												t_rt *r)
{
	cJSON *value;

	if ((value =
		cJSON_GetObjectItemCaseSensitive(json_object, "color")) != NULL)
		object->color = json_parse_vec3(value);
	if ((value =
		cJSON_GetObjectItemCaseSensitive(json_object, "metalness")) != NULL)
		object->f_metalness = value->valueint;
	if ((value =
		cJSON_GetObjectItemCaseSensitive(json_object, "reflection")) != NULL)
		object->f_reflection = value->valuedouble;
	if ((value =
		cJSON_GetObjectItemCaseSensitive(json_object, "refraction")) != NULL)
		object->f_refraction = value->valuedouble;
	if ((value =
		cJSON_GetObjectItemCaseSensitive(json_object, "transparency")) != NULL)
		object->f_transparency = value->valuedouble;
	parse_texture(json_object, object, r);
	if ((value =
		cJSON_GetObjectItemCaseSensitive(json_object, "tiling")) != NULL)
		object->f_tiling = json_parse_vec2(value);
	if ((value =
		cJSON_GetObjectItemCaseSensitive(json_object, "offset")) != NULL)
		object->f_offset = json_parse_vec2(value);
}
