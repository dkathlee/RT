/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vku_swapchain.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/06 01:11:01 by dkathlee          #+#    #+#             */
/*   Updated: 2020/09/14 01:41:30 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

VkPresentModeKHR	vku_get_present_mode(t_vulkan *v)
{
	VkPresentModeKHR			*pres_modes;
	uint32_t					pres_mode_count;
	VkPresentModeKHR			present_mode;
	uint32_t					i;

	vkGetPhysicalDeviceSurfacePresentModesKHR(v->phys_device.device,
											v->surface, &pres_mode_count, NULL);
	if ((pres_modes = ft_memalloc(sizeof(VkPresentModeKHR) * pres_mode_count))
																		== NULL)
		handle_error(ERROR_MEM_ALLOC);
	vkGetPhysicalDeviceSurfacePresentModesKHR(v->phys_device.device, v->surface,
												&pres_mode_count, pres_modes);
	present_mode = VK_PRESENT_MODE_FIFO_KHR;
	i = 0;
	while (i < pres_mode_count)
	{
		if (pres_modes[i] == VK_PRESENT_MODE_MAILBOX_KHR)
		{
			present_mode = VK_PRESENT_MODE_MAILBOX_KHR;
			break ;
		}
		i++;
	}
	ft_memdel((void**)&pres_modes);
	return (present_mode);
}

static void			swapchain_creation(t_vulkan *v,
										t_rt *r,
										VkSurfaceFormatKHR *surf_form,
										VkPresentModeKHR present_mode)
{
	VkSwapchainCreateInfoKHR	swapchain_create_info;

	swapchain_create_info = (VkSwapchainCreateInfoKHR){
		.sType = VK_STRUCTURE_TYPE_SWAPCHAIN_CREATE_INFO_KHR,
		.surface = v->surface,
		.minImageCount = v->framebuffer.sc_image_count,
		.imageFormat = surf_form->format,
		.imageColorSpace = surf_form->colorSpace,
		.imageExtent = (VkExtent2D)
		{
			.height = r->win_height,
			.width = r->win_width
		},
		.imageArrayLayers = 1,
		.imageUsage = VK_IMAGE_USAGE_COLOR_ATTACHMENT_BIT,
		.imageSharingMode = VK_SHARING_MODE_EXCLUSIVE,
		.preTransform = v->phys_device.surface_cap.currentTransform,
		.compositeAlpha = VK_COMPOSITE_ALPHA_OPAQUE_BIT_KHR,
		.presentMode = present_mode,
		.clipped = VK_TRUE,
	};
	if (vkCreateSwapchainKHR(v->device, &swapchain_create_info, NULL,
										&(v->swapchain)) != VK_SUCCESS)
		handle_error("Swapchain creation error!");
}

static void			set_win_size(t_vulkan *v, t_rt *r)
{
	r->win_height = v->phys_device.surface_cap.currentExtent.height;
	r->win_width = v->phys_device.surface_cap.currentExtent.width;
	if (r->win_width == UINT32_MAX)
	{
		r->win_width = clamp_u32(WIN_WIDTH,
		v->phys_device.surface_cap.minImageExtent.width,
		v->phys_device.surface_cap.maxImageExtent.width);
		r->win_height = clamp_u32(WIN_HEIGHT,
		v->phys_device.surface_cap.minImageExtent.height,
		v->phys_device.surface_cap.maxImageExtent.height);
	}
}

void				vku_swapchain_create(t_vulkan *v, t_rt *r)
{
	VkSurfaceFormatKHR			*surf_form;
	VkPresentModeKHR			present_mode;

	surf_form = v->phys_device.surface_formats;
	if (surf_form->format == VK_FORMAT_UNDEFINED)
		surf_form->format = VK_FORMAT_B8G8R8A8_UNORM;
	present_mode = vku_get_present_mode(v);
	v->framebuffer.sc_image_count = present_mode == VK_PRESENT_MODE_MAILBOX_KHR
		? PRESENT_MODE_MAILBOX_IMAGE_COUNT : PRESENT_MODE_DEFAULT_IMAGE_COUNT;
	set_win_size(v, r);
	swapchain_creation(v, r, surf_form, present_mode);
	if (vkGetSwapchainImagesKHR(v->device, v->swapchain,
				&v->framebuffer.sc_image_count, NULL) != VK_SUCCESS)
		handle_error("Get swapchain images error");
	if (vkGetSwapchainImagesKHR(v->device, v->swapchain,
	&(v->framebuffer.sc_image_count), v->framebuffer.sc_images) != VK_SUCCESS)
		handle_error("Get swapchain images error");
}
