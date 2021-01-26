/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   textures.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/30 09:52:27 by marvin            #+#    #+#             */
/*   Updated: 2020/09/30 09:52:27 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

static SDL_Surface	*load_texture(char *fname)
{
	SDL_Surface			*an_surf;
	SDL_Surface			*surf;
	SDL_PixelFormat		fmt;

	if ((an_surf = IMG_Load(fname)) == NULL)
		handle_error("Loading image error!");
	ft_memcpy(&fmt, an_surf->format, sizeof(SDL_PixelFormat));
	fmt.BytesPerPixel = 4;
	fmt.BitsPerPixel = 32;
	fmt.Rmask = RMASK;
	fmt.Gmask = GMASK;
	fmt.Bmask = BMASK;
	fmt.Amask = AMASK;
	if ((surf = SDL_ConvertSurface(an_surf, &fmt, an_surf->flags)) == NULL)
		handle_error("Surface convertation error");
	SDL_FreeSurface(an_surf);
	return (surf);
}

static void			send_texture_to_buffer(t_vulkan *v,
											SDL_Surface *surf,
											uint32_t offset)
{
	uint32_t	i;
	void		*data;

	i = 0;
	while (i < v->framebuffer.sc_image_count)
	{
		if (vkMapMemory(v->device, v->texture_buffers[i].dev_mem, 0,
							TEXTURES_BUFFER_SIZE, 0, &data) != VK_SUCCESS)
			handle_error("Map Memory error!");
		ft_memcpy((int*)data + offset, surf->pixels, surf->h * surf->pitch);
		vkUnmapMemory(v->device, v->texture_buffers[i].dev_mem);
		i++;
	}
}

static uint32_t		load_ui_texture(t_rt *r, t_vulkan *v)
{
	SDL_Surface	*surf;

	surf = load_texture("images/UI.png");
	send_texture_to_buffer(v, surf, 0);
	r->ui_texture.offset_in_buffer = 0;
	r->ui_texture.height = surf->h;
	r->ui_texture.width = surf->w;
	SDL_FreeSurface(surf);
	return (surf->h * surf->w);
}

void				vku_load_textures(t_rt *r, t_vulkan *v)
{
	SDL_Surface	*surf;
	uint32_t	i;
	uint32_t	j;
	uint32_t	current_offset;

	current_offset = load_ui_texture(r, v);
	i = -1;
	while (++i < r->n_textures)
	{
		surf = load_texture((r->texture_files)[i]);
		send_texture_to_buffer(v, surf, current_offset);
		j = -1;
		while (++j < r->n_fig)
			if ((r->sbo_figures)[j].texture.index == (int32_t)i)
			{
				r->sbo_figures[j].texture.offset_in_buffer = current_offset;
				r->sbo_figures[j].texture.height = surf->h;
				r->sbo_figures[j].texture.width = surf->w;
			}
		current_offset += surf->h * surf->w;
		SDL_FreeSurface(surf);
	}
}
