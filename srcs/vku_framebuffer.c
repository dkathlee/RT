/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vku_framebufer.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/18 13:01:05 by marvin            #+#    #+#             */
/*   Updated: 2020/08/18 13:01:05 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

static VkImageViewCreateInfo	get_imageview_create_info(t_vulkan *v,
															uint32_t i)
{
	VkImageViewCreateInfo	res;

	res = (VkImageViewCreateInfo){
		.sType = VK_STRUCTURE_TYPE_IMAGE_VIEW_CREATE_INFO,
		.image = (v->framebuffer.sc_images)[i],
		.viewType = VK_IMAGE_VIEW_TYPE_2D,
		.format = v->phys_device.surface_formats->format,
		.subresourceRange = {
			.aspectMask = VK_IMAGE_ASPECT_COLOR_BIT,
			.baseMipLevel = 0,
			.levelCount = 1,
			.baseArrayLayer = 0,
			.layerCount = 1
		},
	};
	return (res);
}

void							vku_create_framebuffers(t_vulkan *v)
{
	VkImageViewCreateInfo	imageview_create_info;
	VkFramebufferCreateInfo	framebuffer_create_info;
	uint32_t				i;

	i = 0;
	while (i < v->framebuffer.sc_image_count)
	{
		imageview_create_info = get_imageview_create_info(v, i);
		if (vkCreateImageView(v->device, &imageview_create_info, 0,
						&((v->framebuffer.sc_image_views)[i])) != VK_SUCCESS)
			handle_error("ImageView creation error!");
		framebuffer_create_info = (VkFramebufferCreateInfo){
			.sType = VK_STRUCTURE_TYPE_FRAMEBUFFER_CREATE_INFO,
			.renderPass = v->renderpass,
			.attachmentCount = 1,
			.pAttachments = &((v->framebuffer.sc_image_views)[i]),
			.width = v->phys_device.surface_cap.currentExtent.width,
			.height = v->phys_device.surface_cap.currentExtent.height,
			.layers = 1
		};
		if (vkCreateFramebuffer(v->device, &framebuffer_create_info, 0,
							&((v->framebuffer.frame_buffers)[i])) != VK_SUCCESS)
			handle_error("Framebuffer creation error!");
		i++;
	}
}
