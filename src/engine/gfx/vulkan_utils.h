///
/// Copyright 2019 Govind Pimpale
/// vulkan_methods.h
///
///  Created on: Aug 8, 2018
///      Author: gpi
///

#ifndef SRC_VULKAN_UTILS_H_
#define SRC_VULKAN_UTILS_H_

#include <stdbool.h>
#include <stdint.h>

#include <vulkan/vulkan.h>

#define GLFW_INCLUDE_VULKAN
#include <GLFW/glfw3.h>

#include "errors.h"
#include "vertex.h"



ErrVal new_Buffer_DeviceMemory(VkBuffer *pBuffer, VkDeviceMemory *pBufferMemory,
                               const VkDeviceSize size,
                               const VkPhysicalDevice physicalDevice,
                               const VkDevice device,
                               const VkBufferUsageFlags usage,
                               const VkMemoryPropertyFlags properties);


void delete_DeviceMemory(VkDeviceMemory *pDeviceMemory, const VkDevice device);

#endif /* SRC_VULKAN_UTILS_H_ */
