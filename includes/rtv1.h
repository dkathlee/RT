/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rtv1.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/06 10:24:56 by celva             #+#    #+#             */
/*   Updated: 2020/10/01 22:34:47 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RTV1_H
# define RTV1_H
# ifdef __APPLE__
#  define VK_USE_PLATFORM_MACOS_MVK
#  define O_BINARY 0x0000
# elif _WIN32
#  define VK_USE_PLATFORM_WIN32_KHR
#  define SDL_MAIN_HANDLED
# else
#  define VK_USE_PLATFORM_XCB_KHR
#  define O_BINARY 0x0000
# endif
# include "SDL.h"
# include "SDL_image.h"
# include "SDL_vulkan.h"
# include "ft_printf.h"
# include "vku.h"
# include "cJSON.h"

# include <unistd.h>
# include <math.h>
# include <float.h>
# define WIN_WIDTH	1500
# define WIN_HEIGHT	1000
# define RAD(Value)		((Value) * 0.0174533)
# define ERROR_MEM_ALLOC "Memory Allocation Error"

typedef enum
{
	obj_null, obj_sphere, obj_plane, obj_cone, obj_cylinder,
	light_ambient, light_point, light_directional, camera
}	t_obj_type;

typedef struct	s_transform
{
	t_vec4		position;
	t_vec4		rotation;
}				t_transform;

typedef struct	s_texture
{
	uint32_t	offset_in_buffer;
	uint32_t	width;
	uint32_t	height;
	int32_t		index;
}				t_texture;

typedef struct	s_camera
{
	t_vec4		position;
	t_vec4		forward;
	t_vec4		up;
	t_vec4		right;
	t_vec4		background_color;
	float		d;
	float		vh;
	float		vw;
	float		fill_to_aligment[1];
}				t_camera;

typedef struct	s_rt_input
{
	t_camera	camera;
	float		win_width;
	float		win_height;
	uint32_t	n_fig;
	uint32_t	n_lig;
	t_texture	ui_texture;
}				t_rt_input;

typedef struct	s_object
{
	t_vec4		position;
	t_vec4		direction;
	t_vec4		f_ver;
	t_vec4		basis[3];
	t_vec4		color;
	t_texture	texture;
	t_vec2		f_tiling;
	t_vec2		f_offset;
	uint32_t	type;
	float		l_intensity;
	float		f_radius;
	float		f_height;
	float		f_metalness;
	float		f_transparency;
	float		f_reflection;
	float		f_refraction;
}				t_object;

typedef struct	s_rt
{
	t_camera	camera;
	float		win_width;
	float		win_height;
	uint32_t	n_fig;
	t_object	*sbo_figures;
	char		**texture_files;
	uint32_t	n_textures;
	uint32_t	n_lig;
	t_texture	ui_texture;
	t_object	*sbo_lights;
}				t_rt;

typedef struct	s_app
{
	t_vulkan	vulkan;
	SDL_Window	*window;
	char		*appname;
	t_rt		r;
}				t_app;

void			rtv_app_create(t_app *app);
void			rtv_app_run(t_app *app);
void			vku_instance_create(t_app *app);
void			vku_get_physical_device(t_vulkan *v);
void			vku_create_logical_device(t_vulkan *v);
void			vku_window_create(t_app *app);
void			vku_init_render(t_vulkan *v, t_rt *r);
void			vku_record_cmb(t_vulkan *v);
void			vku_draw_frame(t_vulkan *v);
void			vku_swapchain_create(t_vulkan *v, t_rt *r);
VkShaderModule	vku_create_shader_module(t_vulkan *v, char *code,
												uint32_t code_l);
void			vku_create_pipeline(t_vulkan *v);
void			vku_create_render_pass(t_vulkan *v);
void			vku_create_framebuffers(t_vulkan *v);
void			vku_create_command_buffers(t_vulkan *v);
void			vku_destroy_buffers(t_vulkan *v);
void			vku_load_textures(t_rt *r, t_vulkan *v);
void			read_scene(char *fname, t_rt *r);
size_t			load_shader_file(char *fname, char **shader);
void			draw_frame(t_vulkan *v, t_rt *r);
int				handling_keyboard_input(SDL_Event evt, t_camera *camera);
void			rotate_x(t_vec4 *t, float angle);
void			rotate_y(t_vec4 *t, float angle);
void			rotate_z(t_vec4 *t, float angle);
void			rotation_axis(t_vec4 *t, t_vec4 axis, double angle);
void			handle_error(char *msg);
uint32_t		clamp_u32(uint32_t d, uint32_t min, uint32_t max);
void			parse_camera_values(cJSON *camera, t_rt *r);
void			parse_cone_values(cJSON *json_cone, t_object *cone);
void			parse_cylinder_values(cJSON *json_object, t_object *object);
void			parse_directional_values(cJSON *json_object, t_object *light);
void			parse_optional_parameters(cJSON *json_object,
											t_object *object,
											t_rt *r);
void			parse_plane_values(cJSON *json_object, t_object *object);
void			parse_point_values(cJSON *json_object, t_object *light);
void			parse_ambient_values(cJSON *json_object, t_object *light);
void			parse_sphere_values(cJSON *json_object, t_object *object);
void			parse_texture(cJSON *json_object, t_object *object, t_rt *r);
int				parse_type(char *type);
void			check_cam_vectors(t_camera *c);
t_vec2			json_parse_vec2(cJSON *value);
t_vec4			json_parse_vec3(cJSON *value);
#endif
