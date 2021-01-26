/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/01 18:56:35 by celva             #+#    #+#             */
/*   Updated: 2020/09/16 13:39:19 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

static int	keyboard_input_right_left(SDL_Event evt, t_camera *camera)
{
	if (evt.key.keysym.sym == SDLK_LEFT)
	{
		camera->position = vec4_add_vec4(camera->position,
				vec4_mul_f(vec4_cross(camera->forward, camera->up), 0.1f));
		return (0);
	}
	if (evt.key.keysym.sym == SDLK_RIGHT)
	{
		camera->position = vec4_add_vec4(camera->position,
				vec4_mul_f(vec4_cross(camera->forward, camera->up), -0.1f));
		return (0);
	}
	return (-1);
}

static int	keyboard_input_up_down(SDL_Event evt, t_camera *camera)
{
	if (evt.key.keysym.sym == SDLK_UP)
	{
		camera->position = vec4_add_vec4(camera->position,
										vec4_mul_f(camera->forward, 0.1f));
		return (0);
	}
	if (evt.key.keysym.sym == SDLK_DOWN)
	{
		camera->position = vec4_sub_vec4(camera->position,
										vec4_mul_f(camera->forward, 0.1f));
		return (0);
	}
	return (-1);
}

static int	keyboard_input_q_e_a_d(SDL_Event evt, t_camera *camera)
{
	if (evt.key.keysym.sym == SDLK_a)
	{
		rotation_axis(&(camera->forward), camera->up, RAD(10));
		rotation_axis(&(camera->right), camera->up, RAD(10));
		return (0);
	}
	if (evt.key.keysym.sym == SDLK_d)
	{
		rotation_axis(&(camera->forward), camera->up, RAD(-10));
		rotation_axis(&(camera->right), camera->up, RAD(-10));
		return (0);
	}
	if (evt.key.keysym.sym == SDLK_q)
	{
		rotation_axis(&(camera->up), camera->forward, RAD(-10));
		rotation_axis(&(camera->right), camera->forward, RAD(-10));
		return (0);
	}
	if (evt.key.keysym.sym == SDLK_e)
	{
		rotation_axis(&(camera->up), camera->forward, RAD(10));
		rotation_axis(&(camera->right), camera->forward, RAD(10));
		return (0);
	}
	return (-1);
}

static int	keyboard_input_w_s(SDL_Event evt, t_camera *camera)
{
	if (evt.key.keysym.sym == SDLK_w)
	{
		rotation_axis(&(camera->forward), camera->right, RAD(-10));
		rotation_axis(&(camera->up), camera->right, RAD(-10));
		return (0);
	}
	if (evt.key.keysym.sym == SDLK_s)
	{
		rotation_axis(&(camera->forward), camera->right, RAD(10));
		rotation_axis(&(camera->up), camera->right, RAD(10));
		return (0);
	}
	return (-1);
}

int			handling_keyboard_input(SDL_Event evt, t_camera *camera)
{
	if ((keyboard_input_up_down(evt, camera) == 0) ||
		(keyboard_input_right_left(evt, camera) == 0) ||
		(keyboard_input_q_e_a_d(evt, camera) == 0) ||
		(keyboard_input_w_s(evt, camera) == 0))
	{
		return (0);
	}
	else if (evt.key.keysym.sym == SDLK_ESCAPE)
		exit(0);
	return (1);
}
