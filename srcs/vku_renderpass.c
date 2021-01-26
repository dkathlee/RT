/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vku_renderpass.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/18 12:48:25 by marvin            #+#    #+#             */
/*   Updated: 2020/08/27 01:24:13 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

static VkAttachmentDescription	get_attechment_description(t_vulkan *v)
{
	VkAttachmentDescription	res;

	res = (VkAttachmentDescription){
		.format = v->phys_device.surface_formats->format,
		.samples = VK_SAMPLE_COUNT_1_BIT,
		.loadOp = VK_ATTACHMENT_LOAD_OP_CLEAR,
		.storeOp = VK_ATTACHMENT_STORE_OP_STORE,
		.stencilLoadOp = VK_ATTACHMENT_LOAD_OP_DONT_CARE,
		.stencilStoreOp = VK_ATTACHMENT_STORE_OP_DONT_CARE,
		.initialLayout = VK_IMAGE_LAYOUT_UNDEFINED,
		.finalLayout = VK_IMAGE_LAYOUT_PRESENT_SRC_KHR
	};
	return (res);
}

static VkSubpassDependency		get_subpass_dependency(void)
{
	VkSubpassDependency	res;

	res = (VkSubpassDependency){
		.srcSubpass = VK_SUBPASS_EXTERNAL,
		.dstSubpass = 0,
		.srcStageMask = VK_PIPELINE_STAGE_COLOR_ATTACHMENT_OUTPUT_BIT,
		.srcAccessMask = 0,
		.dstStageMask = VK_PIPELINE_STAGE_COLOR_ATTACHMENT_OUTPUT_BIT,
		.dstAccessMask = VK_ACCESS_COLOR_ATTACHMENT_WRITE_BIT
	};
	return (res);
}

static void						create_render_pass(t_vulkan *v,
								VkAttachmentDescription attechment_description,
								VkSubpassDependency dependency)
{
	VkRenderPassCreateInfo	render_pass_create_info;

	render_pass_create_info = (VkRenderPassCreateInfo){
		.sType = VK_STRUCTURE_TYPE_RENDER_PASS_CREATE_INFO,
		.attachmentCount = 1,
		.pAttachments = &attechment_description,
		.subpassCount = 1,
		.pSubpasses = &(VkSubpassDescription) {
			.pipelineBindPoint = VK_PIPELINE_BIND_POINT_GRAPHICS,
			.preserveAttachmentCount = 0,
			.pPreserveAttachments = NULL,
			.pResolveAttachments = NULL,
			.pDepthStencilAttachment = NULL,
			.colorAttachmentCount = 1,
			.pColorAttachments = &(VkAttachmentReference) {
				.attachment = 0,
				.layout = VK_IMAGE_LAYOUT_COLOR_ATTACHMENT_OPTIMAL
			}
		},
		.dependencyCount = 1,
		.pDependencies = &dependency
	};
	if (vkCreateRenderPass(v->device, &render_pass_create_info,
								0, &(v->renderpass)) != VK_SUCCESS)
		handle_error("Renderpass creation error!");
}

void							vku_create_render_pass(t_vulkan *v)
{
	VkSubpassDependency		dependency;
	VkAttachmentDescription	attechment_description;

	attechment_description = get_attechment_description(v);
	dependency = get_subpass_dependency();
	create_render_pass(v, attechment_description, dependency);
}
