#ifndef SRC_ENGINE_GFX_GFX_TYPES_H
#define SRC_ENGINE_GFX_GFX_TYPES_H

#include "common.h"

#include <vulkan/vulkan.h>
#include <GLFW/glfw3.h>
#include <vk_mem_alloc.h>

#define CGLM_FORCE_DEPTH_ZERO_TO_ONE
#include <cglm/cglm.h>

#include "array.h"

#define VK_FRAMES 3

typedef struct VkFrame 
{
	uint32_t         id;

	VkSemaphore      image_available;
	VkSemaphore      render_finished;
	VkFence          flight;
	
	VkCommandPool    cmd_pool;
	VkCommandBuffer  cmd_buf;

	uint32_t         image_index;
	/// DRE 2026
	VkSemaphore nk_render_finished;	
}VkFrame;

typedef struct NkVkImage
{
    VkImage       image;
    VmaAllocation allocation;
    VkImageView   view;
} NkVkImage;


typedef struct VkEngine
{
    /*
     * Window and application state
     */

    GLFWwindow *window;

    char   dev_name[1024];
    bool   _verbose;
    double last_resize;


    /*
     * Validation and debug state
     */

    bool                     debug;
    VkDebugUtilsMessengerEXT messenger;


    /*
     * Vulkan instance and surface
     */

    VkInstance   instance;
    VkSurfaceKHR surface;

    /*
     * Physical-device and logical-device state
     */

    VkPhysicalDevice           dev_physical;
    VkPhysicalDeviceProperties dev_properties;
    VkDevice                   dev;		/// aka logical device

    VmaAllocator vma;
    /*
     * Queue-family selection
     */

    uint32_t family_graphics;
    bool     family_graphics_valid;

    uint32_t family_presentation;
    bool     family_presentation_valid;
    /*
     * Vulkan extension and validation-layer availability
     */
    Array(VkExtensionProperties) instance_ext_avbl;
    Array(const char *)          instance_ext_req;

    Array(VkExtensionProperties) device_ext_avbl;
    Array(const char *)          device_ext_req;

    Array(VkLayerProperties)     validation_avbl;
    Array(const char *)          validation_req;

    /*
     * Device queues
     */

    VkQueue graphics_queue;
    VkQueue present_queue;

    /*
     * Swapchain
     */
    VkSwapchainKHR swapchain;

    VkImage     *swapchain_img;
    VkImageView *swapchain_img_view;

    uint32_t    swapchain_img_num;
    VkFormat    swapchain_img_format;
    VkExtent2D  swapchain_extent;
    /*
     * Depth buffer
     */
    VkImage       depth_image;
    VmaAllocation depth_alloc;
    VkImageView   depth_view;
    /*
     * Render targets
     */

    VkRenderPass   renderpass;
    VkFramebuffer *framebuffers;
    uint32_t       framebuffers_num;
    bool framebuffer_resize;
    /*
     * Frame synchronization and image ownership
     */
    VkFrame frames[VK_FRAMES];

    /*
     * One fence per swapchain image, if used as an images-in-flight
     * tracking array. Rename this to images_in_flight if that is its
     * actual purpose.
     */
    VkFence   *fence_image;
    uint32_t   current_frame;


    /*
     * Command infrastructure
     */

    /*
     * Primarily used for short-lived staging operations.
     * Per-frame rendering command pools and command buffers are stored
     * in VkFrame.
     */
    VkCommandPool cmd_pool;

    /*
     * Transfer and staging resources
     */

    VkBuffer       staging_buffer;
    VmaAllocation  staging_alloc;


    /*
     * Shared rendering objects
     */

    /*
     * Used by texture uploads and other engine-level image operations.
     * Nuklear may use this sampler, but does not own it.
     */
    VkSampler texture_sampler;

    /*
     * Shared descriptor pool used when creating engine and UI
     * descriptor sets. The pool remains owned by VkEngine.
     */
    VkDescriptorPool descriptor_pool;


    VkPipelineCache pipeline_cache;

    /*
     * Nuklear / WidgetRenderer integration
     *
     * Nuklear Vulkan resources are owned by WidgetRenderer, not by
     * VkEngine. Keep only a reference here if the engine needs to access
     * the UI renderer during frame recording.
     */

    struct WidgetRenderer *widget_renderer;
}VkEngine;

/**
 * CODE MIGRATION
 *
 * Old nk_glfw_device / nk_glfw field                  New location
 *
 * --------------------------------------------------------------------------
 * Nuklear CPU-side state
 * --------------------------------------------------------------------------
 *
 * dev->cmds                                             wr->cmds
 * dev->tex_null                                         wr->tex_null
 *
 * glfw->ctx                                             wr->ctx
 * glfw->atlas                                           wr->atlas
 *
 *
 * --------------------------------------------------------------------------
 * Nuklear pipeline state
 * --------------------------------------------------------------------------
 *
 * dev->uniform_descriptor_set_layout                    wr->uniform_descriptor_set_layout
 * dev->uniform_descriptor_set                           wr->uniform_descriptor_set
 * dev->texture_descriptor_set_layout                    wr->texture_descriptor_set_layout
 *
 * dev->pipeline_layout                                  wr->pipeline_layout
 * dev->pipeline                                         wr->pipeline
 *
 *
 * --------------------------------------------------------------------------
 * Nuklear vertex/index buffers
 * --------------------------------------------------------------------------
 *
 * dev->max_vertex_buffer                                wr->frame[frame].max_vertex_buffer
 * dev->max_element_buffer                               wr->frame[frame].max_element_buffer
 *
 * dev->vertex_buffer                                    wr->frame[frame].vertex_buffer
 * dev->vertex_memory                                    wr->frame[frame].vertex_alloc
 * dev->mapped_vertex                                    wr->frame[frame].mapped_vertex
 *
 * dev->index_buffer                                     wr->frame[frame].index_buffer
 * dev->index_memory                                     wr->frame[frame].index_alloc
 * dev->mapped_index                                     wr->frame[frame].mapped_index
 *
 * If the implementation still uses one shared buffer rather than one
 * buffer per frame, the destination can temporarily be:
 *
 * dev->vertex_buffer                                    wr->vertex_buffer
 * dev->vertex_memory                                    wr->vertex_alloc
 * dev->mapped_vertex                                    wr->mapped_vertex
 *
 * dev->index_buffer                                     wr->index_buffer
 * dev->index_memory                                     wr->index_alloc
 * dev->mapped_index                                     wr->mapped_index
 *
 *
 * --------------------------------------------------------------------------
 * Nuklear uniform resources
 * --------------------------------------------------------------------------
 *
 * dev->uniform_buffer                                    wr->frame[frame].uniform_buffer
 * dev->uniform_memory                                    wr->frame[frame].uniform_alloc
 * dev->mapped_uniform                                    wr->frame[frame].mapped_uniform
 * dev->uniform_descriptor_set                           wr->frame[frame].uniform_descriptor_set
 *
 * If the uniform buffer is shared by all frames, the temporary destination
 * can be:
 *
 * dev->uniform_buffer                                   wr->uniform_buffer
 * dev->uniform_memory                                   wr->uniform_alloc
 * dev->mapped_uniform                                   wr->mapped_uniform
 * dev->uniform_descriptor_set                           wr->uniform_descriptor_set
 *
 *
 * --------------------------------------------------------------------------
 * Nuklear texture descriptors
 * --------------------------------------------------------------------------
 *
 * dev->texture_descriptor_sets                          wr->texture_descriptor_sets
 * dev->texture_descriptor_sets_len                      wr->texture_descriptor_sets_len
 *
 * New field:
 *
 *                                                         wr->texture_descriptor_sets_capacity
 *
 * The texture descriptor array is owned by WidgetRenderer because it
 * represents Nuklear texture/image handles.
 *
 *
 * --------------------------------------------------------------------------
 * Nuklear font resources
 * --------------------------------------------------------------------------
 *
 * dev->font_image                                        wr->font_image
 * dev->font_memory                                       wr->font_alloc
 * dev->font_image_view                                   wr->font_image_view
 *
 * New field:
 *
 *                                                         wr->font_descriptor_set
 *
 * The font image, image view, allocation, and descriptor set belong to the
 * WidgetRenderer together with wr->atlas.
 *
 *
 * --------------------------------------------------------------------------
 * Window and swapchain dimensions
 * --------------------------------------------------------------------------
 *
 * glfw->win                                             vk->window
 *
 * glfw->width                                           win_get_width()
 * glfw->height                                          win_get_height()
 *
 * glfw->display_width                                   vk->swapchain_extent.width
 * glfw->display_height                                  vk->swapchain_extent.height
 *
 * Do not copy display dimensions into WidgetRenderer unless a separate
 * logical UI resolution is required. Use:
 *
 *                                                         vk->swapchain_extent.width
 *                                                         vk->swapchain_extent.height
 *
 *
 * --------------------------------------------------------------------------
 * Widget input and UI state
 * --------------------------------------------------------------------------
 *
 * glfw->fb_scale                                       wr->fb_scale
 * glfw->text                                           wr->text
 * glfw->key_events                                     wr->key_events
 * glfw->text_len                                       wr->text_len
 * glfw->scroll                                         wr->scroll
 *
 * glfw->last_button_click                              wr->last_button_click
 * glfw->is_double_click_down                           wr->is_double_click_down
 * glfw->double_click_pos                               wr->double_click_pos
 * glfw->delta_time_seconds_last                       wr->delta_time_seconds_last
 *
 *
 * --------------------------------------------------------------------------
 * Engine-owned Vulkan resources
 * --------------------------------------------------------------------------
 *
 * These old backend fields should not be migrated into WidgetRenderer:
 *
 * old field                                             New location
 *
 * dev->logical_device                                  vk->dev
 * dev->physical_device                                 vk->dev_physical
 *
 * dev->image_views                                     vk->swapchain_img_view
 * dev->image_views_len                                 vk->swapchain_img_num
 * dev->color_format                                    vk->swapchain_img_format
 *
 * dev->framebuffers                                    vk->framebuffers
 * dev->framebuffers_len                                vk->framebuffers_num
 *
 * dev->render_pass                                     vk->renderpass
 * dev->sampler                                         vk->texture_sampler
 * dev->descriptor_pool                                 vk->descriptor_pool
 * dev->command_pool                                    vk->cmd_pool
 *
 * These remain owned by VkEngine because they are swapchain, device,
 * synchronization, or shared Vulkan resources.
 *
 *
 * --------------------------------------------------------------------------
 * Removed or replaced fields
 * --------------------------------------------------------------------------
 *
 * dev->vertex_memory                                    replaced by VmaAllocation
 * dev->index_memory                                     replaced by VmaAllocation
 * dev->uniform_memory                                   replaced by VmaAllocation
 * dev->font_memory                                      replaced by VmaAllocation
 *
 * dev->render_completed                                replaced by the
 *                                                       appropriate VkFrame
 *                                                       semaphore
 *
 * dev->image_views_len                                 replaced by
 *                                                       vk->swapchain_img_num
 *
 * dev->framebuffers_len                                replaced by
 *                                                       vk->framebuffers_num
 *
 * NkVk::ctx                                             removed
 *
 * NkVk::render_pass                                     removed
 * NkVk::framebuffers                                    removed
 * NkVk::framebuffers_num                                removed
 * NkVk::display_width                                  removed
 * NkVk::display_height                                 removed
 *
 * WidgetRenderer should use VkEngine's renderpass, framebuffers, and
 * swapchain extent while recording commands instead of storing duplicate
 * copies of those handles.
 */

#endif /* SRC_ENGINE_GFX_GFX_TYPES_H */
