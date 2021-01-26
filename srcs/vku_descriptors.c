/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vku_descriptors.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/18 09:37:51 by marvin            #+#    #+#             */
/*   Updated: 2020/10/01 15:22:41 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

void						vku_create_descriptor_pool(t_vulkan *v)
{
	VkDescriptorPoolSize		pool_sizes;
	VkDescriptorPoolCreateInfo	pool_info;

	pool_sizes = (VkDescriptorPoolSize){
		.type = VK_DESCRIPTOR_TYPE_STORAGE_BUFFER,
		.descriptorCount = v->framebuffer.sc_image_count
	};
	pool_info = (VkDescriptorPoolCreateInfo){
		.sType = VK_STRUCTURE_TYPE_DESCRIPTOR_POOL_CREATE_INFO,
		.poolSizeCount = 1,
		.pPoolSizes = &pool_sizes,
		.maxSets = v->framebuffer.sc_image_count
	};
	if (vkCreateDescriptorPool(v->device, &pool_info, NULL, &v->descriptor.pool)
													!= VK_SUCCESS)
		handle_error("Descriptor pool creation error!");
}

void						vku_create_descriptor_set_layout(t_vulkan *v)
{
	VkDescriptorSetLayoutBinding	layout_bindings[2];
	VkDescriptorSetLayoutCreateInfo	layout_info;

	layout_bindings[0] = (VkDescriptorSetLayoutBinding){
		.binding = 0,
		.descriptorCount = 1,
		.descriptorType = VK_DESCRIPTOR_TYPE_STORAGE_BUFFER,
		.pImmutableSamplers = NULL,
		.stageFlags = VK_SHADER_STAGE_FRAGMENT_BIT
	};
	layout_bindings[1] = (VkDescriptorSetLayoutBinding){
		.binding = 1,
		.descriptorCount = 1,
		.descriptorType = VK_DESCRIPTOR_TYPE_STORAGE_BUFFER,
		.pImmutableSamplers = NULL,
		.stageFlags = VK_SHADER_STAGE_FRAGMENT_BIT
	};
	layout_info = (VkDescriptorSetLayoutCreateInfo){
		.sType = VK_STRUCTURE_TYPE_DESCRIPTOR_SET_LAYOUT_CREATE_INFO,
		.bindingCount = 2,
		.pBindings = layout_bindings
	};
	if (vkCreateDescriptorSetLayout(v->device, &layout_info, NULL,
								&(v->descriptor.set_layout)) != VK_SUCCESS)
		handle_error("Descriptor set layout creation error!");
}

static VkWriteDescriptorSet	create_db_info(VkDescriptorSet ds,
										uint32_t binding,
										VkDescriptorBufferInfo *dbi)
{
	VkWriteDescriptorSet	res;

	res = (VkWriteDescriptorSet){
		.sType = VK_STRUCTURE_TYPE_WRITE_DESCRIPTOR_SET,
		.dstSet = ds,
		.dstBinding = binding,
		.dstArrayElement = 0,
		.descriptorType = VK_DESCRIPTOR_TYPE_STORAGE_BUFFER,
		.descriptorCount = 1,
		.pBufferInfo = dbi
	};
	return (res);
}

static void					update_descriptor_sets(t_vulkan *v)
{
	size_t						i;
	VkDescriptorBufferInfo		sbo_info;
	VkDescriptorBufferInfo		sbo_textures_info;
	VkWriteDescriptorSet		descriptor_write[2];

	i = 0;
	while (i < v->framebuffer.sc_image_count)
	{
		sbo_info = (VkDescriptorBufferInfo){
			.buffer = (v->sbo_buffers)[i].buffer,
			.offset = 0,
			.range = STORAGE_BUFFER_SIZE
		};
		sbo_textures_info = (VkDescriptorBufferInfo){
			.buffer = (v->texture_buffers)[i].buffer,
			.offset = 0,
			.range = TEXTURES_BUFFER_SIZE
		};
		descriptor_write[0] = create_db_info((v->descriptor.sets)[i],
													0, &sbo_info);
		descriptor_write[1] = create_db_info((v->descriptor.sets)[i],
													1, &sbo_textures_info);
		vkUpdateDescriptorSets(v->device, 2, descriptor_write, 0, NULL);
		i++;
	}
}

void						vku_create_descriptor_sets(t_vulkan *v)
{
	VkDescriptorSetAllocateInfo	alloc_info;
	VkDescriptorSetLayout		layouts[MAX_SWAPCHAIN_IMAGES];

	layouts[0] = v->descriptor.set_layout;
	layouts[1] = v->descriptor.set_layout;
	layouts[2] = v->descriptor.set_layout;
	alloc_info = (VkDescriptorSetAllocateInfo){
		.sType = VK_STRUCTURE_TYPE_DESCRIPTOR_SET_ALLOCATE_INFO,
		.descriptorPool = v->descriptor.pool,
		.descriptorSetCount = v->framebuffer.sc_image_count,
		.pSetLayouts = layouts
	};
	if (vkAllocateDescriptorSets(v->device, &alloc_info,
									v->descriptor.sets) != VK_SUCCESS)
		handle_error("Descriptor sets allocation error!");
	update_descriptor_sets(v);
}
