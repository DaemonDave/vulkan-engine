#include "vk_util.h"

#include "common.h"
#include "engine.h"
#include "gfx.h"
#include "gfx_types.h"
#include "res/res.h"

extern struct VkEngine vk;

/****************
 * MEMORY STUFF *
 ****************/
static bool vk_find_memory_type(
    uint32_t type_filter,
    VkMemoryPropertyFlags properties,
    uint32_t *memory_type_index)
{
    if (memory_type_index == NULL) {
        return false;
    }

    VkPhysicalDeviceMemoryProperties memory_properties;

    vkGetPhysicalDeviceMemoryProperties(
        vk.dev_physical,
        &memory_properties
    );

    for (uint32_t i = 0;
         i < memory_properties.memoryTypeCount;
         ++i)
    {
        const VkMemoryType *memory_type =
            &memory_properties.memoryTypes[i];

        if ((type_filter & (1u << i)) &&
            (memory_type->propertyFlags & properties) == properties)
        {
            *memory_type_index = i;
            return true;
        }
    }

    return false;
}


static bool vk_create_buffer(
    VkDeviceSize size,
    VkBufferUsageFlags usage,
    VkMemoryPropertyFlags memory_properties,
    VkBuffer *buffer,
    VkDeviceMemory *memory)
{
    if (buffer == NULL ||
        memory == NULL ||
        size == 0 ||
        vk.dev == VK_NULL_HANDLE ||
        vk.dev_physical == VK_NULL_HANDLE)
    {
        return false;
    }

    *buffer = VK_NULL_HANDLE;
    *memory = VK_NULL_HANDLE;

    VkBufferCreateInfo buffer_info = {
        .sType = VK_STRUCTURE_TYPE_BUFFER_CREATE_INFO,
        .pNext = NULL,
        .flags = 0,
        .size = size,
        .usage = usage,
        .sharingMode = VK_SHARING_MODE_EXCLUSIVE,
        .queueFamilyIndexCount = 0,
        .pQueueFamilyIndices = NULL,
    };

    VkResult result = vkCreateBuffer(
        vk.dev,
        &buffer_info,
        NULL,
        buffer
    );

    if (result != VK_SUCCESS) {
        return false;
    }

    VkMemoryRequirements memory_requirements;

    vkGetBufferMemoryRequirements(
        vk.dev,
        *buffer,
        &memory_requirements
    );

    uint32_t memory_type_index;

    if (!vk_find_memory_type(
            memory_requirements.memoryTypeBits,
            memory_properties,
            &memory_type_index))
    {
        vkDestroyBuffer(vk.dev, *buffer, NULL);
        *buffer = VK_NULL_HANDLE;

        return false;
    }

    VkMemoryAllocateInfo allocation_info = {
        .sType = VK_STRUCTURE_TYPE_MEMORY_ALLOCATE_INFO,
        .pNext = NULL,
        .allocationSize = memory_requirements.size,
        .memoryTypeIndex = memory_type_index,
    };

    result = vkAllocateMemory(
        vk.dev,
        &allocation_info,
        NULL,
        memory
    );

    if (result != VK_SUCCESS) {
        vkDestroyBuffer(vk.dev, *buffer, NULL);

        *buffer = VK_NULL_HANDLE;
        *memory = VK_NULL_HANDLE;

        return false;
    }

    result = vkBindBufferMemory(
        vk.dev,
        *buffer,
        *memory,
        0
    );

    if (result != VK_SUCCESS) {
        vkFreeMemory(vk.dev, *memory, NULL);
        vkDestroyBuffer(vk.dev, *buffer, NULL);

        *buffer = VK_NULL_HANDLE;
        *memory = VK_NULL_HANDLE;

        return false;
    }

    return true;
}


static void vk_destroy_buffer(
    VkBuffer buffer,
    VkDeviceMemory memory)
{
    if (vk.dev == VK_NULL_HANDLE) {
        return;
    }

    if (buffer != VK_NULL_HANDLE) {
        vkDestroyBuffer(vk.dev, buffer, NULL);
    }

    if (memory != VK_NULL_HANDLE) {
        vkFreeMemory(vk.dev, memory, NULL);
    }
}


void vk_copy_buffer(
    VkBuffer src,
    VkBuffer dst,
    VkDeviceSize size)
{
    if (src == VK_NULL_HANDLE ||
        dst == VK_NULL_HANDLE ||
        size == 0)
    {
        return;
    }

    VkCommandBuffer command_buffer = vk_begin_commands();

    if (command_buffer == VK_NULL_HANDLE) {
        return;
    }

    VkBufferCopy copy_info = {
        .srcOffset = 0,
        .dstOffset = 0,
        .size = size,
    };

    vkCmdCopyBuffer(
        command_buffer,
        src,
        dst,
        1,
        &copy_info
    );

    /*
     * vk_end_commands() must submit and wait for completion before
     * returning. Otherwise the staging buffer cannot be destroyed yet.
     */
    vk_end_commands(command_buffer);
}


bool vk_upload_buffer(
    VkBuffer *buffer,
    VkDeviceMemory *memory,
    const void *data,
    VkDeviceSize size,
    VkBufferUsageFlags usage)
{
    if (buffer == NULL ||
        memory == NULL ||
        data == NULL ||
        size == 0 ||
        vk.dev == VK_NULL_HANDLE ||
        vk.dev_physical == VK_NULL_HANDLE)
    {
        return false;
    }

    *buffer = VK_NULL_HANDLE;
    *memory = VK_NULL_HANDLE;

    VkBuffer staging_buffer = VK_NULL_HANDLE;
    VkDeviceMemory staging_memory = VK_NULL_HANDLE;

    if (!vk_create_buffer(
            size,
            VK_BUFFER_USAGE_TRANSFER_SRC_BIT,
            VK_MEMORY_PROPERTY_HOST_VISIBLE_BIT |
            VK_MEMORY_PROPERTY_HOST_COHERENT_BIT,
            &staging_buffer,
            &staging_memory))
    {
        /*
         * Retry without HOST_COHERENT. Some implementations may provide
         * HOST_VISIBLE memory without HOST_COHERENT.
         */
        if (!vk_create_buffer(
                size,
                VK_BUFFER_USAGE_TRANSFER_SRC_BIT,
                VK_MEMORY_PROPERTY_HOST_VISIBLE_BIT,
                &staging_buffer,
                &staging_memory))
        {
            return false;
        }
    }

    void *mapped = NULL;

    VkResult result = vkMapMemory(
        vk.dev,
        staging_memory,
        0,
        size,
        0,
        &mapped
    );

    if (result != VK_SUCCESS || mapped == NULL) {
        vk_destroy_buffer(
            staging_buffer,
            staging_memory
        );

        return false;
    }

    memcpy(mapped, data, (size_t)size);

    /*
     * VK_WHOLE_SIZE avoids manually aligning the flush range to
     * VkPhysicalDeviceLimits::nonCoherentAtomSize.
     */
    VkMappedMemoryRange mapped_range = {
        .sType = VK_STRUCTURE_TYPE_MAPPED_MEMORY_RANGE,
        .pNext = NULL,
        .memory = staging_memory,
        .offset = 0,
        .size = VK_WHOLE_SIZE,
    };

    result = vkFlushMappedMemoryRanges(
        vk.dev,
        1,
        &mapped_range
    );

    vkUnmapMemory(
        vk.dev,
        staging_memory
    );

    if (result != VK_SUCCESS) {
        vk_destroy_buffer(
            staging_buffer,
            staging_memory
        );

        return false;
    }

    if (!vk_create_buffer(
            size,
            VK_BUFFER_USAGE_TRANSFER_DST_BIT | usage,
            VK_MEMORY_PROPERTY_DEVICE_LOCAL_BIT,
            buffer,
            memory))
    {
        vk_destroy_buffer(
            staging_buffer,
            staging_memory
        );

        return false;
    }

    vk_copy_buffer(
        staging_buffer,
        *buffer,
        size
    );

    /*
     * Safe only if vk_end_commands() waits for the copy to finish.
     */
    vk_destroy_buffer(
        staging_buffer,
        staging_memory
    );

    return true;
}


/************
 * COMMANDS *
 ************/


VkCommandBuffer vk_begin_commands()
{
	VkCommandBufferAllocateInfo alloc_info = {
		.sType       = VK_STRUCTURE_TYPE_COMMAND_BUFFER_ALLOCATE_INFO,
		.level       = VK_COMMAND_BUFFER_LEVEL_PRIMARY,
		.commandPool = vk.cmd_pool,
		.commandBufferCount = 1,
	};
	VkCommandBuffer cmdbuf;
	vkAllocateCommandBuffers(vk.dev, &alloc_info, &cmdbuf);

	VkCommandBufferBeginInfo begin_info = {
		.sType = VK_STRUCTURE_TYPE_COMMAND_BUFFER_BEGIN_INFO,
		.flags = VK_COMMAND_BUFFER_USAGE_ONE_TIME_SUBMIT_BIT,
	};

	vkBeginCommandBuffer(cmdbuf, &begin_info);
	return cmdbuf;
}

void vk_end_commands(VkCommandBuffer cmdbuf)
{
	vkEndCommandBuffer(cmdbuf);

	VkSubmitInfo submit_info = {
		.sType = VK_STRUCTURE_TYPE_SUBMIT_INFO,
		.commandBufferCount = 1,
		.pCommandBuffers = &cmdbuf,
	};

	vkQueueSubmit(vk.graphics_queue, 1, &submit_info, VK_NULL_HANDLE);
	vkQueueWaitIdle(vk.graphics_queue);

	vkFreeCommandBuffers(vk.dev, vk.cmd_pool, 1, &cmdbuf);
}

VkFormat vk_find_supported_format( 
	VkFormat *formats,
	size_t    formats_num,
	VkImageTiling tiling, 
	VkFormatFeatureFlags features 
){
	for (int i = 0; i < formats_num; i++){
		VkFormatProperties props;
		vkGetPhysicalDeviceFormatProperties(vk.dev_physical, formats[i], &props);

		if (tiling == VK_IMAGE_TILING_LINEAR 
		&& (props.linearTilingFeatures & features) == features)
			return formats[i];

		if (tiling == VK_IMAGE_TILING_OPTIMAL 
		&& (props.optimalTilingFeatures & features) == features)
			return formats[i];

	}
	engine_crash("No supported formats");
	return 0;
}

bool vk_has_stencil(VkFormat format)
{
	return format == VK_FORMAT_D32_SFLOAT_S8_UINT 
		|| format == VK_FORMAT_D24_UNORM_S8_UINT;
}

VkFormat vk_find_depth_format()
{
	VkFormat formats[] = {
		VK_FORMAT_D32_SFLOAT, 
		VK_FORMAT_D32_SFLOAT_S8_UINT, 
		VK_FORMAT_D24_UNORM_S8_UINT
	};
	return vk_find_supported_format(
		formats, 
		LENGTH(formats), 
		VK_IMAGE_TILING_OPTIMAL, 
		VK_FORMAT_FEATURE_DEPTH_STENCIL_ATTACHMENT_BIT
	);
}


VkShaderModule vk_create_shader_module(enum Resource file)
{
	size_t spv_size;
	char  *spv = res_file(file, &spv_size);
	
	if (!spv) engine_crash("Missing spv file");

	VkShaderModuleCreateInfo create_info = {
		.sType     = VK_STRUCTURE_TYPE_SHADER_MODULE_CREATE_INFO,
		.codeSize = spv_size,
		.pCode    = (void*)spv,
	};
	VkShaderModule shader_module;
	VkResult ret  = vkCreateShaderModule(vk.dev, &create_info, NULL, &shader_module);
	free(spv);
	if(ret != VK_SUCCESS) engine_crash("vkCreateShaderModule failed");
	
	return shader_module;
}



/*
 * Images
 */

void vk_transition_image_layout(
	VkImage       image,
	VkFormat      format,
	VkImageLayout old_layout,
	VkImageLayout new_layout
){
	VkCommandBuffer cmdbuf = vk_begin_commands();

	VkImageMemoryBarrier barrier = {
		.sType      = VK_STRUCTURE_TYPE_IMAGE_MEMORY_BARRIER,
		.oldLayout  = old_layout,
		.newLayout  = new_layout,
		.srcQueueFamilyIndex = VK_QUEUE_FAMILY_IGNORED,
		.dstQueueFamilyIndex = VK_QUEUE_FAMILY_IGNORED,
		.image = image,
		.subresourceRange = {
			.aspectMask     = VK_IMAGE_ASPECT_COLOR_BIT,
			.baseMipLevel   = 0,
			.levelCount     = 1,
			.baseArrayLayer = 0,
			.layerCount     = 1,
		},
		// TODO
		.srcAccessMask = 0,
		.dstAccessMask = 0,
	};
	
	VkPipelineStageFlags src_stage;
	VkPipelineStageFlags dst_stage;

	if (old_layout == VK_IMAGE_LAYOUT_UNDEFINED 
	 && new_layout == VK_IMAGE_LAYOUT_TRANSFER_DST_OPTIMAL ) 
	{
		barrier.srcAccessMask = 0;
		barrier.dstAccessMask = VK_ACCESS_TRANSFER_WRITE_BIT;
		src_stage             = VK_PIPELINE_STAGE_TOP_OF_PIPE_BIT;
		dst_stage             = VK_PIPELINE_STAGE_TRANSFER_BIT;
	} 
	else 
	if (old_layout == VK_IMAGE_LAYOUT_TRANSFER_DST_OPTIMAL 
	 && new_layout == VK_IMAGE_LAYOUT_SHADER_READ_ONLY_OPTIMAL ) 
	{
		barrier.srcAccessMask = VK_ACCESS_TRANSFER_WRITE_BIT;
		barrier.dstAccessMask = VK_ACCESS_SHADER_READ_BIT;
		src_stage             = VK_PIPELINE_STAGE_TRANSFER_BIT;
		dst_stage             = VK_PIPELINE_STAGE_FRAGMENT_SHADER_BIT;
	} else {
		engine_crash("Unsupported layout transition");
	}

	vkCmdPipelineBarrier(
		cmdbuf,
		src_stage, dst_stage,
		0,
		0, NULL,
		0, NULL,
		1, &barrier
	);
	vk_end_commands(cmdbuf);
}

void vk_copy_buffer_to_image(
	VkBuffer buffer,
	VkImage  image,
	uint32_t width,
	uint32_t height
){
	VkCommandBuffer cmdbuf = vk_begin_commands();
	
	VkBufferImageCopy region = {
		.bufferOffset = 0,
		.bufferRowLength = 0,
		.bufferImageHeight = 0,

		.imageSubresource = {
			.aspectMask = VK_IMAGE_ASPECT_COLOR_BIT,
			.mipLevel = 0,
			.baseArrayLayer = 0,
			.layerCount = 1,
		},
		.imageOffset = {0,0,0},
		.imageExtent = {
			width,
			height,
			1
		},
	};

	vkCmdCopyBufferToImage(
		cmdbuf,
		buffer,
		image,
		VK_IMAGE_LAYOUT_TRANSFER_DST_OPTIMAL, 
		1, 
		&region
	);
	
	vk_end_commands(cmdbuf);
}
