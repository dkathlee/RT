/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vku_buffers.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/11 17:01:03 by dkathlee          #+#    #+#             */
/*   Updated: 2020/10/01 01:38:01 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

void						vku_destroy_buffers(t_vulkan *v)
{
	uint32_t	i;

	i = 0;
	while (i < v->framebuffer.sc_image_count)
	{
		vkDestroyBuffer(v->device, v->sbo_buffers[i].buffer, NULL);
		vkFreeMemory(v->device, v->sbo_buffers[i].dev_mem, NULL);
		i++;
	}
}

static uint32_t				find_memory_type(VkPhysicalDevice dev,
												uint32_t type_filter,
												VkMemoryPropertyFlags prop)
{
	VkPhysicalDeviceMemoryProperties	mem_properties;
	uint32_t							i;

	vkGetPhysicalDeviceMemoryProperties(dev, &mem_properties);
	i = 0;
	while (i < mem_properties.memoryTypeCount)
	{
		if ((type_filter & (1 << i)) &&
			(mem_properties.memoryTypes[i].propertyFlags & prop) == prop)
			return (i);
		i++;
	}
	return (-1);
}

static VkBufferCreateInfo	get_buffer_info(t_vulkan *v,
											VkBufferUsageFlags usage,
											t_buffer *buffer)
{
	VkBufferCreateInfo		buffer_info;

	buffer_info = (VkBufferCreateInfo){
		.sType = VK_STRUCTURE_TYPE_BUFFER_CREATE_INFO,
		.size = buffer->buf_size,
		.usage = usage,
		.sharingMode = VK_SHARING_MODE_EXCLUSIVE,
		.queueFamilyIndexCount = 1,
		.pQueueFamilyIndices = &(v->phys_device.family_index)
	};
	return (buffer_info);
}

void						vku_create_buffer(t_vulkan *v, t_buffer *buffer,
											VkBufferUsageFlags usage,
											VkMemoryPropertyFlags properties)
{
	VkBufferCreateInfo		buffer_info;
	VkMemoryAllocateInfo	alloc_info;
	VkMemoryRequirements	mem_requirements;

	buffer_info = get_buffer_info(v, usage, buffer);
	if (vkCreateBuffer(v->device, &buffer_info, NULL,
						&(buffer->buffer)) != VK_SUCCESS)
		handle_error("Buffer creation error!");
	vkGetBufferMemoryRequirements(v->device, buffer->buffer, &mem_requirements);
	alloc_info = (VkMemoryAllocateInfo) {
		.sType = VK_STRUCTURE_TYPE_MEMORY_ALLOCATE_INFO,
		.allocationSize = mem_requirements.size,
		.memoryTypeIndex = find_memory_type(v->phys_device.device,
								mem_requirements.memoryTypeBits, properties)
	};
	if (vkAllocateMemory(v->device, &alloc_info, NULL,
							&(buffer->dev_mem)) != VK_SUCCESS)
		handle_error("Memory allocation error!");
	if (vkBindBufferMemory(v->device, buffer->buffer,
							buffer->dev_mem, 0) != VK_SUCCESS)
		handle_error("Bind Buffer Memory error!");
}
