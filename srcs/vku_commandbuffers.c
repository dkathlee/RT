/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vku_commandbuffers.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/18 13:16:45 by marvin            #+#    #+#             */
/*   Updated: 2020/08/18 13:16:45 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

static void	begin_renderpass(t_vulkan *v, uint32_t index)
{
	VkRenderPassBeginInfo		renderpass_info;

	renderpass_info = (VkRenderPassBeginInfo) {
		.sType = VK_STRUCTURE_TYPE_RENDER_PASS_BEGIN_INFO,
		.renderPass = v->renderpass,
		.framebuffer = (v->framebuffer.frame_buffers)[index],
		.clearValueCount = 1,
		.pClearValues = &(VkClearValue){{{ 0.0f, 0.1f, 0.2f, 1.0f }}},
		.renderArea = (VkRect2D){
			.offset = (VkOffset2D) { .x = 0, .y = 0 },
			.extent = v->phys_device.surface_cap.currentExtent
		}
	};
	vkCmdBeginRenderPass(v->command_buffers[index], &renderpass_info,
							VK_SUBPASS_CONTENTS_INLINE);
}

static void	write_commands(t_vulkan *v, uint32_t index)
{
	VkCommandBufferBeginInfo	commandbuffer_info;

	commandbuffer_info = (VkCommandBufferBeginInfo){
		.sType = VK_STRUCTURE_TYPE_COMMAND_BUFFER_BEGIN_INFO
	};
	if (vkBeginCommandBuffer(v->command_buffers[index],
							&commandbuffer_info) != VK_SUCCESS)
		handle_error("Begin Command Buffer error!");
	begin_renderpass(v, index);
	vkCmdSetViewport((v->command_buffers)[index], 0, 1,
					&(VkViewport){ 0.0f, 0.0f,
					(float)v->phys_device.surface_cap.currentExtent.width,
					(float)v->phys_device.surface_cap.currentExtent.height,
					0.0f, 1.0f});
	vkCmdSetScissor((v->command_buffers)[index], 0, 1, &(VkRect2D){ {0, 0},
					v->phys_device.surface_cap.currentExtent});
	vkCmdBindPipeline(v->command_buffers[index],
						VK_PIPELINE_BIND_POINT_GRAPHICS, v->pipeline);
	vkCmdBindDescriptorSets(v->command_buffers[index],
						VK_PIPELINE_BIND_POINT_GRAPHICS, v->pipeline_layout,
						0, 1, &(v->descriptor.sets[index]), 0, NULL);
	vkCmdDraw(v->command_buffers[index], 3, 1, 0, 0);
	vkCmdEndRenderPass(v->command_buffers[index]);
	if (vkEndCommandBuffer(v->command_buffers[index]) != VK_SUCCESS)
		handle_error("End Command Buffer error!");
}

void		vku_create_command_buffers(t_vulkan *v)
{
	t_uint32					i;
	VkCommandBufferAllocateInfo	alloc_info;

	alloc_info = (VkCommandBufferAllocateInfo){
		.sType = VK_STRUCTURE_TYPE_COMMAND_BUFFER_ALLOCATE_INFO,
		.commandPool = v->commandpool,
		.level = VK_COMMAND_BUFFER_LEVEL_PRIMARY,
		.commandBufferCount = v->framebuffer.sc_image_count
	};
	if (vkAllocateCommandBuffers(v->device, &alloc_info, v->command_buffers)
															!= VK_SUCCESS)
		handle_error("Command Buffers Allocation error!");
	i = 0;
	while (i < v->framebuffer.sc_image_count)
	{
		write_commands(v, i);
		i++;
	}
}
