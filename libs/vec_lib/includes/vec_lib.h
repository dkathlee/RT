/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vec_lib.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dkathlee <dkathlee@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/11 15:25:15 by dkathlee          #+#    #+#             */
/*   Updated: 2020/09/11 15:25:30 by dkathlee         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef VEC_LIB_H
# define VEC_LIB_H
# include <math.h>
# include <stdint.h>

typedef struct	s_ivec2
{
	int32_t		x;
	int32_t		y;
}				t_ivec2;

typedef struct	s_dvec2
{
	double		x;
	double		y;
}				t_dvec2;

typedef struct	s_vec2
{
	float		x;
	float		y;
}				t_vec2;

typedef struct	s_ivec3
{
	int32_t		x;
	int32_t		y;
	int32_t		z;
}				t_ivec3;

typedef struct	s_dvec3
{
	double		x;
	double		y;
	double		z;
}				t_dvec3;

typedef struct	s_vec3
{
	float		x;
	float		y;
	float		z;
}				t_vec3;

typedef struct	s_ivec4
{
	int32_t		x;
	int32_t		y;
	int32_t		z;
	int32_t		w;
}				t_ivec4;

typedef struct	s_dvec4
{
	float		x;
	float		y;
	float		z;
	float		w;
}				t_dvec4;
typedef struct	s_vec4
{
	float		x;
	float		y;
	float		z;
	float		w;
}				t_vec4;

float			ivec3_mod(t_ivec3 v);
double			dvec3_mod(t_dvec3 v);
float			vec3_mod(t_vec3 v);
float			ivec4_mod(t_ivec4 v);
double			dvec4_mod(t_dvec4 v);
float			vec4_mod(t_vec4 v);
t_ivec3			ivec3_sub_ivec3(t_ivec3 v1, t_ivec3 v2);
t_dvec3			dvec3_sub_dvec3(t_dvec3 v1, t_dvec3 v2);
t_vec3			vec3_sub_vec3(t_vec3 v1, t_vec3 v2);
t_ivec4			ivec4_sub_ivec4(t_ivec4 v1, t_ivec4 v2);
t_dvec4			dvec4_sub_dvec4(t_dvec4 v1, t_dvec4 v2);
t_vec4			vec4_sub_vec4(t_vec4 v1, t_vec4 v2);
t_ivec3			ivec3_add_ivec3(t_ivec3 v1, t_ivec3 v2);
t_dvec3			dvec3_add_dvec3(t_dvec3 v1, t_dvec3 v2);
t_vec3			vec3_add_vec3(t_vec3 v1, t_vec3 v2);
t_ivec4			ivec4_add_ivec4(t_ivec4 v1, t_ivec4 v2);
t_dvec4			dvec4_add_dvec4(t_dvec4 v1, t_dvec4 v2);
t_vec4			vec4_add_vec4(t_vec4 v1, t_vec4 v2);
t_ivec3			ivec3_mul_ivec3(t_ivec3 v1, t_ivec3 v2);
t_dvec3			dvec3_mul_dvec3(t_dvec3 v1, t_dvec3 v2);
t_vec3			vec3_mul_vec3(t_vec3 v1, t_vec3 v2);
t_ivec4			ivec4_mul_ivec4(t_ivec4 v1, t_ivec4 v2);
t_dvec4			dvec4_mul_dvec4(t_dvec4 v1, t_dvec4 v2);
t_vec4			vec4_mul_vec4(t_vec4 v1, t_vec4 v2);
t_ivec3			ivec3_mul_f(t_ivec3 v, float d);
t_dvec3			dvec3_mul_d(t_dvec3 v, double d);
t_vec3			vec3_mul_f(t_vec3 v, float d);
t_ivec4			ivec4_mul_f(t_ivec4 v, float d);
t_dvec4			dvec4_mul_d(t_dvec4 v, double d);
t_vec4			vec4_mul_f(t_vec4 v, float d);
float			ivec3_scalar(t_ivec3 v1, t_ivec3 v2);
double			dvec3_scalar(t_dvec3 v1, t_dvec3 v2);
float			vec3_scalar(t_vec3 v1, t_vec3 v2);
float			ivec4_scalar(t_ivec4 v1, t_ivec4 v2);
double			dvec4_scalar(t_dvec4 v1, t_dvec4 v2);
float			vec4_scalar(t_vec4 v1, t_vec4 v2);
t_ivec3			ivec3_cross(t_ivec3 v1, t_ivec3 v2);
t_dvec3			dvec3_cross(t_dvec3 v1, t_dvec3 v2);
t_vec3			vec3_cross(t_vec3 v1, t_vec3 v2);
t_ivec4			ivec4_cross(t_ivec4 v1, t_ivec4 v2);
t_dvec4			dvec4_cross(t_dvec4 v1, t_dvec4 v2);
t_vec4			vec4_cross(t_vec4 v1, t_vec4 v2);
#endif
