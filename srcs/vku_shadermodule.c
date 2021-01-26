/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vku_shadermodule.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/16 12:45:59 by dkathlee          #+#    #+#             */
/*   Updated: 2020/08/18 15:48:42 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

VkShaderModule	vku_create_shader_module(t_vulkan *v, char *code,
														uint32_t code_l)
{
	VkShaderModuleCreateInfo	sm_create_info;
	VkShaderModule				shader_module;

	sm_create_info = (VkShaderModuleCreateInfo) {
		.sType = VK_STRUCTURE_TYPE_SHADER_MODULE_CREATE_INFO,
		.codeSize = code_l,
		.pCode = (uint32_t*)code
	};
	if (vkCreateShaderModule(v->device, &sm_create_info, NULL,
								&shader_module) != VK_SUCCESS)
		handle_error("Shader module creation error!");
	return (shader_module);
}
