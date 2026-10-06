

struct WidgetUniform
{
    mat4 ortho;
};

struct WidgetVertex
{
    float    pos  [2];
    uint8_t  color[4];
    uint16_t depth;
};
typedef Handle WidgetRendererHandle;
 
//! to avoid define race conditions and extra files any needed pre-nuklear defines are made here  
struct wr_vec2 {float x,y;};
typedef NK_INT8 wr_char;

struct WidgetFrameData {
    VkBuffer       uniform_buffer;
    VmaAllocation  uniform_alloc;
    void          *mapped_uniform;
    VkDescriptorSet uniform_descriptor_set;

    VkBuffer       vertex_buffer;
    VmaAllocation  vertex_alloc;
    void          *mapped_vertex;

    VkBuffer       index_buffer;
    VmaAllocation  index_alloc;
    void          *mapped_index;

    uint32_t max_vertex_buffer;
    uint32_t max_element_buffer;
};

typedef struct nk_vulkan_texture_descriptor_set 
{
    VkImageView     image_view;
    VkDescriptorSet descriptor_set;
} NkVulkanTextureDescriptorSet;

/**
 * This gives WidgetRenderer control of all Nuklear draw operations without making it responsible for swapchain lifetime or window resizing.

The resulting ownership is:
text

VkEngine
 ├── device, allocator, queues
 ├── swapchain and framebuffers
 ├── render pass
 ├── shared descriptor pool and sampler
 └── VkFrame synchronization

WidgetRenderer
 ├── nk_context and nk_font_atlas
 ├── Nuklear command buffer
 ├── Nuklear pipeline
 ├── Nuklear descriptor layouts
 ├── Nuklear uniform/vertex/index buffers
 ├── Nuklear texture descriptors
 ├── Nuklear font image and descriptor
 └── all Nuklear draw/recording functions
 
 Your ownership split is therefore:

Owned by VkEngine:

    VkInstance
    VkSurfaceKHR
    VkPhysicalDevice
    VkDevice
    VmaAllocator
    Queues and queue-family indices
    Swapchain images and image views
    Depth resources
    Render pass
    Framebuffers
    Command pools
    Staging resources
    Synchronization objects
    Shared sampler
    Shared descriptor pool
    GLFWwindow

Owned by WidgetRenderer:

    Nuklear context, atlas, buffers, and style state
    GLFW input callbacks and input state
    Nuklear pipeline and pipeline layout
    Nuklear descriptor-set layouts
    Per-frame UI buffers and allocations
    Font image, allocation, image view, and descriptor set
    Registered texture descriptor records
    Application-specific widget state
    UI texture descriptors and images created specifically for the renderer

 
 * */
struct VkFrame 
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
};

struct VkEngine
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
    VkDevice                   dev;

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

    struct VkFrame frames[VK_FRAMES];

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


    /*
     * Nuklear / WidgetRenderer integration
     *
     * Nuklear Vulkan resources are owned by WidgetRenderer, not by
     * VkEngine. Keep only a reference here if the engine needs to access
     * the UI renderer during frame recording.
     */

    struct WidgetRenderer *widget_renderer;
};


typedef struct WidgetRenderer {
    /* Application/UI ownership */
    TextEngine engine;

    struct nk_context    ctx;
    struct nk_font_atlas atlas;

    struct nk_buffer           cmds;
    struct nk_draw_null_texture tex_null;

    struct wr_vec2 fb_scale;
    struct wr_vec2 scroll;

    unsigned int text[NK_GLFW_TEXT_MAX];
    wr_char key_events[NK_KEY_MAX];
    int text_len;

    double last_button_click;
    int is_double_click_down;
    struct wr_vec2 double_click_pos;
    float delta_time_seconds_last;

    /* Nuklear graphics pipeline */
    VkPipeline       pipeline;
    VkPipelineLayout pipeline_layout;

    VkDescriptorSetLayout uniform_descriptor_set_layout;
    VkDescriptorSetLayout texture_descriptor_set_layout;

    /* Per-frame Nuklear GPU resources */
    struct WidgetFrameData frame[VK_FRAMES];

    /* Nuklear texture registry */
    NkVulkanTextureDescriptorSet *texture_descriptor_sets;
    uint32_t texture_descriptor_sets_len;
    uint32_t texture_descriptor_sets_capacity;

    /* Nuklear font texture */
    VkImage          font_image;
    VmaAllocation     font_alloc;
    VkImageView       font_image_view;
    VkDescriptorSet   font_descriptor_set;

} WidgetRenderer;
