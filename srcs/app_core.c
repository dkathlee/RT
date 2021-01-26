/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   app_core.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/06 10:25:20 by celva             #+#    #+#             */
/*   Updated: 2020/09/16 13:34:45 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

void				rtv_app_create(t_app *app)
{
	vku_instance_create(app);
	ft_printf("Instance creation done\n");
	vku_window_create(app);
	ft_printf("Window creation done\n");
	vku_get_physical_device(&(app->vulkan));
	ft_printf("Get physical device done: %s\n",
						app->vulkan.phys_device.dev_prop.deviceName);
	vku_create_logical_device(&(app->vulkan));
	ft_printf("Logical device creation done\n");
	vku_swapchain_create(&(app->vulkan), &(app->r));
	ft_printf("Swapchain creation done\n");
	vku_init_render(&(app->vulkan), &(app->r));
	ft_printf("Render initialization done\n");
}

void				rtv_app_destroy(t_vulkan *v)
{
	vkWaitForFences(v->device, v->framebuffer.sc_image_count,
					&(v->sync.frame_fences[0]), VK_TRUE, UINT64_MAX);
	vkDestroyFramebuffer(v->device, v->framebuffer.frame_buffers[0], NULL);
	vkDestroyFramebuffer(v->device, v->framebuffer.frame_buffers[1], NULL);
	if (v->framebuffer.sc_image_count == 3)
		vkDestroyFramebuffer(v->device, v->framebuffer.frame_buffers[2], NULL);
	vkFreeCommandBuffers(v->device, v->commandpool,
						v->framebuffer.sc_image_count, v->command_buffers);
	vkDestroyPipeline(v->device, v->pipeline, NULL);
	vkDestroyPipelineLayout(v->device, v->pipeline_layout, NULL);
	vkDestroyRenderPass(v->device, v->renderpass, NULL);
	vkDestroySwapchainKHR(v->device, v->swapchain, NULL);
	vku_destroy_buffers(v);
	vkDestroyDescriptorPool(v->device, v->descriptor.pool, NULL);
	vkDestroyImageView(v->device, v->framebuffer.sc_image_views[0], NULL);
	vkDestroyImageView(v->device, v->framebuffer.sc_image_views[1], NULL);
	if (v->framebuffer.sc_image_count == 3)
		vkDestroyImageView(v->device, v->framebuffer.sc_image_views[2], NULL);
	vkDestroyDescriptorSetLayout(v->device, v->descriptor.set_layout, NULL);
	vku_destroy_sync_objects(v);
	vkDestroyCommandPool(v->device, v->commandpool, NULL);
	vkDestroyDevice(v->device, NULL);
	vkDestroySurfaceKHR(v->inst, v->surface, NULL);
	vkDestroyInstance(v->inst, NULL);
}

void				rtv_app_run(t_app *app)
{
	SDL_Event	evt;
	uint32_t	run;
	uint32_t	redraw;

	run = 1;
	redraw = 0;
	while (run)
	{
		while (SDL_PollEvent(&evt))
		{
			if (evt.type == SDL_QUIT)
				run = 0;
			else if (evt.type == SDL_KEYDOWN)
				redraw = handling_keyboard_input(evt, &app->r.camera);
		}
		if (redraw == 0)
		{
			draw_frame(&(app->vulkan), &(app->r));
			redraw = 1;
		}
	}
	rtv_app_destroy(&(app->vulkan));
	SDL_DestroyWindow(app->window);
	SDL_Quit();
}
