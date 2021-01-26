/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vku_instance.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/05 23:23:27 by dkathlee          #+#    #+#             */
/*   Updated: 2020/08/30 12:19:47 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

static const char	**vku_get_supported_extentions(uint32_t *c,
											VkExtensionProperties **prop)
{
	const char				**inst_ext;
	uint32_t				i;

	if (vkEnumerateInstanceExtensionProperties(NULL, c, NULL) != VK_SUCCESS)
		handle_error("Enumerate Instance Extention Properties error!");
	if ((*prop = ft_memalloc(sizeof(VkExtensionProperties) * *c)) == NULL)
		handle_error(ERROR_MEM_ALLOC);
	if (vkEnumerateInstanceExtensionProperties(NULL, c, *prop) != VK_SUCCESS)
		handle_error("Enumerate Instance Extention Properties error!");
	if ((inst_ext = ft_memalloc(sizeof(char*) * *c)) == NULL)
		handle_error(ERROR_MEM_ALLOC);
	i = -1;
	while (++i < *c)
		inst_ext[i] = (*prop)[i].extensionName;
	return (inst_ext);
}

void				vku_instance_create(t_app *app)
{
	VkExtensionProperties	*ext_prop;
	VkInstanceCreateInfo	inst_info;
	const char				**inst_ext;
	uint32_t				count_ext;

	inst_ext = vku_get_supported_extentions(&count_ext, &ext_prop);
	inst_info = (VkInstanceCreateInfo){
		.sType = VK_STRUCTURE_TYPE_INSTANCE_CREATE_INFO,
		.pApplicationInfo = &(VkApplicationInfo){
			.sType = VK_STRUCTURE_TYPE_APPLICATION_INFO,
			.pApplicationName = app->appname,
			.applicationVersion = VK_MAKE_VERSION(1, 0, 0),
			.apiVersion = VK_API_VERSION_1_0,
		},
		.enabledExtensionCount = count_ext,
		.ppEnabledExtensionNames = inst_ext
	};
	if (vkCreateInstance(&inst_info, NULL, &(app->vulkan.inst)) != VK_SUCCESS)
		handle_error("Instance creation error!");
	ft_memdel((void**)&ext_prop);
	ft_memdel((void**)&inst_ext);
}
