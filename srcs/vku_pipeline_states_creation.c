/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vku_pipeline_states_creation.c                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/29 21:07:07 by marvin            #+#    #+#             */
/*   Updated: 2020/08/29 21:07:07 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

VkPipelineVertexInputStateCreateInfo	vertex_input_state(void)
{
	VkPipelineVertexInputStateCreateInfo	res;

	res = (VkPipelineVertexInputStateCreateInfo) {
		.sType = VK_STRUCTURE_TYPE_PIPELINE_VERTEX_INPUT_STATE_CREATE_INFO
	};
	return (res);
}

VkPipelineRasterizationStateCreateInfo	rasterization_state(void)
{
	VkPipelineRasterizationStateCreateInfo	res;

	res = (VkPipelineRasterizationStateCreateInfo) {
		.sType = VK_STRUCTURE_TYPE_PIPELINE_RASTERIZATION_STATE_CREATE_INFO,
		.lineWidth = 1.0f
	};
	return (res);
}

VkPipelineMultisampleStateCreateInfo	multisample_state(void)
{
	VkPipelineMultisampleStateCreateInfo	res;

	res = (VkPipelineMultisampleStateCreateInfo) {
		.sType = VK_STRUCTURE_TYPE_PIPELINE_MULTISAMPLE_STATE_CREATE_INFO,
		.rasterizationSamples = VK_SAMPLE_COUNT_1_BIT
	};
	return (res);
}

VkPipelineViewportStateCreateInfo		viewport_state(void)
{
	VkPipelineViewportStateCreateInfo	res;

	res = (VkPipelineViewportStateCreateInfo) {
		.sType = VK_STRUCTURE_TYPE_PIPELINE_VIEWPORT_STATE_CREATE_INFO,
		.viewportCount = 1,
		.pViewports = 0,
		.scissorCount = 1,
		.pScissors = 0
	};
	return (res);
}

VkPipelineColorBlendStateCreateInfo		color_blend_state(
						VkPipelineColorBlendAttachmentState *attachments)
{
	VkPipelineColorBlendStateCreateInfo	res;

	res = (VkPipelineColorBlendStateCreateInfo) {
		.sType = VK_STRUCTURE_TYPE_PIPELINE_COLOR_BLEND_STATE_CREATE_INFO,
		.logicOpEnable = VK_FALSE,
		.blendConstants = {0, 0, 0, 0},
		.attachmentCount = 1,
		.pAttachments = attachments
	};
	return (res);
}
