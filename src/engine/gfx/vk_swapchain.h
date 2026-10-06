#ifndef SRC_ENGINE_GFX_VK_SWAPCHAIN_H
#define SRC_ENGINE_GFX_VK_SWAPCHAIN_H

#include <vulkan/vulkan.h>

struct VkSwapchainDetails {
	VkSurfaceCapabilitiesKHR capabilities;
	VkSurfaceFormatKHR      *format;
	uint32_t                 format_num;
	VkPresentModeKHR        *pmode;
	uint32_t                 pmode_num;
};

// Remember to free with vk_swapchain_details_free(&details) !
void 
vk_swapchain_details_free(struct VkSwapchainDetails**);

struct VkSwapchainDetails *
vk_swapchain_details(VkPhysicalDevice);


void vk_create_swapchain(void);
void vk_create_image_views(void);
void vk_destroy_swapchain(void);

#endif /* SRC_ENGINE_GFX_VK_SWAPCHAIN_H */
