/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vku_physical_device.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dkathlee <dkathlee@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/05 23:37:45 by dkathlee          #+#    #+#             */
/*   Updated: 2020/09/17 16:56:24 by dkathlee         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

static void		set_device_formats(t_vulkan *v, VkPhysicalDevice device,
									uint32_t j)
{
	uint32_t					num;

	if (vkGetPhysicalDeviceSurfaceFormatsKHR(device, v->surface,
											&(num), NULL) != VK_SUCCESS)
		handle_error("Get physical device surface format error");
	if ((v->phys_device.surface_formats =
					ft_memalloc(sizeof(VkSurfaceFormatKHR) * num)) == NULL)
		handle_error(ERROR_MEM_ALLOC);
	v->phys_device.num_formats = num;
	v->phys_device.family_index = j;
	if (vkGetPhysicalDeviceSurfaceFormatsKHR(device, v->surface, &num,
								v->phys_device.surface_formats) != VK_SUCCESS)
		handle_error("Get physical device surface format error");
	if (vkGetPhysicalDeviceSurfaceCapabilitiesKHR(device, v->surface,
								&(v->phys_device.surface_cap)) != VK_SUCCESS)
		handle_error("Get physical device surface capabilities error");
}

static void		get_device_family_properties(t_vulkan *v,
										VkPhysicalDevice device,
										VkQueueFamilyProperties **qf_prop,
										VkBool32 **sup_pres)
{
	uint32_t					num;

	vkGetPhysicalDeviceQueueFamilyProperties(device, &num, NULL);
	v->phys_device.num_families = num;
	if ((*qf_prop = ft_memalloc(sizeof(VkQueueFamilyProperties) * num)) == NULL)
		handle_error(ERROR_MEM_ALLOC);
	vkGetPhysicalDeviceQueueFamilyProperties(device, &num, *qf_prop);
	if ((*sup_pres = ft_memalloc(sizeof(VkBool32) * num)) == NULL)
		handle_error(ERROR_MEM_ALLOC);
}

static void		check_device(t_vulkan *v, VkPhysicalDevice device,
							VkPhysicalDeviceProperties device_prop)
{
	VkBool32					*sup_pres;
	uint32_t					j;
	VkQueueFamilyProperties		*qf_prop;

	get_device_family_properties(v, device, &qf_prop, &sup_pres);
	j = -1;
	while (++j < v->phys_device.num_families)
	{
		if (vkGetPhysicalDeviceSurfaceSupportKHR(device, j, v->surface,
												&(sup_pres[j])) != VK_SUCCESS)
			handle_error("Get physical device surface support error");
		if (qf_prop[j].queueFlags & VK_QUEUE_GRAPHICS_BIT &&
			device_prop.deviceType == VK_PHYSICAL_DEVICE_TYPE_DISCRETE_GPU)
			if (sup_pres[j])
			{
				v->phys_device.dev_prop = device_prop;
				v->phys_device.device = device;
				v->phys_device.q_family_prop = qf_prop;
				v->phys_device.q_supports_present = sup_pres;
				set_device_formats(v, device, j);
				break ;
			}
	}
	ft_memdel((void**)&qf_prop);
	ft_memdel((void**)&sup_pres);
}

static void		select_physical_device(t_vulkan *v, uint32_t num_d,
										VkPhysicalDevice *devices,
										VkPhysicalDeviceProperties *device_prop)
{
	uint32_t					i;

	i = -1;
	while (++i < num_d)
	{
		vkGetPhysicalDeviceProperties(devices[i], &(device_prop[i]));
		check_device(v, devices[i], device_prop[i]);
	}
}

void			vku_get_physical_device(t_vulkan *v)
{
	VkPhysicalDevice			*devices;
	uint32_t					num_d;
	VkPhysicalDeviceProperties	*d_prop;

	if (vkEnumeratePhysicalDevices(v->inst, &num_d, NULL) != VK_SUCCESS)
		handle_error("Enumerate Physical Devices error!");
	if ((devices = ft_memalloc(sizeof(VkPhysicalDevice) * num_d)) == NULL)
		handle_error(ERROR_MEM_ALLOC);
	if (vkEnumeratePhysicalDevices(v->inst, &num_d, devices) != VK_SUCCESS)
		handle_error("Enumerate Physical Devices error!");
	if ((d_prop = ft_memalloc(sizeof(VkPhysicalDeviceProperties) * num_d))
																== NULL)
		handle_error(ERROR_MEM_ALLOC);
	select_physical_device(v, num_d, devices, d_prop);
	ft_memdel((void**)&devices);
	ft_memdel((void**)&d_prop);
}
