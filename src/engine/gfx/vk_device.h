#ifndef SRC_ENGINE_GFX_VK_DEVICE_H
#define SRC_ENGINE_GFX_VK_DEVICE_H

#include <vulkan/vulkan.h>

VkDevice vk_create_device(void);

void vk_device_ext_add(const char *ext);

#endif /* SRC_ENGINE_GFX_VK_DEVICE_H */
