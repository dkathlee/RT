/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vku.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/04 09:16:26 by dkathlee          #+#    #+#             */
/*   Updated: 2020/10/01 13:51:19 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef VKU_H
# define VKU_H
# include "vec_lib.h"
# include <vulkan.h>
# include <vk_sdk_platform.h>
# define VK_ICD_FILENAMES "libs/vulkan/macOS/icd.d/MoltenVK_icd.json"
# define VK_LAYER_PATH "$VULKAN_SDK/explicit_layers.d"
# if SDL_BYTEORDER == SDL_BIG_ENDIAN
#  define RMASK	0xff000000
#  define GMASK	0x00ff0000
#  define BMASK	0x0000ff00
#  define AMASK	0x000000ff
# else
#  define RMASK	0x000000ff
#  define GMASK	0x0000ff00
#  define BMASK	0x00ff0000
#  define AMASK	0xff000000
# endif

enum {
	VULKAN_MEM_DEVICE_READBACK,
	VULKAN_MEM_DEVICE_UPLOAD,
	VULKAN_MEM_DEVICE_LOCAL,
	VULKAN_MEM_COUNT
};

enum {
	Kb = (1 << 10),
	Mb = (Kb << 10),
	MAX_SWAPCHAIN_IMAGES = 3,
	PRESENT_MODE_MAILBOX_IMAGE_COUNT = 3,
	PRESENT_MODE_DEFAULT_IMAGE_COUNT = 2,
	STORAGE_BUFFER_SIZE = 64 * Kb,
	TEXTURES_BUFFER_SIZE = 256 * Mb
};

typedef struct							s_buffer
{
	VkDeviceMemory				dev_mem;
	VkBuffer					buffer;
	void						*mem_ptr;
	VkDeviceSize				buf_size;
}										t_buffer;

typedef struct							s_framebuffer
{
	uint32_t					sc_image_count;
	VkImage						sc_images[MAX_SWAPCHAIN_IMAGES];
	VkImageView					sc_image_views[MAX_SWAPCHAIN_IMAGES];
	VkFramebuffer				frame_buffers[MAX_SWAPCHAIN_IMAGES];
}										t_framebuffer;

typedef struct							s_physical_device
{
	uint32_t					num_families;
	uint32_t					num_formats;
	uint32_t					family_index;
	VkPhysicalDevice			device;
	VkPhysicalDeviceProperties	dev_prop;
	VkQueueFamilyProperties		*q_family_prop;
	VkBool32					*q_supports_present;
	VkSurfaceFormatKHR			*surface_formats;
	VkSurfaceCapabilitiesKHR	surface_cap;
}										t_physical_device;

typedef struct							s_syncronization
{
	VkFence						frame_fences[MAX_SWAPCHAIN_IMAGES];
	VkSemaphore					image_available_sem[MAX_SWAPCHAIN_IMAGES];
	VkSemaphore					render_finished_sem[MAX_SWAPCHAIN_IMAGES];
}										t_syncronization;

typedef struct							s_descriptor
{
	VkDescriptorPool			pool;
	VkDescriptorSetLayout		set_layout;
	VkDescriptorSet				sets[MAX_SWAPCHAIN_IMAGES];
}										t_descriptor;

typedef struct							s_vulkan
{
	VkInstance					inst;
	VkDevice					device;
	VkSurfaceKHR				surface;
	VkSurfaceFormatKHR			surface_format;
	VkSwapchainKHR				swapchain;
	VkPipeline					pipeline;
	VkPipelineLayout			pipeline_layout;
	VkRenderPass				renderpass;
	VkCommandBuffer				command_buffers[MAX_SWAPCHAIN_IMAGES];
	VkCommandPool				commandpool;
	VkQueue						queue;
	t_physical_device			phys_device;
	t_framebuffer				framebuffer;
	t_syncronization			sync;
	uint32_t					compatible_mem_types[VULKAN_MEM_COUNT];
	t_descriptor				descriptor;
	t_buffer					sbo_buffers[MAX_SWAPCHAIN_IMAGES];
	t_buffer					texture_buffers[MAX_SWAPCHAIN_IMAGES];
}										t_vulkan;

void									vku_create_buffer(t_vulkan *v,
											t_buffer *buffer,
											VkBufferUsageFlags usage,
											VkMemoryPropertyFlags properties);
void									vku_create_descriptor_pool(t_vulkan *v);
void									vku_create_descriptor_set_layout(
																t_vulkan *v);
void									vku_create_descriptor_sets(t_vulkan *v);
void									vku_destroy_sync_objects(t_vulkan *v);
VkPipelineVertexInputStateCreateInfo	vertex_input_state(void);
VkPipelineRasterizationStateCreateInfo	rasterization_state(void);
VkPipelineMultisampleStateCreateInfo	multisample_state(void);
VkPipelineViewportStateCreateInfo		viewport_state(void);
VkPipelineColorBlendStateCreateInfo		color_blend_state(
						VkPipelineColorBlendAttachmentState *attachments);
#endif
