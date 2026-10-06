#include "vulkan_utils.h"

#include <errno.h>
#include <inttypes.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>

#include <vulkan/vulkan.h>



int new_Buffer_DeviceMemory(VkBuffer *pBuffer, VkDeviceMemory *pBufferMemory,
                               const VkDeviceSize size,
                               const VkPhysicalDevice physicalDevice,
                               const VkDevice device,
                               const VkBufferUsageFlags usage,
                               const VkMemoryPropertyFlags properties)
{
    VkBufferCreateInfo bufferInfo = {0};
    bufferInfo.sType = VK_STRUCTURE_TYPE_BUFFER_CREATE_INFO;
    bufferInfo.size = size;
    bufferInfo.usage = usage;
    bufferInfo.sharingMode = VK_SHARING_MODE_EXCLUSIVE;
    /* Create buffer */
    VkResult bufferCreateResult = vkCreateBuffer(device, &bufferInfo, NULL, pBuffer);
    if (bufferCreateResult != VK_SUCCESS)
    {
        log_info( "failed to create buffer: ");
        return (ERR_UNKNOWN);
    }
    /* Allocate memory for buffer */
    VkMemoryRequirements memoryRequirements;
    vkGetBufferMemoryRequirements(device, *pBuffer, &memoryRequirements);

    VkMemoryAllocateInfo allocateInfo = {0};
    allocateInfo.sType = VK_STRUCTURE_TYPE_MEMORY_ALLOCATE_INFO;
    allocateInfo.allocationSize = memoryRequirements.size;
    /* Get the type of memory required, handle errors */
    bool getMemoryTypeRetVal = vk_find_memory_type( &allocateInfo.memoryTypeIndex, properties, memoryRequirements.memoryTypeBits);
    if (getMemoryTypeRetVal != true)
    {
        log_info( "failed to get type of memory to allocate");
        return (VK_ERROR_MEMORY_MAP_FAILED);
    }

    /* Actually allocate memory */
    VkResult memoryAllocateResult = vkAllocateMemory(device, &allocateInfo, NULL, pBufferMemory);
    if (memoryAllocateResult != VK_SUCCESS)
    {
        log_info( "failed to allocate memory for buffer: %s",  );
        return (VK_ERROR_MEMORY_MAP_FAILED);
    }
    vkBindBufferMemory(device, *pBuffer, *pBufferMemory, 0);
    return (VK_ERROR_UNKNOWN);
}

void delete_DeviceMemory(VkDeviceMemory *pDeviceMemory, const VkDevice device)
{
    vkFreeMemory(device, *pDeviceMemory, NULL);
    *pDeviceMemory = VK_NULL_HANDLE;
}

