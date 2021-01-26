/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vku_render.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/10 10:36:02 by celva             #+#    #+#             */
/*   Updated: 2020/08/28 13:28:31 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

void		vku_destroy_sync_objects(t_vulkan *v)
{
	uint32_t				i;

	i = 0;
	while (i < v->framebuffer.sc_image_count)
	{
		vkDestroySemaphore(v->device, v->sync.image_available_sem[i], NULL);
		vkDestroySemaphore(v->device, v->sync.render_finished_sem[i], NULL);
		vkDestroyFence(v->device, v->sync.frame_fences[i], NULL);
		i++;
	}
}

static void	create_sync_objects(t_vulkan *v)
{
	uint32_t				i;
	VkSemaphoreCreateInfo	semaphore_create_info;
	VkFenceCreateInfo		fence_create_info;

	semaphore_create_info = (VkSemaphoreCreateInfo){
		.sType = VK_STRUCTURE_TYPE_SEMAPHORE_CREATE_INFO,
		.pNext = NULL};
	fence_create_info = (VkFenceCreateInfo){
		.sType = VK_STRUCTURE_TYPE_FENCE_CREATE_INFO,
		.flags = VK_FENCE_CREATE_SIGNALED_BIT
	};
	i = 0;
	while (i < v->framebuffer.sc_image_count)
	{
		if (vkCreateSemaphore(v->device, &semaphore_create_info, 0,
				&(v->sync.image_available_sem[i])) != VK_SUCCESS)
			handle_error("Image Availible Semaphore creation error!");
		if (vkCreateSemaphore(v->device, &semaphore_create_info, 0,
				&(v->sync.render_finished_sem[i])) != VK_SUCCESS)
			handle_error("Render Finished Semaphore creation error!");
		if (vkCreateFence(v->device, &fence_create_info, 0,
							&(v->sync.frame_fences[i])) != VK_SUCCESS)
			handle_error("Fence creation error!");
		i++;
	}
}

static void	create_buffers(t_vulkan *v)
{
	t_uint32	i;

	i = 0;
	while (i < v->framebuffer.sc_image_count)
	{
		(v->sbo_buffers)[i].buf_size = STORAGE_BUFFER_SIZE;
		vku_create_buffer(v, (v->sbo_buffers) + i,
								VK_BUFFER_USAGE_STORAGE_BUFFER_BIT,
								VK_MEMORY_PROPERTY_HOST_VISIBLE_BIT |
								VK_MEMORY_PROPERTY_HOST_COHERENT_BIT);
		(v->texture_buffers)[i].buf_size = TEXTURES_BUFFER_SIZE;
		vku_create_buffer(v, (v->texture_buffers) + i,
								VK_BUFFER_USAGE_STORAGE_BUFFER_BIT,
								VK_MEMORY_PROPERTY_HOST_VISIBLE_BIT |
								VK_MEMORY_PROPERTY_HOST_COHERENT_BIT);
		i++;
	}
}

void		vku_init_render(t_vulkan *v, t_rt *r)
{
	VkCommandPoolCreateInfo		commandpool_create_info;

	commandpool_create_info = (VkCommandPoolCreateInfo){
		.sType = VK_STRUCTURE_TYPE_COMMAND_POOL_CREATE_INFO,
		.flags = VK_COMMAND_POOL_CREATE_RESET_COMMAND_BUFFER_BIT,
		.queueFamilyIndex = v->phys_device.family_index,
	};
	if (vkCreateCommandPool(v->device, &commandpool_create_info, 0,
								&(v->commandpool)) != VK_SUCCESS)
		handle_error("Commandpool creation error!");
	create_sync_objects(v);
	create_buffers(v);
	vku_create_render_pass(v);
	vku_create_descriptor_set_layout(v);
	vku_create_pipeline(v);
	vku_create_framebuffers(v);
	vku_create_descriptor_pool(v);
	vku_create_descriptor_sets(v);
	vku_create_command_buffers(v);
	vku_load_textures(r, v);
}
