/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vku_logical_device.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/05 23:37:45 by dkathlee          #+#    #+#             */
/*   Updated: 2020/08/27 12:12:18 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

static uint32_t	find_comp_mem_type(VkPhysicalDeviceMemoryProperties *mem_prop,
									VkMemoryPropertyFlags flags)
{
	uint32_t	res;
	uint32_t	i;

	res = 0;
	i = 0;
	while (i < mem_prop->memoryTypeCount)
	{
		res |= ((mem_prop->memoryTypes[i].propertyFlags & flags) == flags) << i;
		i++;
	}
	return (res);
}

static void		create_device(t_vulkan *v)
{
	VkDeviceCreateInfo					dev_info;
	const char							*dev_ext[1];

	dev_ext[0] = VK_KHR_SWAPCHAIN_EXTENSION_NAME;
	dev_info = (VkDeviceCreateInfo){
		.sType = VK_STRUCTURE_TYPE_DEVICE_CREATE_INFO,
		.enabledExtensionCount = 1,
		.ppEnabledExtensionNames = dev_ext,
		.pEnabledFeatures = NULL,
		.queueCreateInfoCount = 1,
		.pQueueCreateInfos = &(VkDeviceQueueCreateInfo){
			.sType = VK_STRUCTURE_TYPE_DEVICE_QUEUE_CREATE_INFO,
			.queueFamilyIndex = v->phys_device.family_index,
			.queueCount = 1,
			.pQueuePriorities = &(float){ 1.0 }
		}
	};
	if (vkCreateDevice(v->phys_device.device, &dev_info, NULL,
									&(v->device)) != VK_SUCCESS)
		handle_error("Device creation error!");
}

void			vku_create_logical_device(t_vulkan *v)
{
	VkPhysicalDeviceMemoryProperties	device_mem_prop;

	create_device(v);
	vkGetDeviceQueue(v->device, v->phys_device.family_index, 0,
									&(v->queue));
	vkGetPhysicalDeviceMemoryProperties(v->phys_device.device,
									&device_mem_prop);
	v->compatible_mem_types[VULKAN_MEM_DEVICE_READBACK] =
	find_comp_mem_type(&device_mem_prop, VK_MEMORY_PROPERTY_HOST_VISIBLE_BIT
									| VK_MEMORY_PROPERTY_HOST_CACHED_BIT);
	v->compatible_mem_types[VULKAN_MEM_DEVICE_UPLOAD] =
	find_comp_mem_type(&device_mem_prop, VK_MEMORY_PROPERTY_HOST_VISIBLE_BIT
									| VK_MEMORY_PROPERTY_HOST_COHERENT_BIT);
	v->compatible_mem_types[VULKAN_MEM_DEVICE_LOCAL] =
	find_comp_mem_type(&device_mem_prop, VK_MEMORY_PROPERTY_DEVICE_LOCAL_BIT);
}
