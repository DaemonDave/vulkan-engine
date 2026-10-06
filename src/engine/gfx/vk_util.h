#ifndef SRC_ENGINE_GFX_VK_UTIL_H
#define SRC_ENGINE_GFX_VK_UTIL_H

#include "common.h"
#include "gfx_types.h"
#include "res/res.h"




void vk_copy_buffer(
	VkBuffer src, 
	VkBuffer dst, 
	VkDeviceSize size
);


bool vk_upload_buffer(
    VkBuffer *buffer,
    VkDeviceMemory *memory,
    const void *data,
    VkDeviceSize size,
    VkBufferUsageFlags usage);

VkCommandBuffer vk_begin_commands();

void vk_end_commands(
	VkCommandBuffer cmdbuf
);




VkFormat vk_find_supported_format( 
	VkFormat *formats,
	size_t    formats_num,
	VkImageTiling tiling, 
	VkFormatFeatureFlags features 
);
	
bool vk_has_stencil(VkFormat format);

VkFormat vk_find_depth_format();


VkShaderModule vk_create_shader_module(enum Resource file);


void vk_transition_image_layout(
	VkImage       image,
	VkFormat      format,
	VkImageLayout old_layout,
	VkImageLayout new_layout
);


void vk_copy_buffer_to_image(
	VkBuffer buffer,
	VkImage  image,
	uint32_t width,
	uint32_t height
);

#endif /* SRC_ENGINE_GFX_VK_UTIL_H */
