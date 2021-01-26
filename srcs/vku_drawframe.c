/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vku_drawframe.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/14 17:56:35 by dkathlee          #+#    #+#             */
/*   Updated: 2020/09/16 15:44:32 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

static void		update_sbo(t_vulkan *v, t_rt *r, uint32_t buf_index)
{
	void		*data;
	t_rt_input	input;

	if (vkMapMemory(v->device, v->sbo_buffers[buf_index].dev_mem, 0,
						STORAGE_BUFFER_SIZE, 0, &data) != VK_SUCCESS)
		handle_error("Map Memory error!");
	input = (t_rt_input){
		.camera = r->camera,
		.win_height = r->win_height,
		.win_width = r->win_width,
		.n_fig = r->n_fig,
		.n_lig = r->n_lig,
		.ui_texture = r->ui_texture
	};
	ft_memcpy(data, &input, sizeof(input));
	ft_memcpy(data + sizeof(t_rt_input), r->sbo_figures,
					sizeof(t_object) * r->n_fig);
	ft_memcpy(data + sizeof(t_rt_input) + sizeof(t_object) * r->n_fig,
						r->sbo_lights, sizeof(t_object) * r->n_lig);
	vkUnmapMemory(v->device, v->sbo_buffers[buf_index].dev_mem);
}

static void		submit_queue(t_vulkan *v, uint32_t index)
{
	VkSubmitInfo	submit_info;

	submit_info = (VkSubmitInfo){
		.sType = VK_STRUCTURE_TYPE_SUBMIT_INFO,
		.waitSemaphoreCount = 1,
		.pWaitSemaphores = &(v->sync.image_available_sem[index]),
		.pWaitDstStageMask = &(VkPipelineStageFlags) {
			VK_PIPELINE_STAGE_BOTTOM_OF_PIPE_BIT
		},
		.commandBufferCount = 1,
		.pCommandBuffers = &((v->command_buffers)[index]),
		.signalSemaphoreCount = 1,
		.pSignalSemaphores = &(v->sync.render_finished_sem[index])
	};
	if (vkQueueSubmit(v->queue, 1, &submit_info, v->sync.frame_fences[index])
											!= VK_SUCCESS)
		handle_error("Queue Submit error!");
}

static uint32_t	acquire_next_image(t_vulkan *v, uint32_t index)
{
	uint32_t			image_index;

	if (vkWaitForFences(v->device, 1, &(v->sync.frame_fences[index]),
									VK_TRUE, UINT64_MAX) != VK_SUCCESS)
		handle_error("Waiting for fence error!");
	if (vkResetFences(v->device, 1,
						&(v->sync.frame_fences[index])) != VK_SUCCESS)
		handle_error("Reset fences error!");
	if (vkAcquireNextImageKHR(v->device, v->swapchain, UINT64_MAX,
						v->sync.image_available_sem[index], VK_NULL_HANDLE,
						&image_index) != VK_SUCCESS)
		handle_error("Acquire next image error!");
	return (image_index);
}

void			draw_frame(t_vulkan *v, t_rt *r)
{
	uint32_t			index;
	uint32_t			image_index;
	VkPresentInfoKHR	present_info;
	static uint32_t		frame_index;

	index = frame_index % v->framebuffer.sc_image_count;
	image_index = acquire_next_image(v, index);
	update_sbo(v, r, image_index);
	submit_queue(v, index);
	present_info = (VkPresentInfoKHR){
		.sType = VK_STRUCTURE_TYPE_PRESENT_INFO_KHR,
		.waitSemaphoreCount = 1,
		.pWaitSemaphores = &(v->sync.render_finished_sem[index]),
		.swapchainCount = 1,
		.pSwapchains = &(v->swapchain),
		.pImageIndices = &image_index,
	};
	vkQueuePresentKHR(v->queue, &present_info);
	frame_index++;
}
