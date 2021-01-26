/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vku_pipeline.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/18 10:51:05 by marvin            #+#    #+#             */
/*   Updated: 2020/09/01 13:32:48 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

static VkPipelineShaderStageCreateInfo	*get_stage_create_infos(t_vulkan *v,
									VkPipelineShaderStageCreateInfo *stages)
{
	VkShaderModule	fragment_shader;
	VkShaderModule	vertex_shader;
	size_t			code_len;
	char			*code;

	code_len = load_shader_file("shaders/rtv1.frag.spv", &code);
	fragment_shader = vku_create_shader_module(v, code, code_len);
	ft_memdel((void**)&code);
	code_len = load_shader_file("shaders/rtv1.vert.spv", &code);
	vertex_shader = vku_create_shader_module(v, code, code_len);
	ft_memdel((void**)&code);
	stages[0] = (VkPipelineShaderStageCreateInfo){
		.sType = VK_STRUCTURE_TYPE_PIPELINE_SHADER_STAGE_CREATE_INFO,
		.stage = VK_SHADER_STAGE_VERTEX_BIT,
		.module = vertex_shader,
		.pName = "main",
	};
	stages[1] = (VkPipelineShaderStageCreateInfo){
		.sType = VK_STRUCTURE_TYPE_PIPELINE_SHADER_STAGE_CREATE_INFO,
		.stage = VK_SHADER_STAGE_FRAGMENT_BIT,
		.module = fragment_shader,
		.pName = "main",
	};
	return (stages);
}

static void								create_pipeline_layout(t_vulkan *v)
{
	VkPipelineLayoutCreateInfo pipeline_layout_create_info;

	pipeline_layout_create_info = (VkPipelineLayoutCreateInfo){
		.sType = VK_STRUCTURE_TYPE_PIPELINE_LAYOUT_CREATE_INFO,
		.setLayoutCount = 1,
		.pSetLayouts = &(v->descriptor.set_layout)
	};
	if (vkCreatePipelineLayout(v->device, &pipeline_layout_create_info,
								0, &(v->pipeline_layout)) != VK_SUCCESS)
		handle_error("Pipeline Layout Creation error!");
}

static void								destroy_shader_modules(t_vulkan *v,
				VkPipelineShaderStageCreateInfo *stages, uint32_t stage_count)
{
	uint32_t	i;

	i = 0;
	while (i < stage_count)
	{
		vkDestroyShaderModule(v->device, stages[i].module, NULL);
		i++;
	}
}

static void								create_graphics_pipelines(t_vulkan *v,
				VkPipelineInputAssemblyStateCreateInfo *input_assembly_state,
				VkPipelineDynamicStateCreateInfo *dynamic_state,
				VkPipelineColorBlendStateCreateInfo *color_blend_state)
{
	VkGraphicsPipelineCreateInfo			pipeline_create_info;
	VkPipelineShaderStageCreateInfo			stages[2];
	VkPipelineVertexInputStateCreateInfo	vertex_input_state_create_info;
	VkPipelineViewportStateCreateInfo		viewport_state_create_info;
	VkPipelineRasterizationStateCreateInfo	rasterization_state_create_info;

	vertex_input_state_create_info = vertex_input_state();
	viewport_state_create_info = viewport_state();
	rasterization_state_create_info = rasterization_state();
	pipeline_create_info = (VkGraphicsPipelineCreateInfo){
		.sType = VK_STRUCTURE_TYPE_GRAPHICS_PIPELINE_CREATE_INFO,
		.stageCount = 2, .pStages = get_stage_create_infos(v, stages),
		.pVertexInputState = &vertex_input_state_create_info,
		.pInputAssemblyState = input_assembly_state,
		.pViewportState = &viewport_state_create_info,
		.pRasterizationState = &rasterization_state_create_info,
		.pMultisampleState = &(VkPipelineMultisampleStateCreateInfo) {
			.sType = VK_STRUCTURE_TYPE_PIPELINE_MULTISAMPLE_STATE_CREATE_INFO,
			.rasterizationSamples = VK_SAMPLE_COUNT_1_BIT },
		.pColorBlendState = color_blend_state, .pDynamicState = dynamic_state,
		.layout = v->pipeline_layout, .renderPass = v->renderpass };
	if (vkCreateGraphicsPipelines(v->device, VK_NULL_HANDLE, 1,
					&pipeline_create_info, 0, &(v->pipeline)) != VK_SUCCESS)
		handle_error("Graphics Pipeline creation error!");
	destroy_shader_modules(v, stages, 2);
}

void									vku_create_pipeline(t_vulkan *v)
{
	VkPipelineInputAssemblyStateCreateInfo	input_assembly_state;
	VkPipelineColorBlendStateCreateInfo		color_blend_state_create_info;
	VkPipelineDynamicStateCreateInfo		dynamic_state;
	VkPipelineColorBlendAttachmentState		color_blend_attachment;

	input_assembly_state = (VkPipelineInputAssemblyStateCreateInfo) {
		.sType = VK_STRUCTURE_TYPE_PIPELINE_INPUT_ASSEMBLY_STATE_CREATE_INFO,
		.topology = VK_PRIMITIVE_TOPOLOGY_TRIANGLE_LIST,
		.primitiveRestartEnable = VK_FALSE,
	};
	color_blend_attachment = (VkPipelineColorBlendAttachmentState) {
		.colorWriteMask = VK_COLOR_COMPONENT_R_BIT | VK_COLOR_COMPONENT_G_BIT |
							VK_COLOR_COMPONENT_B_BIT | VK_COLOR_COMPONENT_A_BIT
	};
	color_blend_state_create_info = color_blend_state(&color_blend_attachment);
	dynamic_state = (VkPipelineDynamicStateCreateInfo) {
		.sType = VK_STRUCTURE_TYPE_PIPELINE_DYNAMIC_STATE_CREATE_INFO,
		.dynamicStateCount = 2,
		.pDynamicStates = (const VkDynamicState[2]) { VK_DYNAMIC_STATE_VIEWPORT,
													VK_DYNAMIC_STATE_SCISSOR },
	};
	create_pipeline_layout(v);
	create_graphics_pipelines(v, &input_assembly_state, &dynamic_state,
											&color_blend_state_create_info);
}
