/** \file widget_renderer.c
 * 
 * Includes Immediate Mode GUI code in one place only
 * 
 * The important rules are:

    NK_PRIVATE must be defined before the first inclusion of nuklear.h.
    nuklear.h must be included before widget_renderer_helper.h.
    NK_IMPLEMENTATION must be defined in exactly one .c file.
    NK_GLFW3_IMPLEMENTATION must also be defined in exactly one .c file.
    Do not define either implementation macro in gfx.c.

Your helper header should also include its own dependencies rather than relying entirely on include order:
 * 
 * */
/*! #include "nuklear_config.h" holds NUKLEAR configuration #defines
 * NK_PRIVATE exposes the full definitions of structures such as:
 *
 *     struct nk_context
 *     struct nk_font_atlas
 *     struct nk_buffer
 *     struct nk_draw_null_texture
 */
#define NK_INCLUDE_FIXED_TYPES
#define NK_INCLUDE_STANDARD_IO
#define NK_INCLUDE_STANDARD_VARARGS
#define NK_INCLUDE_DEFAULT_ALLOCATOR
#define NK_INCLUDE_VERTEX_BUFFER_OUTPUT
#define NK_INCLUDE_FONT_BAKING
#define NK_INCLUDE_DEFAULT_FONT

/*
 * Required because WidgetRenderer embeds Nuklear structs by value.
 */

#define NK_PRIVATE
#define NK_API extern
#define NK_IMPLEMENTATION
#include "nuklear.h"
#undef NK_IMPLEMENTATION

#include "widget_renderer.h"
#include "widget_renderer_helper.h"

extern struct VkEngine vk;

uint32_t index_offset = 0;
// global data struct held in scope and hidden location in file
WidgetRenderer wr;

static struct HandleAllocator alloc = HANDLE_ALLOCATOR( WidgetRendererHandle, 1);


///
// DRE 2026
///


NK_API void
nk_glfw3_char_callback(GLFWwindow *win, unsigned int codepoint)
{
    WidgetRenderer *wr =
        (WidgetRenderer *)glfwGetWindowUserPointer(win);

    if (!wr)
        return;

    if (wr->text_len < NK_GLFW_TEXT_MAX)
        wr->text[wr->text_len++] = codepoint;
}


NK_API void
nk_glfw3_key_callback(GLFWwindow *win,
                      int key,
                      int scancode,
                      int action,
                      int mods)
{
    static int insert_toggle = 0;

    WidgetRenderer *wr =
        (WidgetRenderer *)glfwGetWindowUserPointer(win);

    if (!wr)
        return;

    /*
     * GLFW_REPEAT is treated as a pressed key so Nuklear receives
     * continuous key events while a key is held.
     */
    nk_char pressed =
        (action == GLFW_RELEASE) ? nk_false : nk_true;

    NK_UNUSED(scancode);
    NK_UNUSED(mods);

    switch (key)
    {
    case GLFW_KEY_DELETE:
        wr->key_events[NK_KEY_DEL] = pressed;
        break;

    case GLFW_KEY_TAB:
        wr->key_events[NK_KEY_TAB] = pressed;
        break;

    case GLFW_KEY_BACKSPACE:
        wr->key_events[NK_KEY_BACKSPACE] = pressed;
        break;

    case GLFW_KEY_UP:
        wr->key_events[NK_KEY_UP] = pressed;
        break;

    case GLFW_KEY_DOWN:
        wr->key_events[NK_KEY_DOWN] = pressed;
        break;

    case GLFW_KEY_LEFT:
        wr->key_events[NK_KEY_LEFT] = pressed;
        break;

    case GLFW_KEY_RIGHT:
        wr->key_events[NK_KEY_RIGHT] = pressed;
        break;

    case GLFW_KEY_ESCAPE:
        wr->key_events[NK_KEY_TEXT_RESET_MODE] = pressed;
        break;

    case GLFW_KEY_LEFT_ALT:
    case GLFW_KEY_RIGHT_ALT:
        wr->key_events[NK_KEY_ALT] = pressed;
        break;

    case GLFW_KEY_PAGE_UP:
        wr->key_events[NK_KEY_SCROLL_UP] = pressed;
        break;

    case GLFW_KEY_PAGE_DOWN:
        wr->key_events[NK_KEY_SCROLL_DOWN] = pressed;
        break;

    case GLFW_KEY_F1:
        wr->key_events[NK_KEY_F1] = pressed;
        break;

    case GLFW_KEY_F2:
        wr->key_events[NK_KEY_F2] = pressed;
        break;

    case GLFW_KEY_F3:
        wr->key_events[NK_KEY_F3] = pressed;
        break;

    case GLFW_KEY_F4:
        wr->key_events[NK_KEY_F4] = pressed;
        break;

    case GLFW_KEY_F5:
        wr->key_events[NK_KEY_F5] = pressed;
        break;

    case GLFW_KEY_F6:
        wr->key_events[NK_KEY_F6] = pressed;
        break;

    case GLFW_KEY_F7:
        wr->key_events[NK_KEY_F7] = pressed;
        break;

    case GLFW_KEY_F8:
        wr->key_events[NK_KEY_F8] = pressed;
        break;

    case GLFW_KEY_F9:
        wr->key_events[NK_KEY_F9] = pressed;
        break;

    case GLFW_KEY_F10:
        wr->key_events[NK_KEY_F10] = pressed;
        break;

    case GLFW_KEY_F11:
        wr->key_events[NK_KEY_F11] = pressed;
        break;

    case GLFW_KEY_F12:
        wr->key_events[NK_KEY_F12] = pressed;
        break;

    /*
     * Text editing and clipboard shortcuts.
     */
    case GLFW_KEY_C:
        wr->key_events[NK_KEY_COPY] = pressed;
        break;

    case GLFW_KEY_V:
        wr->key_events[NK_KEY_PASTE] = pressed;
        break;

    case GLFW_KEY_X:
        wr->key_events[NK_KEY_CUT] = pressed;
        break;

    case GLFW_KEY_Z:
        wr->key_events[NK_KEY_TEXT_UNDO] = pressed;
        break;

    case GLFW_KEY_R:
        wr->key_events[NK_KEY_TEXT_REDO] = pressed;
        break;

    case GLFW_KEY_B:
        wr->key_events[NK_KEY_TEXT_LINE_START] = pressed;
        break;

    case GLFW_KEY_E:
        wr->key_events[NK_KEY_TEXT_LINE_END] = pressed;
        break;

    case GLFW_KEY_A:
        wr->key_events[NK_KEY_TEXT_SELECT_ALL] = pressed;
        break;

    case GLFW_KEY_ENTER:
    case GLFW_KEY_KP_ENTER:
        wr->key_events[NK_KEY_ENTER] = pressed;
        break;

    case GLFW_KEY_INSERT:
        /*
         * Toggle insert/replace mode only on release. This prevents
         * GLFW_REPEAT from toggling the mode multiple times.
         */
        if (!pressed)
        {
            insert_toggle = !insert_toggle;

            if (insert_toggle)
            {
                wr->key_events[NK_KEY_TEXT_INSERT_MODE] = nk_true;
                wr->key_events[NK_KEY_TEXT_REPLACE_MODE] = nk_false;
            }
            else
            {
                wr->key_events[NK_KEY_TEXT_INSERT_MODE] = nk_false;
                wr->key_events[NK_KEY_TEXT_REPLACE_MODE] = nk_true;
            }
        }
        break;

    default:
        break;
    }
}
/**
 * 
 * glfw.text       -> wr->text
glfw.text_len   -> wr->text_len
glfw.key_events -> wr->key_events
glfw.scroll     -> wr->scroll
 * */
NK_API void
nk_glfw3_scroll_callback(GLFWwindow *win,
                         double xoff,
                         double yoff)
{
    WidgetRenderer *wr =
        (WidgetRenderer *)glfwGetWindowUserPointer(win);

    if (!wr)
        return;

    wr->scroll.x += (float)xoff;
    wr->scroll.y += (float)yoff;
}

NK_API void
nk_glfw3_mouse_button_callback(GLFWwindow *window,
                               int button,
                               int action,
                               int mods)
{
    WidgetRenderer *wr =
        (WidgetRenderer *)glfwGetWindowUserPointer(window);

    NK_UNUSED(mods);

    if (!wr || button != GLFW_MOUSE_BUTTON_LEFT)
        return;

    double x;
    double y;

    glfwGetCursorPos(window, &x, &y);
    // DRE 2-26 
    // Set the window user pointer separately:
    // glfwSetWindowUserPointer(vk.window, wr);

    if (action == GLFW_PRESS)
    {
        double now = glfwGetTime();
        double dt = now - wr->last_button_click;

        if (dt > NK_GLFW_DOUBLE_CLICK_LO &&
            dt < NK_GLFW_DOUBLE_CLICK_HI)
        {
            wr->is_double_click_down = nk_true;
            wr->double_click_pos.x = (float)x;
            wr->double_click_pos.y = (float)y;
        }

        wr->last_button_click = now;
    }
    else if (action == GLFW_RELEASE)
    {
        wr->is_double_click_down = nk_false;
    }
}


 void
nk_glfw3_clipboard_paste(nk_handle usr,
                         struct nk_text_edit *edit)
{
    GLFWwindow *window = (GLFWwindow *)usr.ptr;

    if (!window || !edit)
        return;

    const char *text = glfwGetClipboardString(window);

    if (text)
    {
        nk_textedit_paste(edit, text, nk_strlen(text));
    }
}


 void
nk_glfw3_clipboard_copy(nk_handle usr,
                        const char *text,
                        int len)
{
    GLFWwindow *window = (GLFWwindow *)usr.ptr;

    if (!window || !text || len <= 0)
        return;

    char *str = (char *)malloc((size_t)len + 1);

    if (!str)
        return;

    memcpy(str, text, (size_t)len);
    str[len] = '\0';

    glfwSetClipboardString(window, str);

    free(str);
}


/* wr.atlas is now the owner of the font atlas. */
NK_API void
nk_glfw3_font_stash_begin(struct nk_font_atlas **atlas)
{
    NK_ASSERT(atlas);

    nk_font_atlas_init_default(&wr.atlas);
    nk_font_atlas_begin(&wr.atlas);

    *atlas = &wr.atlas;
}

NK_API void
nk_glfw3_font_stash_end(VkQueue queue)
{
    const void *image;
    int width;
    int height;

    image = nk_font_atlas_bake(&wr.atlas, &width, &height, NK_FONT_ATLAS_RGBA32);

    /*
     * Upload `image` to the GPU using `queue`, then obtain the
     * resulting texture handle.
     */

    nk_font_atlas_end(
        &wr.atlas,
        wr.font_tex,
        &wr.tex_null
    );
}



nk_bool
nk_glfw3_init(
    struct WidgetRenderer *renderer,
    GLFWwindow *window,
    enum nk_glfw_init_state init_state)
{
    if (renderer == NULL || window == NULL)
        return nk_false;

    renderer->window = window;

    glfwGetWindowSize(
        window,
        &renderer->width,
        &renderer->height);

    glfwGetFramebufferSize(
        window,
        &renderer->display_width,
        &renderer->display_height);

    renderer->last_button_click = 0.0;
    renderer->is_double_click_down = nk_false;
    renderer->double_click_pos.x = 0.0f;
    renderer->double_click_pos.y = 0.0f;

    if (init_state == NK_GLFW3_INSTALL_CALLBACKS) {
        glfwSetWindowUserPointer(window, renderer);

        glfwSetScrollCallback(
            window,
            nk_glfw3_scroll_callback);

        glfwSetCharCallback(
            window,
            nk_glfw3_char_callback);

        glfwSetKeyCallback(
            window,
            nk_glfw3_key_callback);

        glfwSetMouseButtonCallback(
            window,
            nk_glfw3_mouse_button_callback);
    }

    renderer->ctx.clip.copy = nk_glfw3_clipboard_copy;
    renderer->ctx.clip.paste = nk_glfw3_clipboard_paste;
    renderer->ctx.clip.userdata = nk_handle_ptr(renderer);

    return nk_true;
}


static void
nk_glfw3_shutdown(
    WidgetRenderer *renderer)
{
    if (renderer == NULL || renderer->window == NULL)
        return;

    if (renderer->callbacks_installed)
    {
        glfwSetScrollCallback(renderer->window, NULL);
        glfwSetCharCallback(renderer->window, NULL);
        glfwSetKeyCallback(renderer->window, NULL);
        glfwSetMouseButtonCallback(renderer->window, NULL);

        renderer->callbacks_installed = false;
    }

    glfwSetWindowUserPointer(renderer->window, NULL);
    renderer->window = NULL;
}


static void
nk_vk_destroy_font_resources(void)
{
    /*
     * The descriptor set belongs to vk.descriptor_pool.
     *
     * The descriptor pool must have been created with:
     *
     * VK_DESCRIPTOR_POOL_CREATE_FREE_DESCRIPTOR_SET_BIT
     */
    if (wr.font_descriptor_set != VK_NULL_HANDLE)
    {
        if (vk.descriptor_pool != VK_NULL_HANDLE)
        {
            VkResult result = vkFreeDescriptorSets(
                vk.dev,
                vk.descriptor_pool,
                1,
                &wr.font_descriptor_set);

            if (result != VK_SUCCESS)
            {
                LOG_ERROR_ARGS(
                    ERR_LEVEL_ERROR,
                    "failed to free font descriptor set: %s",
                    vkstrerror(result));
            }
        }

        wr.font_descriptor_set = VK_NULL_HANDLE;
    }

    /*
     * The image view must be destroyed before the image.
     */
    if (wr.font_image_view != VK_NULL_HANDLE)
    {
        vkDestroyImageView(
            vk.dev,
            wr.font_image_view,
            NULL);

        wr.font_image_view = VK_NULL_HANDLE;
    }

    /*
     * Destroy the image before freeing its memory.
     */
    if (wr.font_image != VK_NULL_HANDLE)
    {
        vkDestroyImage(
            vk.dev,
            wr.font_image,
            NULL);

        wr.font_image = VK_NULL_HANDLE;
    }

    /*
     * Vulkan device memory replaces the old VmaAllocation.
     */
    if (wr.font_memory != VK_NULL_HANDLE)
    {
        vkFreeMemory(
            vk.dev,
            wr.font_memory,
            NULL);

        wr.font_memory = VK_NULL_HANDLE;
    }

    /*
     * This must happen after Nuklear is finished using the atlas.
     */
    nk_font_atlas_clear(&wr.atlas);

    wr.font_tex = nk_handle_ptr(NULL);
}


static void
nk_vk_reset_renderer(void)
{
    /*
     * Save descriptor layouts before clearing the renderer state.
     */
    VkDescriptorSetLayout uniform_layout =
        wr.uniform_descriptor_set_layout;

    VkDescriptorSetLayout texture_layout =
        wr.texture_descriptor_set_layout;

    /*
     * Destroy descriptor layouts only after all descriptor sets,
     * pipelines, and pipeline layouts using them are no longer in use.
     */
    if (uniform_layout != VK_NULL_HANDLE) {
        vkDestroyDescriptorSetLayout(
            vk.dev,
            uniform_layout,
            NULL
        );
    }

    if (texture_layout != VK_NULL_HANDLE &&
        texture_layout != uniform_layout) {
        vkDestroyDescriptorSetLayout(
            vk.dev,
            texture_layout,
            NULL
        );
    }

    wr.pipeline = VK_NULL_HANDLE;
    wr.pipeline_layout = VK_NULL_HANDLE;

    wr.uniform_descriptor_set_layout = VK_NULL_HANDLE;
    wr.texture_descriptor_set_layout = VK_NULL_HANDLE;

    wr.font_image = VK_NULL_HANDLE;
    wr.font_alloc = VK_NULL_HANDLE;
    wr.font_image_view = VK_NULL_HANDLE;
    wr.font_descriptor_set = VK_NULL_HANDLE;

    wr.texture_descriptor_sets = NULL;
    wr.texture_descriptor_sets_len = 0;
    wr.texture_descriptor_sets_capacity = 0;

    wr.vertex_gpu_buffer = VK_NULL_HANDLE;
    wr.vertex_gpu_alloc = VK_NULL_HANDLE;

    wr.index_gpu_buffer = VK_NULL_HANDLE;
    wr.index_gpu_alloc = VK_NULL_HANDLE;

    for (uint32_t i = 0; i < VK_FRAMES; ++i) {
        memset(
            &wr.frame[i],
            0,
            sizeof(wr.frame[i])
        );
    }
}

static void
nk_vk_destroy_descriptor_set_layouts(void)
{
    /*
     * Destroy layouts only after all descriptor sets, pipelines, and
     * pipeline layouts that use them have been destroyed or are no
     * longer in use.
     */
    if (wr.texture_descriptor_set_layout != VK_NULL_HANDLE) {
        vkDestroyDescriptorSetLayout(
            vk.dev,
            wr.texture_descriptor_set_layout,
            NULL
        );

        wr.texture_descriptor_set_layout = VK_NULL_HANDLE;
    }

    if (wr.uniform_descriptor_set_layout != VK_NULL_HANDLE) {
        vkDestroyDescriptorSetLayout(
            vk.dev,
            wr.uniform_descriptor_set_layout,
            NULL
        );

        wr.uniform_descriptor_set_layout = VK_NULL_HANDLE;
    }
}


static void
nk_vk_destroy_pipeline_layout(
    WidgetRenderer *renderer,
    VkEngine        *engine)
{
    if (renderer == NULL || engine == NULL)
        return;

    if (renderer->pipeline_layout != VK_NULL_HANDLE) {
        vkDestroyPipelineLayout(
            engine->dev,
            renderer->pipeline_layout,
            NULL);

        renderer->pipeline_layout = VK_NULL_HANDLE;
    }
}

static void
nk_vk_destroy_pipeline(void)
{
    if (wr.pipeline != VK_NULL_HANDLE) {
        vkDestroyPipeline(
            vk.dev,
            wr.pipeline,
            NULL
        );

        wr.pipeline = VK_NULL_HANDLE;
    }
}

static void
nk_vk_destroy_frame_resources(void)
{
    if (vk.dev == VK_NULL_HANDLE)
        return;

    for (uint32_t i = 0; i < VK_FRAMES; ++i)
    {
        WidgetFrameData *frame = &wr.frame[i];

        /*
         * Descriptor sets normally do not need to be freed individually;
         * destroying vk.descriptor_pool releases them all. Individual
         * freeing requires VK_DESCRIPTOR_POOL_CREATE_FREE_DESCRIPTOR_SET_BIT.
         */
        if (frame->uniform_descriptor_set != VK_NULL_HANDLE &&
            vk.descriptor_pool != VK_NULL_HANDLE)
        {
            VkResult result = vkFreeDescriptorSets(
                vk.dev,
                vk.descriptor_pool,
                1,
                &frame->uniform_descriptor_set);

            if (result != VK_SUCCESS)
            {
                LOG_ERROR_ARGS(
                    ERR_LEVEL_ERROR,
                    "failed to free frame descriptor set: %s",
                    vkstrerror(result));
            }

            frame->uniform_descriptor_set = VK_NULL_HANDLE;
        }

        /*
         * Unmap device memory before freeing it.
         */
        if (frame->mapped_uniform != NULL &&
            frame->uniform_memory != VK_NULL_HANDLE)
        {
            vkUnmapMemory(
                vk.dev,
                frame->uniform_memory);

            frame->mapped_uniform = NULL;
        }

        if (frame->mapped_vertex != NULL &&
            frame->vertex_memory != VK_NULL_HANDLE)
        {
            vkUnmapMemory(
                vk.dev,
                frame->vertex_memory);

            frame->mapped_vertex = NULL;
        }

        if (frame->mapped_index != NULL &&
            frame->index_memory != VK_NULL_HANDLE)
        {
            vkUnmapMemory(
                vk.dev,
                frame->index_memory);

            frame->mapped_index = NULL;
        }

        /*
         * Destroy buffers before freeing their VkDeviceMemory.
         */
        if (frame->uniform_buffer != VK_NULL_HANDLE)
        {
            vkDestroyBuffer(
                vk.dev,
                frame->uniform_buffer,
                NULL);

            frame->uniform_buffer = VK_NULL_HANDLE;
        }

        if (frame->uniform_memory != VK_NULL_HANDLE)
        {
            vkFreeMemory(
                vk.dev,
                frame->uniform_memory,
                NULL);

            frame->uniform_memory = VK_NULL_HANDLE;
        }

        if (frame->vertex_buffer != VK_NULL_HANDLE)
        {
            vkDestroyBuffer(
                vk.dev,
                frame->vertex_buffer,
                NULL);

            frame->vertex_buffer = VK_NULL_HANDLE;
        }

        if (frame->vertex_memory != VK_NULL_HANDLE)
        {
            vkFreeMemory(
                vk.dev,
                frame->vertex_memory,
                NULL);

            frame->vertex_memory = VK_NULL_HANDLE;
        }

        if (frame->index_buffer != VK_NULL_HANDLE)
        {
            vkDestroyBuffer(
                vk.dev,
                frame->index_buffer,
                NULL);

            frame->index_buffer = VK_NULL_HANDLE;
        }

        if (frame->index_memory != VK_NULL_HANDLE)
        {
            vkFreeMemory(
                vk.dev,
                frame->index_memory,
                NULL);

            frame->index_memory = VK_NULL_HANDLE;
        }

        frame->mapped_uniform = NULL;
        frame->mapped_vertex = NULL;
        frame->mapped_index = NULL;

        frame->max_vertex_buffer = 0;
        frame->max_index_buffer = 0;
        frame->uniform_buffer_size = 0;
        frame->index_count = 0;
    }
}



static void
nk_vk_destroy(WidgetRenderer *renderer,
              VkEngine       *engine)
{
    if (renderer == NULL || engine == NULL)
        return;

    /*
     * The GPU must no longer be using these resources.
     */
    vkDeviceWaitIdle(engine->dev);

    nk_vk_destroy_font_resources(renderer, engine);

    nk_vk_destroy_frame_resources(renderer, engine);
    nk_vk_destroy_pipeline(renderer, engine);
    nk_vk_destroy_pipeline_layout(renderer, engine);
    nk_vk_destroy_descriptor_set_layouts(renderer, engine);

    nk_vk_reset_renderer(renderer);
}


static void
widget_renderer_destroy_callback( Handle handle, void *)
{
    WidgetRenderer *renderer;

    renderer = handle_deref(
        &alloc,
        handle);

    if (renderer == NULL)
        return;

    if (renderer->window != NULL)
        nk_glfw3_shutdown(renderer);

    if (renderer->nk_initialized)
    {
        nk_free(&renderer->ctx);
        renderer->nk_initialized = false;
    }

    nk_buffer_free(&renderer->cmds);

    /*
     * Destroy Vulkan resources here.
     *
     * This should include:
     *
     *   - frame buffers
     *   - font image/view/allocation
     *   - pipeline
     *   - pipeline layout
     *   - descriptor-set layouts
     */
    nk_vk_destroy(
        renderer,
        &vk);

    handle_free(
        &alloc,
        &handle);
}


static void
widget_renderer_destroy(void)
{
    if (vk.dev != VK_NULL_HANDLE)
        vkDeviceWaitIdle(vk.dev);

    /*
     * Per-frame uniform, vertex, and index buffers.
     */
    for (uint32_t i = 0; i < VK_FRAMES; ++i)
    {
        WidgetFrameData *frame = &wr.frame[i];

        if (frame->mapped_uniform != NULL) {
            vkUnmapMemory(
                vk.dev,
                frame->uniform_memory
            );

            frame->mapped_uniform = NULL;
        }

        if (frame->uniform_buffer != VK_NULL_HANDLE) {
            vkDestroyBuffer(
                vk.dev,
                frame->uniform_buffer,
                NULL
            );

            frame->uniform_buffer = VK_NULL_HANDLE;
        }

        if (frame->uniform_memory != VK_NULL_HANDLE) {
            vkFreeMemory(
                vk.dev,
                frame->uniform_memory,
                NULL
            );

            frame->uniform_memory = VK_NULL_HANDLE;
        }

        if (frame->mapped_vertex != NULL) {
            vkUnmapMemory(
                vk.dev,
                frame->vertex_memory
            );

            frame->mapped_vertex = NULL;
        }

        if (frame->vertex_buffer != VK_NULL_HANDLE) {
            vkDestroyBuffer(
                vk.dev,
                frame->vertex_buffer,
                NULL
            );

            frame->vertex_buffer = VK_NULL_HANDLE;
        }

        if (frame->vertex_memory != VK_NULL_HANDLE) {
            vkFreeMemory(
                vk.dev,
                frame->vertex_memory,
                NULL
            );

            frame->vertex_memory = VK_NULL_HANDLE;
        }

        if (frame->mapped_index != NULL) {
            vkUnmapMemory(
                vk.dev,
                frame->index_memory
            );

            frame->mapped_index = NULL;
        }

        if (frame->index_buffer != VK_NULL_HANDLE) {
            vkDestroyBuffer(
                vk.dev,
                frame->index_buffer,
                NULL
            );

            frame->index_buffer = VK_NULL_HANDLE;
        }

        if (frame->index_memory != VK_NULL_HANDLE) {
            vkFreeMemory(
                vk.dev,
                frame->index_memory,
                NULL
            );

            frame->index_memory = VK_NULL_HANDLE;
        }

        frame->uniform_descriptor_set = VK_NULL_HANDLE;
        frame->max_vertex_buffer = 0;
        frame->max_index_buffer = 0;
        frame->index_count = 0;
    }

    /*
     * The font image view must be destroyed before the font image.
     */
    if (vk.dev != VK_NULL_HANDLE &&
        wr.font_image_view != VK_NULL_HANDLE)
    {
        vkDestroyImageView(
            vk.dev,
            wr.font_image_view,
            NULL
        );

        wr.font_image_view = VK_NULL_HANDLE;
    }

    if (vk.dev != VK_NULL_HANDLE &&
        wr.font_image != VK_NULL_HANDLE)
    {
        vkDestroyImage(
            vk.dev,
            wr.font_image,
            NULL
        );

        wr.font_image = VK_NULL_HANDLE;
    }

    if (vk.dev != VK_NULL_HANDLE &&
        wr.font_memory != VK_NULL_HANDLE)
    {
        vkFreeMemory(
            vk.dev,
            wr.font_memory,
            NULL
        );

        wr.font_memory = VK_NULL_HANDLE;
    }

    wr.font_descriptor_set = VK_NULL_HANDLE;
    wr.font_tex = nk_handle_ptr(NULL);

    /*
     * Additional geometry buffers.
     */
    if (vk.dev != VK_NULL_HANDLE &&
        wr.vertex_gpu_buffer != VK_NULL_HANDLE)
    {
        vkDestroyBuffer(
            vk.dev,
            wr.vertex_gpu_buffer,
            NULL
        );

        wr.vertex_gpu_buffer = VK_NULL_HANDLE;
    }

    if (vk.dev != VK_NULL_HANDLE &&
        wr.vertex_gpu_memory != VK_NULL_HANDLE)
    {
        vkFreeMemory(
            vk.dev,
            wr.vertex_gpu_memory,
            NULL
        );

        wr.vertex_gpu_memory = VK_NULL_HANDLE;
    }

    if (vk.dev != VK_NULL_HANDLE &&
        wr.index_gpu_buffer != VK_NULL_HANDLE)
    {
        vkDestroyBuffer(
            vk.dev,
            wr.index_gpu_buffer,
            NULL
        );

        wr.index_gpu_buffer = VK_NULL_HANDLE;
    }

    if (vk.dev != VK_NULL_HANDLE &&
        wr.index_gpu_memory != VK_NULL_HANDLE)
    {
        vkFreeMemory(
            vk.dev,
            wr.index_gpu_memory,
            NULL
        );

        wr.index_gpu_memory = VK_NULL_HANDLE;
    }

    /*
     * Nuklear font and command resources.
     */
    nk_font_atlas_clear(&wr.atlas);
    nk_buffer_free(&wr.cmds);
    nk_buffer_free(&wr.vertex_nk_buffer);
    nk_buffer_free(&wr.index_nk_buffer);

    /*
     * CPU-side quad storage.
     */
    free(wr.quad_vertices);
    wr.quad_vertices = NULL;
    wr.quad_vertex_capacity = 0;
    wr.quad_count = 0;

    /*
     * Registered texture descriptor-set bookkeeping.
     */
    free(wr.texture_descriptor_sets);
    wr.texture_descriptor_sets = NULL;
    wr.texture_descriptor_sets_len = 0;
    wr.texture_descriptor_sets_capacity = 0;

    /*
     * Descriptor-set layouts.
     */
    if (vk.dev != VK_NULL_HANDLE &&
        wr.uniform_descriptor_set_layout != VK_NULL_HANDLE)
    {
        vkDestroyDescriptorSetLayout(
            vk.dev,
            wr.uniform_descriptor_set_layout,
            NULL
        );

        wr.uniform_descriptor_set_layout = VK_NULL_HANDLE;
    }

    if (vk.dev != VK_NULL_HANDLE &&
        wr.texture_descriptor_set_layout != VK_NULL_HANDLE)
    {
        vkDestroyDescriptorSetLayout(
            vk.dev,
            wr.texture_descriptor_set_layout,
            NULL
        );

        wr.texture_descriptor_set_layout = VK_NULL_HANDLE;
    }

    /*
     * Pipeline resources.
     */
    if (vk.dev != VK_NULL_HANDLE &&
        wr.pipeline != VK_NULL_HANDLE)
    {
        vkDestroyPipeline(
            vk.dev,
            wr.pipeline,
            NULL
        );

        wr.pipeline = VK_NULL_HANDLE;
    }

    if (vk.dev != VK_NULL_HANDLE &&
        wr.pipeline_layout != VK_NULL_HANDLE)
    {
        vkDestroyPipelineLayout(
            vk.dev,
            wr.pipeline_layout,
            NULL
        );

        wr.pipeline_layout = VK_NULL_HANDLE;
    }

    /*
     * Nuklear context.
     */
    if (wr.nk_initialized) {
        nk_free(&wr.ctx);
        wr.nk_initialized = false;
    }

    wr.window = NULL;
    wr.callbacks_installed = false;
}



static uint16_t *create_index_buffer(size_t max_glyphs, size_t *size)
{
    static const uint16_t quad_index[] =
    {
        0, 1, 2,
        1, 2, 3
    };

    *size = max_glyphs * sizeof(quad_index);
    uint16_t *buffer = malloc(*size);

    for (ufast32_t i = 0; i < max_glyphs; i++)
    {
        fast32_t offset = LENGTH(quad_index) * i;
        for (ufast32_t j = 0; j < LENGTH(quad_index); j++)
            buffer[offset+j] = 4*i + quad_index[j];
    }

    return buffer;
}
static void
widget_geometry_upload(void)
{
    WidgetFrameData *frame =
        &wr.frame[vk.current_frame];

    const size_t vertex_bytes =
        nk_buffer_total(&wr.vertex_nk_buffer);

    const size_t index_bytes =
        nk_buffer_total(&wr.index_nk_buffer);

    /*
     * No converted geometry to upload.
     */
    if (vertex_bytes == 0 || index_bytes == 0)
        return;

    if (frame->mapped_vertex == NULL ||
        frame->mapped_index == NULL)
    {
        return;
    }

    if (vertex_bytes > frame->max_vertex_buffer ||
        index_bytes > frame->max_index_buffer)
    {
        return;
    }

    const void *vertex_data =
        nk_buffer_memory_const(&wr.vertex_nk_buffer);

    const void *index_data =
        nk_buffer_memory_const(&wr.index_nk_buffer);

    if (vertex_data == NULL || index_data == NULL)
        return;

    memcpy(
        frame->mapped_vertex,
        vertex_data,
        vertex_bytes
    );

    memcpy(
        frame->mapped_index,
        index_data,
        index_bytes
    );

    /*
     * Flush non-coherent host-visible memory.
     *
     * If the selected memory type is HOST_COHERENT, these calls are
     * not required, but they are valid and harmless.
     */
    VkMappedMemoryRange vertex_range = {
        .sType = VK_STRUCTURE_TYPE_MAPPED_MEMORY_RANGE,
        .pNext = NULL,
        .memory = frame->vertex_memory,
        .offset = 0,
        .size = vertex_bytes
    };

    VkMappedMemoryRange index_range = {
        .sType = VK_STRUCTURE_TYPE_MAPPED_MEMORY_RANGE,
        .pNext = NULL,
        .memory = frame->index_memory,
        .offset = 0,
        .size = index_bytes
    };

    VkResult result = vkFlushMappedMemoryRanges(
        vk.dev,
        1,
        &vertex_range
    );

    if (result != VK_SUCCESS)
        return;

    result = vkFlushMappedMemoryRanges(
        vk.dev,
        1,
        &index_range
    );

    (void)result;
}


void
widget_renderer_draw()
{
 

    const uint32_t frame_index = vk.current_frame;

    struct VkFrame *vk_frame = &vk.frames[frame_index];

    WidgetFrameData *ui_frame = &wr.frame[frame_index];
    // Commmand Buffers belond to VkEngine
    VkCommandBuffer cmd = vk_frame->cmd_buf;

    if (cmd == VK_NULL_HANDLE ||
        ui_frame->vertex_buffer == VK_NULL_HANDLE ||
        ui_frame->index_buffer == VK_NULL_HANDLE ||
        ui_frame->index_count == 0)
    {
        return;
    }

    vkCmdBindPipeline(
        cmd,
        VK_PIPELINE_BIND_POINT_GRAPHICS,
        wr.pipeline);

    VkDeviceSize vertex_offset = 0;

    vkCmdBindVertexBuffers(
        cmd,
        0,
        1,
        &ui_frame->vertex_buffer,
        &vertex_offset);

    vkCmdBindIndexBuffer(
        cmd,
        ui_frame->index_buffer,
        0,
        sizeof(nk_draw_index) == sizeof(uint16_t)
            ? VK_INDEX_TYPE_UINT16
            : VK_INDEX_TYPE_UINT32);

    const struct nk_draw_command *draw_cmd;
    uint32_t index_offset = 0;

    nk_draw_foreach(
        draw_cmd,
        &wr.ctx,
        &wr.cmds)
    {
        if (draw_cmd == NULL || draw_cmd->elem_count == 0)
            continue;

        if (draw_cmd->texture.ptr == NULL)
            continue;

        VkDescriptorSet descriptor_set = *(VkDescriptorSet *)draw_cmd->texture.ptr;

        vkCmdBindDescriptorSets(
            cmd,
            VK_PIPELINE_BIND_POINT_GRAPHICS,
            wr.pipeline_layout,
            0,
            1,
            &descriptor_set,
            0,
            NULL);

        vkCmdDrawIndexed(
            cmd,
            draw_cmd->elem_count,
            1,
            index_offset,
            0,
            0);

        index_offset += draw_cmd->elem_count;
    }
}


NK_API void wr_glfw3_font_stash_begin(struct nk_font_atlas **atlas)
{
    nk_font_atlas_init_default(&wr.atlas);
    nk_font_atlas_begin(&wr.atlas);
    *atlas = &wr.atlas;
}

NK_API void wr_glfw3_font_stash_end(VkQueue graphics_queue)
{
    struct WidgetRenderer *renderer = &wr;

    const void *image;
    int w, h;
    image = nk_font_atlas_bake(&wr.atlas, &w, &h, NK_FONT_ATLAS_RGBA32);
    nk_glfw3_device_upload_atlas(vk.graphics_queue, image, w, h);
    nk_font_atlas_end(&wr.atlas, nk_handle_ptr(renderer->font_image_view), &renderer->tex_null);
    if (renderer->atlas.default_font)
    {
        nk_style_set_font(&renderer->ctx, &renderer->atlas.default_font->handle);
    }
}


void
WidgetInstallFonts(void)
{
    // aim to the 
    struct nk_font_atlas *atlas = &wr.atlas;

    wr_glfw3_font_stash_begin(&atlas);

    /*
     * Add fonts here if needed:
     *
     * struct nk_font *droid =
     *     nk_font_atlas_add_from_file(
     *         atlas,
     *         "../../../extra_font/DroidSans.ttf",
     *         14,
     *         0);
     *
     * struct nk_font *roboto =
     *     nk_font_atlas_add_from_file(
     *         atlas,
     *         "../../../extra_font/Roboto-Regular.ttf",
     *         14,
     *         0);
     *
     * struct nk_font *future =
     *     nk_font_atlas_add_from_file(
     *         atlas,
     *         "../../../extra_font/kenvector_future_thin.ttf",
     *         13,
     *         0);
     *
     * struct nk_font *clean =
     *     nk_font_atlas_add_from_file(
     *         atlas,
     *         "../../../extra_font/ProggyClean.ttf",
     *         12,
     *         0);
     *
     * struct nk_font *tiny =
     *     nk_font_atlas_add_from_file(
     *         atlas,
     *         "../../../extra_font/ProggyTiny.ttf",
     *         10,
     *         0);
     *
     * struct nk_font *cousine =
     *     nk_font_atlas_add_from_file(
     *         atlas,
     *         "../../../extra_font/Cousine-Regular.ttf",
     *         13,
     *         0);
     */
    /// stored into VkEngine's data
    wr_glfw3_font_stash_end(vk.graphics_queue);

    /*
     * Optional:
     *
     * nk_style_load_all_cursors(ctx, atlas->cursors);
     * nk_style_set_font(ctx, &droid->handle);
     */
}


/**

*/

bool GfxFrameUploadBuffer(
    WidgetFrameData *frame,
    VkBuffer *buffer,
    VmaAllocation *allocation,
    const void *data,
    size_t size,
    VkBufferUsageFlags usage)
{
    if (frame == NULL ||
        buffer == NULL ||
        allocation == NULL ||
        data == NULL ||
        size == 0)
    {
        return false;
    }


    *buffer = VK_NULL_HANDLE;
    *allocation = VK_NULL_HANDLE;

    return vk_upload_buffer(
        buffer,
        allocation,
        data,
        size,
        usage
    );
}

bool nk_vk_load_shader_module(
    VkDevice device,
    enum Resource resource,
    VkShaderModule *shader_module)
{
    if (!device || !shader_module)
        return false;

    size_t spv_size = 0;

    void *spv_data = res_file(resource, &spv_size);
    if (!spv_data)
        return false;

    /*
     * SPIR-V must be supplied as an array of 32-bit words.
     */
    if (spv_size == 0 || (spv_size % sizeof(uint32_t)) != 0)
    {
        free(spv_data);
        return false;
    }

    const VkShaderModuleCreateInfo create_info = {
        .sType    = VK_STRUCTURE_TYPE_SHADER_MODULE_CREATE_INFO,
        .pNext    = NULL,
        .flags    = 0,
        .codeSize = spv_size,
        .pCode    = (const uint32_t *)spv_data
    };

    VkResult result = vkCreateShaderModule(
        device,
        &create_info,
        NULL,
        shader_module);

    free(spv_data);

    if (result != VK_SUCCESS)
    {
        *shader_module = VK_NULL_HANDLE;
        return false;
    }

    return true;
}




/**
 * 
 * The relationship is:
text

renderer->ctx
       +
renderer->cmds
       +
config
       ↓
renderer->vertex_buffer
renderer->index_buffer

After conversion:

    renderer->vertex_gpu_buffer contains serialized NkVertex data.
    renderer->index_gpu_buffer contains serialized nk_draw_index data.
    
input polling
    ↓
frame_begin()
    ↓
WidgetRendererBuildWidgets()
    ↓
WidgetRendererUpdate()
    ↓
gfx_frame_mainpass_begin()
    ↓
world rendering
    ↓
widget_renderer_draw()
    ↓
gfx_frame_mainpass_end()
    ↓
frame_end()    

 * */
bool WidgetRendererUpdate(struct Frame *frame)
{
    //struct Frame *frame passes global data updated per frame before updating geometry and renderering steps go on
    // you can get current pose in coodrinates
    
    struct nk_convert_config config;
    nk_flags convert_result;
    // WidgetFrame data is locked to VkEngine frame 
    WidgetFrameData *ui_frame = &wr.frame[vk.current_frame];

    if (!ui_frame)
        return false;

    /*
     * These values are used by WidgetRendererRecord() when calculating
     * viewport and scissor rectangles.
     */
    ui_frame->width  = vk.swapchain_extent.width;
    ui_frame->height = vk.swapchain_extent.height;

    wr.fb_scale.x =
        wr.display_width > 0.0f
            ? (float)ui_frame->width / wr.display_width
            : 1.0f;

    wr.fb_scale.y =
        wr.display_height > 0.0f
            ? (float)ui_frame->height / wr.display_height
            : 1.0f;

    /*
     * These are CPU-side Nuklear conversion buffers.
     *
     * They must be struct nk_buffer objects, not VkBuffer handles.
     * The resulting data is uploaded to the Vulkan buffers below.
     */
    nk_buffer_clear(&wr.vertex_nk_buffer);
    nk_buffer_clear(&wr.index_nk_buffer);

    memset(&config, 0, sizeof(config));

    config.vertex_layout =
        (struct nk_draw_vertex_layout_element[]) {
            {
                NK_VERTEX_POSITION,
                NK_FORMAT_FLOAT,
                NK_OFFSETOF(struct NkVertex, pos)
            },
            {
                NK_VERTEX_TEXCOORD,
                NK_FORMAT_FLOAT,
                NK_OFFSETOF(struct NkVertex, uv)
            },
            {
                NK_VERTEX_COLOR,
                NK_FORMAT_R8G8B8A8,
                NK_OFFSETOF(struct NkVertex, color)
            },
            {
                NK_VERTEX_ATTRIBUTE_COUNT,
                NK_FORMAT_COUNT,
                0
            }
        };

    config.vertex_size      = sizeof(struct NkVertex);
    config.vertex_alignment = NK_ALIGNOF(struct NkVertex);
    config.tex_null             = wr.tex_null;

    config.circle_segment_count = 22;
    config.curve_segment_count  = 22;
    config.arc_segment_count    = 22;

    config.global_alpha = 1.0f;
    config.shape_AA     = NK_ANTI_ALIASING_ON;
    config.line_AA      = NK_ANTI_ALIASING_ON;

    /*
     * Convert the current Nuklear command list into CPU-side vertex
     * and index data.
     *
     * Use the argument order required by the Nuklear header in use.
     */
    convert_result = nk_convert(
        &wr.ctx,
        &wr.cmds,
        &wr.vertex_nk_buffer,
        &wr.index_nk_buffer,
        &config);

    if (convert_result != NK_CONVERT_SUCCESS)
    {
        fprintf(
            stderr,
            "nk_convert failed: %u\n",
            (unsigned)convert_result);

        return false;
    }

    const size_t vertex_size = nk_buffer_total(&wr.vertex_nk_buffer);

    const size_t index_size = nk_buffer_total(&wr.index_nk_buffer);

    /*
     * An empty UI frame is valid.
     */
    if (vertex_size == 0 || index_size == 0)
    {
        ui_frame->index_count        = 0;
        ui_frame->max_vertex_buffer  = 0;
        ui_frame->max_index_buffer = 0;

        return true;
    }

    /*
     * Read from the CPU-side Nuklear buffers.
     */
    const void *vertices = nk_buffer_memory_const(&wr.vertex_nk_buffer);

    const void *indices =  nk_buffer_memory_const(&wr.index_nk_buffer);

    /*
     * Upload the converted data into the Vulkan buffers belonging to
     * this frame-in-flight slot.
     *
     * The corresponding frame fence has already been waited on by
     * gfx_loop(), so these buffers are safe to reuse.
     */
    if (!GfxFrameUploadBuffer(
            ui_frame,
            &ui_frame->vertex_buffer,
            &ui_frame->vertex_alloc,
            vertices,
            vertex_size,
            VK_BUFFER_USAGE_VERTEX_BUFFER_BIT))
    {
        return false;
    }

    if (!GfxFrameUploadBuffer(
            ui_frame,
            &ui_frame->index_buffer,
            &ui_frame->index_alloc,
            indices,
            index_size,
            VK_BUFFER_USAGE_INDEX_BUFFER_BIT))
    {
        return false;
    }

    /*
     * Cache sizes and counts for WidgetRendererRecord().
     */
    ui_frame->max_vertex_buffer  = (uint32_t)vertex_size;
    ui_frame->max_index_buffer = (uint32_t)index_size;
    ui_frame->index_count = (uint32_t)(index_size / sizeof(nk_draw_index));

    return true;
}

static bool
nk_vk_create_pipeline(
    WidgetRenderer *renderer,
    VkEngine *engine)
{
    if (renderer == NULL || engine == NULL)
        return false;

    if (renderer->pipeline_layout == VK_NULL_HANDLE)
        return false;

    VkShaderModule vert_shader = VK_NULL_HANDLE;
    VkShaderModule frag_shader = VK_NULL_HANDLE;

    /*
     * Replace these paths or load the SPIR-V data from memory.
     */
    if (!nk_vk_load_shader_module(
	    engine->dev,
	    RES_NUKLEAR_VERT_GUI,
	    &vert_shader))
    {
	return false;
    }

    if (!nk_vk_load_shader_module(
	    engine->dev,
	    RES_NUKLEAR_FRAG_GUI,
	    &frag_shader))
    {
	vkDestroyShaderModule(
	    engine->dev,
	    vert_shader,
	    NULL);

	return false;
    }


    VkPipelineShaderStageCreateInfo shader_stages[2] = {
        {
            .sType  = VK_STRUCTURE_TYPE_PIPELINE_SHADER_STAGE_CREATE_INFO,
            .stage  = VK_SHADER_STAGE_VERTEX_BIT,
            .module = vert_shader,
            .pName  = "main"
        },
        {
            .sType  = VK_STRUCTURE_TYPE_PIPELINE_SHADER_STAGE_CREATE_INFO,
            .stage  = VK_SHADER_STAGE_FRAGMENT_BIT,
            .module = frag_shader,
            .pName  = "main"
        }
    };

    VkVertexInputBindingDescription binding = {
        .binding   = 0,
        .stride    = sizeof(struct NkVertex),
        .inputRate = VK_VERTEX_INPUT_RATE_VERTEX
    };

    VkVertexInputAttributeDescription attributes[3] = {
        {
            .location = 0,
            .binding  = 0,
            .format   = VK_FORMAT_R32G32_SFLOAT,
            .offset   = offsetof(struct NkVertex, pos)
        },
        {
            .location = 1,
            .binding  = 0,
            .format   = VK_FORMAT_R32G32_SFLOAT,
            .offset   = offsetof(struct NkVertex, uv)
        },
        {
            .location = 2,
            .binding  = 0,
            .format   = VK_FORMAT_R8G8B8A8_UNORM,
            .offset   = offsetof(struct NkVertex, color)
        }
    };

    VkPipelineVertexInputStateCreateInfo vertex_input = {
        .sType                           =
            VK_STRUCTURE_TYPE_PIPELINE_VERTEX_INPUT_STATE_CREATE_INFO,
        .vertexBindingDescriptionCount   = 1,
        .pVertexBindingDescriptions      = &binding,
        .vertexAttributeDescriptionCount = 3,
        .pVertexAttributeDescriptions    = attributes
    };

    VkPipelineInputAssemblyStateCreateInfo input_assembly = {
        .sType                  =
            VK_STRUCTURE_TYPE_PIPELINE_INPUT_ASSEMBLY_STATE_CREATE_INFO,
        .topology               = VK_PRIMITIVE_TOPOLOGY_TRIANGLE_LIST,
        .primitiveRestartEnable = VK_FALSE
    };

    VkPipelineViewportStateCreateInfo viewport_state = {
        .sType         = VK_STRUCTURE_TYPE_PIPELINE_VIEWPORT_STATE_CREATE_INFO,
        .viewportCount = 1,
        .scissorCount  = 1
    };

    VkPipelineRasterizationStateCreateInfo rasterization = {
        .sType                   =
            VK_STRUCTURE_TYPE_PIPELINE_RASTERIZATION_STATE_CREATE_INFO,
        .depthClampEnable       = VK_FALSE,
        .rasterizerDiscardEnable = VK_FALSE,
        .polygonMode             = VK_POLYGON_MODE_FILL,
        .lineWidth              = 1.0f,
        .cullMode               = VK_CULL_MODE_NONE,
        .frontFace              = VK_FRONT_FACE_COUNTER_CLOCKWISE
    };

    VkPipelineMultisampleStateCreateInfo multisample = {
        .sType                =
            VK_STRUCTURE_TYPE_PIPELINE_MULTISAMPLE_STATE_CREATE_INFO,
        .rasterizationSamples = VK_SAMPLE_COUNT_1_BIT
    };

    VkPipelineColorBlendAttachmentState blend_attachment = {
        .blendEnable         = VK_TRUE,
        .srcColorBlendFactor = VK_BLEND_FACTOR_SRC_ALPHA,
        .dstColorBlendFactor = VK_BLEND_FACTOR_ONE_MINUS_SRC_ALPHA,
        .colorBlendOp        = VK_BLEND_OP_ADD,
        .srcAlphaBlendFactor = VK_BLEND_FACTOR_ONE,
        .dstAlphaBlendFactor = VK_BLEND_FACTOR_ONE_MINUS_SRC_ALPHA,
        .alphaBlendOp        = VK_BLEND_OP_ADD,
        .colorWriteMask      =
            VK_COLOR_COMPONENT_R_BIT |
            VK_COLOR_COMPONENT_G_BIT |
            VK_COLOR_COMPONENT_B_BIT |
            VK_COLOR_COMPONENT_A_BIT
    };

    VkPipelineColorBlendStateCreateInfo color_blend = {
        .sType           =
            VK_STRUCTURE_TYPE_PIPELINE_COLOR_BLEND_STATE_CREATE_INFO,
        .logicOpEnable   = VK_FALSE,
        .attachmentCount = 1,
        .pAttachments    = &blend_attachment
    };

    VkDynamicState dynamic_states[] = {
        VK_DYNAMIC_STATE_VIEWPORT,
        VK_DYNAMIC_STATE_SCISSOR
    };

    VkPipelineDynamicStateCreateInfo dynamic_state = {
        .sType             =
            VK_STRUCTURE_TYPE_PIPELINE_DYNAMIC_STATE_CREATE_INFO,
        .dynamicStateCount = 2,
        .pDynamicStates    = dynamic_states
    };

    /*
     * Nuklear normally renders without depth testing.
     */
    VkPipelineDepthStencilStateCreateInfo depth_stencil = {
        .sType            =
            VK_STRUCTURE_TYPE_PIPELINE_DEPTH_STENCIL_STATE_CREATE_INFO,
        .depthTestEnable  = VK_FALSE,
        .depthWriteEnable = VK_FALSE,
        .depthCompareOp   = VK_COMPARE_OP_ALWAYS
    };

    VkGraphicsPipelineCreateInfo pipeline_info = {
        .sType               =
            VK_STRUCTURE_TYPE_GRAPHICS_PIPELINE_CREATE_INFO,
        .stageCount          = 2,
        .pStages             = shader_stages,
        .pVertexInputState   = &vertex_input,
        .pInputAssemblyState = &input_assembly,
        .pViewportState      = &viewport_state,
        .pRasterizationState = &rasterization,
        .pMultisampleState   = &multisample,
        .pDepthStencilState  = &depth_stencil,
        .pColorBlendState    = &color_blend,
        .pDynamicState       = &dynamic_state,
        .layout              = renderer->pipeline_layout,
        .renderPass          = engine->renderpass,
        .subpass             = 0
    };

    VkResult result = vkCreateGraphicsPipelines(
        engine->dev,
        engine->pipeline_cache,
        1,
        &pipeline_info,
        NULL,
        &renderer->pipeline);

    vkDestroyShaderModule(engine->dev, vert_shader, NULL);
    vkDestroyShaderModule(engine->dev, frag_shader, NULL);

    return result == VK_SUCCESS;
}



static bool
nk_vk_create_frame_resources(
    VkDeviceSize max_vertex_buffer,
    VkDeviceSize max_element_buffer)
{
    const VkMemoryPropertyFlags memory_properties =
        VK_MEMORY_PROPERTY_HOST_VISIBLE_BIT |
        VK_MEMORY_PROPERTY_HOST_COHERENT_BIT;

    if (vk.dev == VK_NULL_HANDLE ||
        vk.dev_physical == VK_NULL_HANDLE)
    {
        return false;
    }

    for (uint32_t i = 0; i < VK_FRAMES; ++i)
    {
        WidgetFrameData *frame = &wr.frame[i];

        frame->vertex_buffer = VK_NULL_HANDLE;
        frame->vertex_memory = VK_NULL_HANDLE;
        frame->mapped_vertex = NULL;

        frame->index_buffer = VK_NULL_HANDLE;
        frame->index_memory = VK_NULL_HANDLE;
        frame->mapped_index = NULL;

        frame->uniform_buffer = VK_NULL_HANDLE;
        frame->uniform_memory = VK_NULL_HANDLE;
        frame->mapped_uniform = NULL;

        /*
         * Vertex buffer.
         */
        if (new_Buffer_DeviceMemory(
                &frame->vertex_buffer,
                &frame->vertex_memory,
                max_vertex_buffer,
                vk.dev_physical,
                vk.dev,
                VK_BUFFER_USAGE_VERTEX_BUFFER_BIT,
                memory_properties) != ERR_OK)
        {
            goto fail;
        }

        frame->max_vertex_buffer = max_vertex_buffer;

        /*
         * Index buffer.
         */
        if (new_Buffer_DeviceMemory(
                &frame->index_buffer,
                &frame->index_memory,
                max_element_buffer,
                vk.dev_physical,
                vk.dev,
                VK_BUFFER_USAGE_INDEX_BUFFER_BIT,
                memory_properties) != ERR_OK)
        {
            goto fail;
        }

        frame->max_index_buffer = max_element_buffer;

        /*
         * Per-frame uniform buffer.
         */
        if (new_Buffer_DeviceMemory(
                &frame->uniform_buffer,
                &frame->uniform_memory,
                sizeof(struct Mat4f),
                vk.dev_physical,
                vk.dev,
                VK_BUFFER_USAGE_UNIFORM_BUFFER_BIT,
                memory_properties) != ERR_OK)
        {
            goto fail;
        }

        frame->uniform_buffer_size = sizeof(struct Mat4f);
    }

    /*
     * Map all per-frame buffers.
     */
    for (uint32_t i = 0; i < VK_FRAMES; ++i)
    {
        WidgetFrameData *frame = &wr.frame[i];

        if (vkMapMemory(
                vk.dev,
                frame->vertex_memory,
                0,
                frame->max_vertex_buffer,
                0,
                &frame->mapped_vertex) != VK_SUCCESS)
        {
            goto fail;
        }

        if (vkMapMemory(
                vk.dev,
                frame->index_memory,
                0,
                frame->max_index_buffer,
                0,
                &frame->mapped_index) != VK_SUCCESS)
        {
            goto fail;
        }

        if (vkMapMemory(
                vk.dev,
                frame->uniform_memory,
                0,
                frame->uniform_buffer_size,
                0,
                &frame->mapped_uniform) != VK_SUCCESS)
        {
            goto fail;
        }
    }

    return true;

fail:
    /*
     * Release every frame resource. Handles are checked so this also
     * handles failures during partial creation.
     */
    for (uint32_t i = 0; i < VK_FRAMES; ++i)
    {
        WidgetFrameData *frame = &wr.frame[i];

        if (frame->mapped_vertex != NULL)
        {
            vkUnmapMemory(vk.dev, frame->vertex_memory);
            frame->mapped_vertex = NULL;
        }

        if (frame->mapped_index != NULL)
        {
            vkUnmapMemory(vk.dev, frame->index_memory);
            frame->mapped_index = NULL;
        }

        if (frame->mapped_uniform != NULL)
        {
            vkUnmapMemory(vk.dev, frame->uniform_memory);
            frame->mapped_uniform = NULL;
        }

        if (frame->vertex_buffer != VK_NULL_HANDLE)
        {
            vkDestroyBuffer(vk.dev, frame->vertex_buffer, NULL);
            frame->vertex_buffer = VK_NULL_HANDLE;
        }

        if (frame->vertex_memory != VK_NULL_HANDLE)
        {
            vkFreeMemory(vk.dev, frame->vertex_memory, NULL);
            frame->vertex_memory = VK_NULL_HANDLE;
        }

        if (frame->index_buffer != VK_NULL_HANDLE)
        {
            vkDestroyBuffer(vk.dev, frame->index_buffer, NULL);
            frame->index_buffer = VK_NULL_HANDLE;
        }

        if (frame->index_memory != VK_NULL_HANDLE)
        {
            vkFreeMemory(vk.dev, frame->index_memory, NULL);
            frame->index_memory = VK_NULL_HANDLE;
        }

        if (frame->uniform_buffer != VK_NULL_HANDLE)
        {
            vkDestroyBuffer(vk.dev, frame->uniform_buffer, NULL);
            frame->uniform_buffer = VK_NULL_HANDLE;
        }

        if (frame->uniform_memory != VK_NULL_HANDLE)
        {
            vkFreeMemory(vk.dev, frame->uniform_memory, NULL);
            frame->uniform_memory = VK_NULL_HANDLE;
        }

        frame->max_vertex_buffer = 0;
        frame->max_index_buffer = 0;
        frame->uniform_buffer_size = 0;
    }

    return false;
}


        frame->max_vertex_buffer = (uint32_t)initial_vertex_size;

        /*
         * Index buffer.
         */
        err = new_Buffer_DeviceMemory(
            &frame->index_buffer,
            &frame->index_memory,
            initial_index_size,
            engine->physical_device,
            engine->dev,
            VK_BUFFER_USAGE_INDEX_BUFFER_BIT,
            memory_properties);

        if (err != ERR_OK)
            goto fail;

        result = vkMapMemory(
            engine->dev,
            frame->index_memory,
            0,
            initial_index_size,
            0,
            &frame->mapped_index);

        if (result != VK_SUCCESS)
            goto fail;

        frame->max_index_buffer = (uint32_t)initial_index_size;
        frame->index_count = 0;

        /*
         * Allocate the uniform descriptor set.
         */
        VkDescriptorSetAllocateInfo descriptor_allocate = {
            .sType = VK_STRUCTURE_TYPE_DESCRIPTOR_SET_ALLOCATE_INFO,
            .descriptorPool = engine->descriptor_pool,
            .descriptorSetCount = 1,
            .pSetLayouts = &renderer->uniform_descriptor_set_layout
        };

        result = vkAllocateDescriptorSets(
            engine->dev,
            &descriptor_allocate,
            &frame->uniform_descriptor_set);

        if (result != VK_SUCCESS)
            goto fail;

        VkDescriptorBufferInfo uniform_descriptor = {
            .buffer = frame->uniform_buffer,
            .offset = 0,
            .range = uniform_size
        };

        VkWriteDescriptorSet write = {
            .sType = VK_STRUCTURE_TYPE_WRITE_DESCRIPTOR_SET,
            .dstSet = frame->uniform_descriptor_set,
            .dstBinding = 0,
            .descriptorCount = 1,
            .descriptorType = VK_DESCRIPTOR_TYPE_UNIFORM_BUFFER,
            .pBufferInfo = &uniform_descriptor
        };

        vkUpdateDescriptorSets(
            engine->dev,
            1,
            &write,
            0,
            NULL);
    }

    return true;

fail:
    /*
     * The frame that failed may already contain partially created resources.
     * Destroy them before returning.
     */
    for (uint32_t j = 0; j <= i; ++j) {
        WidgetFrameData *frame = &renderer->frame[j];

        if (frame->mapped_uniform != NULL &&
            frame->uniform_memory != VK_NULL_HANDLE) {
            vkUnmapMemory(engine->dev, frame->uniform_memory);
            frame->mapped_uniform = NULL;
        }

        if (frame->mapped_vertex != NULL &&
            frame->vertex_memory != VK_NULL_HANDLE) {
            vkUnmapMemory(engine->dev, frame->vertex_memory);
            frame->mapped_vertex = NULL;
        }

        if (frame->mapped_index != NULL &&
            frame->index_memory != VK_NULL_HANDLE) {
            vkUnmapMemory(engine->dev, frame->index_memory);
            frame->mapped_index = NULL;
        }

        if (frame->uniform_buffer != VK_NULL_HANDLE)
            vkDestroyBuffer(engine->dev, frame->uniform_buffer, NULL);

        if (frame->vertex_buffer != VK_NULL_HANDLE)
            vkDestroyBuffer(engine->dev, frame->vertex_buffer, NULL);

        if (frame->index_buffer != VK_NULL_HANDLE)
            vkDestroyBuffer(engine->dev, frame->index_buffer, NULL);

        if (frame->uniform_memory != VK_NULL_HANDLE)
            vkFreeMemory(engine->dev, frame->uniform_memory, NULL);

        if (frame->vertex_memory != VK_NULL_HANDLE)
            vkFreeMemory(engine->dev, frame->vertex_memory, NULL);

        if (frame->index_memory != VK_NULL_HANDLE)
            vkFreeMemory(engine->dev, frame->index_memory, NULL);

        frame->uniform_buffer = VK_NULL_HANDLE;
        frame->uniform_memory = VK_NULL_HANDLE;
        frame->vertex_buffer = VK_NULL_HANDLE;
        frame->vertex_memory = VK_NULL_HANDLE;
        frame->index_buffer = VK_NULL_HANDLE;
        frame->index_memory = VK_NULL_HANDLE;
    }

    return false;
}

static void
nk_vk_update_font_descriptor(struct VkEngine *engine,
                             struct WidgetRenderer *renderer)
{
    VkDescriptorImageInfo image_info = {
        .sampler = engine->texture_sampler,
        .imageView = renderer->font_image_view,
        .imageLayout = VK_IMAGE_LAYOUT_SHADER_READ_ONLY_OPTIMAL
    };

    VkWriteDescriptorSet write = {
        .sType = VK_STRUCTURE_TYPE_WRITE_DESCRIPTOR_SET,
        .dstSet = renderer->font_descriptor_set,
        .dstBinding = 0,
        .dstArrayElement = 0,
        .descriptorCount = 1,
        .descriptorType = VK_DESCRIPTOR_TYPE_COMBINED_IMAGE_SAMPLER,
        .pImageInfo = &image_info
    };

    vkUpdateDescriptorSets(engine->dev, 1, &write, 0, NULL);
}


/*
 * Upload an RGBA8 image using the engine-owned VMA allocator and command pool.
 *
 * Resource ownership:
 *   - VkEngine owns the allocator, command pool, queue, and descriptor pool.
 *   - WidgetRenderer owns the returned image, allocation, and image view.
 */
static NkVkImage
nk_vk_upload_rgba8_image(struct VkEngine *engine,
                         const void *pixels,
                         uint32_t width,
                         uint32_t height)
{
    NkVkImage result_image = {
        VK_NULL_HANDLE,
        VK_NULL_HANDLE,
        VK_NULL_HANDLE
    };

    VkResult result;
    ErrVal err;

    VkImage image = VK_NULL_HANDLE;
    VkImageView image_view = VK_NULL_HANDLE;
    VkDeviceMemory image_memory = VK_NULL_HANDLE;

    VkBuffer staging_buffer = VK_NULL_HANDLE;
    VkDeviceMemory staging_memory = VK_NULL_HANDLE;

    VkFence fence = VK_NULL_HANDLE;
    VkCommandBuffer command_buffer = VK_NULL_HANDLE;

    const VkDeviceSize image_size =
        (VkDeviceSize)width * (VkDeviceSize)height * 4u;

    /*
     * Create the device-local destination image.
     */
    VkImageCreateInfo image_info = {0};
    image_info.sType = VK_STRUCTURE_TYPE_IMAGE_CREATE_INFO;
    image_info.imageType = VK_IMAGE_TYPE_2D;
    image_info.format = VK_FORMAT_R8G8B8A8_UNORM;
    image_info.extent.width = width;
    image_info.extent.height = height;
    image_info.extent.depth = 1;
    image_info.mipLevels = 1;
    image_info.arrayLayers = 1;
    image_info.samples = VK_SAMPLE_COUNT_1_BIT;
    image_info.tiling = VK_IMAGE_TILING_OPTIMAL;
    image_info.usage =
        VK_IMAGE_USAGE_TRANSFER_DST_BIT |
        VK_IMAGE_USAGE_SAMPLED_BIT;
    image_info.sharingMode = VK_SHARING_MODE_EXCLUSIVE;
    image_info.initialLayout = VK_IMAGE_LAYOUT_UNDEFINED;

    result = vkCreateImage(engine->dev,
                            &image_info,
                            NULL,
                            &image);
    NK_ASSERT(result == VK_SUCCESS);

    /*
     * Allocate memory for the image.
     */
    VkMemoryRequirements image_memory_requirements;
    vkGetImageMemoryRequirements(engine->dev,
                                 image,
                                 &image_memory_requirements);

    VkMemoryAllocateInfo image_allocate_info = {0};
    image_allocate_info.sType =
        VK_STRUCTURE_TYPE_MEMORY_ALLOCATE_INFO;
    image_allocate_info.allocationSize =
        image_memory_requirements.size;

    err = getMemoryTypeIndex(
        &image_allocate_info.memoryTypeIndex,
        image_memory_requirements.memoryTypeBits,
        VK_MEMORY_PROPERTY_DEVICE_LOCAL_BIT,
        engine->physical_device);

    NK_ASSERT(err == ERR_OK);

    result = vkAllocateMemory(engine->dev,
                              &image_allocate_info,
                              NULL,
                              &image_memory);
    NK_ASSERT(result == VK_SUCCESS);

    result = vkBindImageMemory(engine->dev,
                               image,
                               image_memory,
                               0);
    NK_ASSERT(result == VK_SUCCESS);

    /*
     * Create a temporary host-visible staging buffer.
     *
     * HOST_COHERENT is requested so that the memcpy is immediately
     * visible to the device without an explicit vkFlushMappedMemoryRanges.
     */
    err = new_Buffer_DeviceMemory(
        &staging_buffer,
        &staging_memory,
        image_size,
        engine->physical_device,
        engine->dev,
        VK_BUFFER_USAGE_TRANSFER_SRC_BIT,
        VK_MEMORY_PROPERTY_HOST_VISIBLE_BIT |
        VK_MEMORY_PROPERTY_HOST_COHERENT_BIT);

    NK_ASSERT(err == ERR_OK);

    /*
     * Map and fill the staging buffer.
     */
    void *mapped_data = NULL;

    result = vkMapMemory(engine->dev,
                         staging_memory,
                         0,
                         image_size,
                         0,
                         &mapped_data);
    NK_ASSERT(result == VK_SUCCESS);

    memcpy(mapped_data, pixels, (size_t)image_size);

    vkUnmapMemory(engine->dev, staging_memory);

    /*
     * Allocate a short-lived transfer command buffer.
     */
    VkCommandBufferAllocateInfo command_alloc_info = {0};
    command_alloc_info.sType =
        VK_STRUCTURE_TYPE_COMMAND_BUFFER_ALLOCATE_INFO;
    command_alloc_info.commandPool = engine->cmd_pool;
    command_alloc_info.level = VK_COMMAND_BUFFER_LEVEL_PRIMARY;
    command_alloc_info.commandBufferCount = 1;

    result = vkAllocateCommandBuffers(engine->dev,
                                      &command_alloc_info,
                                      &command_buffer);
    NK_ASSERT(result == VK_SUCCESS);

    VkCommandBufferBeginInfo begin_info = {0};
    begin_info.sType = VK_STRUCTURE_TYPE_COMMAND_BUFFER_BEGIN_INFO;
    begin_info.flags =
        VK_COMMAND_BUFFER_USAGE_ONE_TIME_SUBMIT_BIT;

    result = vkBeginCommandBuffer(command_buffer, &begin_info);
    NK_ASSERT(result == VK_SUCCESS);

    /*
     * Transition image from UNDEFINED to TRANSFER_DST_OPTIMAL.
     */
    VkImageMemoryBarrier to_transfer = {0};
    to_transfer.sType =
        VK_STRUCTURE_TYPE_IMAGE_MEMORY_BARRIER;
    to_transfer.srcAccessMask = 0;
    to_transfer.dstAccessMask =
        VK_ACCESS_TRANSFER_WRITE_BIT;
    to_transfer.oldLayout =
        VK_IMAGE_LAYOUT_UNDEFINED;
    to_transfer.newLayout =
        VK_IMAGE_LAYOUT_TRANSFER_DST_OPTIMAL;
    to_transfer.srcQueueFamilyIndex =
        VK_QUEUE_FAMILY_IGNORED;
    to_transfer.dstQueueFamilyIndex =
        VK_QUEUE_FAMILY_IGNORED;
    to_transfer.image = image;
    to_transfer.subresourceRange.aspectMask =
        VK_IMAGE_ASPECT_COLOR_BIT;
    to_transfer.subresourceRange.baseMipLevel = 0;
    to_transfer.subresourceRange.levelCount = 1;
    to_transfer.subresourceRange.baseArrayLayer = 0;
    to_transfer.subresourceRange.layerCount = 1;

    vkCmdPipelineBarrier(command_buffer,
                         VK_PIPELINE_STAGE_TOP_OF_PIPE_BIT,
                         VK_PIPELINE_STAGE_TRANSFER_BIT,
                         0,
                         0,
                         NULL,
                         0,
                         NULL,
                         1,
                         &to_transfer);

    /*
     * Copy staging buffer contents into the image.
     */
    VkBufferImageCopy copy_region = {0};
    copy_region.bufferOffset = 0;
    copy_region.bufferRowLength = 0;
    copy_region.bufferImageHeight = 0;
    copy_region.imageSubresource.aspectMask =
        VK_IMAGE_ASPECT_COLOR_BIT;
    copy_region.imageSubresource.mipLevel = 0;
    copy_region.imageSubresource.baseArrayLayer = 0;
    copy_region.imageSubresource.layerCount = 1;
    copy_region.imageOffset.x = 0;
    copy_region.imageOffset.y = 0;
    copy_region.imageOffset.z = 0;
    copy_region.imageExtent.width = width;
    copy_region.imageExtent.height = height;
    copy_region.imageExtent.depth = 1;

    vkCmdCopyBufferToImage(command_buffer,
                           staging_buffer,
                           image,
                           VK_IMAGE_LAYOUT_TRANSFER_DST_OPTIMAL,
                           1,
                           &copy_region);

    /*
     * Transition image from TRANSFER_DST_OPTIMAL to
     * SHADER_READ_ONLY_OPTIMAL.
     */
    VkImageMemoryBarrier to_shader = {0};
    to_shader.sType =
        VK_STRUCTURE_TYPE_IMAGE_MEMORY_BARRIER;
    to_shader.srcAccessMask =
        VK_ACCESS_TRANSFER_WRITE_BIT;
    to_shader.dstAccessMask =
        VK_ACCESS_SHADER_READ_BIT;
    to_shader.oldLayout =
        VK_IMAGE_LAYOUT_TRANSFER_DST_OPTIMAL;
    to_shader.newLayout =
        VK_IMAGE_LAYOUT_SHADER_READ_ONLY_OPTIMAL;
    to_shader.srcQueueFamilyIndex =
        VK_QUEUE_FAMILY_IGNORED;
    to_shader.dstQueueFamilyIndex =
        VK_QUEUE_FAMILY_IGNORED;
    to_shader.image = image;
    to_shader.subresourceRange.aspectMask =
        VK_IMAGE_ASPECT_COLOR_BIT;
    to_shader.subresourceRange.baseMipLevel = 0;
    to_shader.subresourceRange.levelCount = 1;
    to_shader.subresourceRange.baseArrayLayer = 0;
    to_shader.subresourceRange.layerCount = 1;

    vkCmdPipelineBarrier(command_buffer,
                         VK_PIPELINE_STAGE_TRANSFER_BIT,
                         VK_PIPELINE_STAGE_FRAGMENT_SHADER_BIT,
                         0,
                         0,
                         NULL,
                         0,
                         NULL,
                         1,
                         &to_shader);

    result = vkEndCommandBuffer(command_buffer);
    NK_ASSERT(result == VK_SUCCESS);

    /*
     * Submit synchronously.
     */
    VkFenceCreateInfo fence_info = {0};
    fence_info.sType = VK_STRUCTURE_TYPE_FENCE_CREATE_INFO;

    result = vkCreateFence(engine->dev,
                           &fence_info,
                           NULL,
                           &fence);
    NK_ASSERT(result == VK_SUCCESS);

    VkSubmitInfo submit_info = {0};
    submit_info.sType = VK_STRUCTURE_TYPE_SUBMIT_INFO;
    submit_info.commandBufferCount = 1;
    submit_info.pCommandBuffers = &command_buffer;

    result = vkQueueSubmit(engine->graphics_queue,
                           1,
                           &submit_info,
                           fence);
    NK_ASSERT(result == VK_SUCCESS);

    result = vkWaitForFences(engine->dev,
                             1,
                             &fence,
                             VK_TRUE,
                             UINT64_MAX);
    NK_ASSERT(result == VK_SUCCESS);

    vkDestroyFence(engine->dev, fence, NULL);

    vkFreeCommandBuffers(engine->dev,
                         engine->cmd_pool,
                         1,
                         &command_buffer);

    /*
     * The transfer has completed, so the staging resources can
     * be destroyed.
     */
    vkDestroyBuffer(engine->dev,
                    staging_buffer,
                    NULL);

    vkFreeMemory(engine->dev,
                 staging_memory,
                 NULL);

    /*
     * Create the image view.
     */
    VkImageViewCreateInfo view_info = {0};
    view_info.sType =
        VK_STRUCTURE_TYPE_IMAGE_VIEW_CREATE_INFO;
    view_info.image = image;
    view_info.viewType = VK_IMAGE_VIEW_TYPE_2D;
    view_info.format = VK_FORMAT_R8G8B8A8_UNORM;
    view_info.subresourceRange.aspectMask =
        VK_IMAGE_ASPECT_COLOR_BIT;
    view_info.subresourceRange.baseMipLevel = 0;
    view_info.subresourceRange.levelCount = 1;
    view_info.subresourceRange.baseArrayLayer = 0;
    view_info.subresourceRange.layerCount = 1;

    result = vkCreateImageView(engine->dev,
                               &view_info,
                               NULL,
                               &image_view);
    NK_ASSERT(result == VK_SUCCESS);

    result_image.image = image;
    result_image.allocation = image_memory;
    result_image.view = image_view;

    return result_image;
}

static void
nk_vk_destroy_font_atlas(void)
{
    /*
     * The descriptor set is owned by vk.descriptor_pool.
     *
     * This requires the pool to have been created with:
     *
     * VK_DESCRIPTOR_POOL_CREATE_FREE_DESCRIPTOR_SET_BIT
     */
    if (wr.font_descriptor_set != VK_NULL_HANDLE)
    {
        if (vk.descriptor_pool != VK_NULL_HANDLE)
        {
            VkResult result = vkFreeDescriptorSets(
                vk.dev,
                vk.descriptor_pool,
                1,
                &wr.font_descriptor_set);

            if (result != VK_SUCCESS)
            {
                LOG_ERROR_ARGS(
                    ERR_LEVEL_ERROR,
                    "failed to free font descriptor set: %s",
                    vkstrerror(result));
            }
        }

        wr.font_descriptor_set = VK_NULL_HANDLE;
    }

    /*
     * Destroy the image view before destroying the image.
     */
    if (wr.font_image_view != VK_NULL_HANDLE)
    {
        vkDestroyImageView(
            vk.dev,
            wr.font_image_view,
            NULL);

        wr.font_image_view = VK_NULL_HANDLE;
    }

    /*
     * Destroy the image before freeing its memory.
     */
    if (wr.font_image != VK_NULL_HANDLE)
    {
        vkDestroyImage(
            vk.dev,
            wr.font_image,
            NULL);

        wr.font_image = VK_NULL_HANDLE;
    }

    /*
     * VkDeviceMemory replaces the old VmaAllocation.
     */
    if (wr.font_memory != VK_NULL_HANDLE)
    {
        vkFreeMemory(
            vk.dev,
            wr.font_memory,
            NULL);

        wr.font_memory = VK_NULL_HANDLE;
    }

    /*
     * The Nuklear context must no longer use the atlas before it is cleared.
     */
    nk_font_atlas_clear(&wr.atlas);

    wr.font_tex = nk_handle_ptr(NULL);
}


static void
nk_vk_upload_font_atlas(struct VkEngine *engine,
                        struct WidgetRenderer *renderer,
                        const void *pixels,
                        int width,
                        int height)
{
    NkVkImage font_image =
	nk_vk_upload_rgba8_image(
	    engine,
	    pixels,
	    (uint32_t)width,
	    (uint32_t)height);

    if (font_image.image == VK_NULL_HANDLE ||
	font_image.allocation == VK_NULL_HANDLE ||
	font_image.view == VK_NULL_HANDLE) {
	goto fail_atlas;
    }

    renderer->font_image = font_image.image;
    renderer->font_alloc = font_image.allocation;
    renderer->font_image_view = font_image.view;

    fail_atlas:
    log_info("nk_vk_upload_font_atlas failed ...\n");

}
static bool
nk_vk_create_font_atlas(void)
{
    struct nk_font_atlas *atlas = &wr.atlas;
    struct nk_font *font;
    const void *pixels;

    int atlas_width = 0;
    int atlas_height = 0;

    VkResult result;

    if (vk.dev == VK_NULL_HANDLE ||
        vk.descriptor_pool == VK_NULL_HANDLE ||
        vk.texture_sampler == VK_NULL_HANDLE ||
        wr.texture_descriptor_set_layout == VK_NULL_HANDLE)
    {
        return false;
    }

    wr.font_image = VK_NULL_HANDLE;
    wr.font_memory = VK_NULL_HANDLE;
    wr.font_image_view = VK_NULL_HANDLE;
    wr.font_descriptor_set = VK_NULL_HANDLE;

    nk_font_atlas_init_default(atlas);
    nk_font_atlas_begin(atlas);

    font = nk_font_atlas_add_default(
        atlas,
        16.0f,
        NULL);

    if (font == NULL)
        goto fail_atlas;

    pixels = nk_font_atlas_bake(
        atlas,
        &atlas_width,
        &atlas_height,
        NK_FONT_ATLAS_RGBA32);

    if (pixels == NULL ||
        atlas_width <= 0 ||
        atlas_height <= 0)
    {
        goto fail_atlas;
    }

    /*
     * This helper must create the VkImage, allocate VkDeviceMemory,
     * create the image view, upload the pixels, and transition the
     * image to VK_IMAGE_LAYOUT_SHADER_READ_ONLY_OPTIMAL.
     */
    NkVkImage font_image = nk_vk_upload_rgba8_image(
        &vk,
        pixels,
        (uint32_t)atlas_width,
        (uint32_t)atlas_height);

    if (font_image.image == VK_NULL_HANDLE ||
        font_image.memory == VK_NULL_HANDLE ||
        font_image.view == VK_NULL_HANDLE)
    {
        /*
         * Clean up partially-created image resources.
         */
        if (font_image.view != VK_NULL_HANDLE)
        {
            vkDestroyImageView(
                vk.dev,
                font_image.view,
                NULL);
        }

        if (font_image.image != VK_NULL_HANDLE)
        {
            vkDestroyImage(
                vk.dev,
                font_image.image,
                NULL);
        }

        if (font_image.memory != VK_NULL_HANDLE)
        {
            vkFreeMemory(
                vk.dev,
                font_image.memory,
                NULL);
        }

        goto fail_atlas;
    }

    wr.font_image = font_image.image;
    wr.font_memory = font_image.memory;
    wr.font_image_view = font_image.view;

    /*
     * Allocate the font descriptor set.
     */
    VkDescriptorSetAllocateInfo allocate_info = {
        .sType = VK_STRUCTURE_TYPE_DESCRIPTOR_SET_ALLOCATE_INFO,
        .descriptorPool = vk.descriptor_pool,
        .descriptorSetCount = 1,
        .pSetLayouts = &wr.texture_descriptor_set_layout
    };

    result = vkAllocateDescriptorSets(
        vk.dev,
        &allocate_info,
        &wr.font_descriptor_set);

    if (result != VK_SUCCESS)
    {
        LOG_ERROR_ARGS(
            ERR_LEVEL_ERROR,
            "failed to allocate font descriptor set: %s",
            vkstrerror(result));

        goto fail_image;
    }

    VkDescriptorImageInfo descriptor_image = {
        .sampler = vk.texture_sampler,
        .imageView = wr.font_image_view,
        .imageLayout = VK_IMAGE_LAYOUT_SHADER_READ_ONLY_OPTIMAL
    };

    VkWriteDescriptorSet descriptor_write = {
        .sType = VK_STRUCTURE_TYPE_WRITE_DESCRIPTOR_SET,
        .dstSet = wr.font_descriptor_set,
        .dstBinding = 0,
        .dstArrayElement = 0,
        .descriptorCount = 1,
        .descriptorType = VK_DESCRIPTOR_TYPE_COMBINED_IMAGE_SAMPLER,
        .pImageInfo = &descriptor_image
    };

    vkUpdateDescriptorSets(
        vk.dev,
        1,
        &descriptor_write,
        0,
        NULL);

    /*
     * Nuklear stores the descriptor-set handle as the font texture.
     */
    nk_font_atlas_end(
        atlas,
        nk_handle_ptr(&wr.font_descriptor_set),
        &wr.tex_null);

    wr.font_tex = nk_handle_ptr(&wr.font_descriptor_set);

    return true;

fail_image:
    if (wr.font_descriptor_set != VK_NULL_HANDLE)
    {
        /*
         * This requires the descriptor pool to have been created with
         * VK_DESCRIPTOR_POOL_CREATE_FREE_DESCRIPTOR_SET_BIT.
         */
        vkFreeDescriptorSets(
            vk.dev,
            vk.descriptor_pool,
            1,
            &wr.font_descriptor_set);

        wr.font_descriptor_set = VK_NULL_HANDLE;
    }

    if (wr.font_image_view != VK_NULL_HANDLE)
    {
        vkDestroyImageView(
            vk.dev,
            wr.font_image_view,
            NULL);

        wr.font_image_view = VK_NULL_HANDLE;
    }

    if (wr.font_image != VK_NULL_HANDLE)
    {
        vkDestroyImage(
            vk.dev,
            wr.font_image,
            NULL);

        wr.font_image = VK_NULL_HANDLE;
    }

    if (wr.font_memory != VK_NULL_HANDLE)
    {
        vkFreeMemory(
            vk.dev,
            wr.font_memory,
            NULL);

        wr.font_memory = VK_NULL_HANDLE;
    }

fail_atlas:
    nk_font_atlas_clear(atlas);

    wr.font_tex = nk_handle_ptr(NULL);

    return false;
}



static bool
nk_vk_create_descriptor_set_layouts(
    WidgetRenderer *renderer,
    VkEngine *engine)
{
    VkResult result;

    VkDescriptorSetLayoutBinding uniform_binding = {
        .binding = 0,
        .descriptorType =
            VK_DESCRIPTOR_TYPE_UNIFORM_BUFFER,
        .descriptorCount = 1,
        .stageFlags =
            VK_SHADER_STAGE_VERTEX_BIT
    };

    VkDescriptorSetLayoutCreateInfo uniform_info = {
        .sType =
            VK_STRUCTURE_TYPE_DESCRIPTOR_SET_LAYOUT_CREATE_INFO,
        .bindingCount = 1,
        .pBindings = &uniform_binding
    };

    result = vkCreateDescriptorSetLayout(
        engine->dev,
        &uniform_info,
        NULL,
        &renderer->uniform_descriptor_set_layout);

    if (result != VK_SUCCESS)
        return false;

    VkDescriptorSetLayoutBinding texture_binding = {
        .binding = 0,
        .descriptorType =
            VK_DESCRIPTOR_TYPE_COMBINED_IMAGE_SAMPLER,
        .descriptorCount = 1,
        .stageFlags =
            VK_SHADER_STAGE_FRAGMENT_BIT
    };

    VkDescriptorSetLayoutCreateInfo texture_info = {
        .sType =
            VK_STRUCTURE_TYPE_DESCRIPTOR_SET_LAYOUT_CREATE_INFO,
        .bindingCount = 1,
        .pBindings = &texture_binding
    };

    result = vkCreateDescriptorSetLayout(
        engine->dev,
        &texture_info,
        NULL,
        &renderer->texture_descriptor_set_layout);

    if (result != VK_SUCCESS)
    {
        vkDestroyDescriptorSetLayout(
            engine->dev,
            renderer->uniform_descriptor_set_layout,
            NULL);

        renderer->uniform_descriptor_set_layout =
            VK_NULL_HANDLE;

        return false;
    }

    return true;
}

static bool
nk_vk_create_pipeline_layout(
    WidgetRenderer *renderer,
    VkEngine *engine)
{
    VkDescriptorSetLayout layouts[2] = {
        renderer->uniform_descriptor_set_layout,
        renderer->texture_descriptor_set_layout
    };

    VkPipelineLayoutCreateInfo info = {
        .sType =
            VK_STRUCTURE_TYPE_PIPELINE_LAYOUT_CREATE_INFO,
        .setLayoutCount = 2,
        .pSetLayouts = layouts
    };

    return vkCreatePipelineLayout(
        engine->dev,
        &info,
        NULL,
        &renderer->pipeline_layout) == VK_SUCCESS;
}

static bool
nk_vk_create_uniform_descriptor_set(
    WidgetRenderer *renderer,
    VkEngine *engine,
    WidgetFrameData *frame)
{
    VkDescriptorSetAllocateInfo alloc_info = {
        .sType =
            VK_STRUCTURE_TYPE_DESCRIPTOR_SET_ALLOCATE_INFO,
        .descriptorPool = engine->descriptor_pool,
        .descriptorSetCount = 1,
        .pSetLayouts =
            &renderer->uniform_descriptor_set_layout
    };

    if (vkAllocateDescriptorSets(
            engine->dev,
            &alloc_info,
            &frame->uniform_descriptor_set) != VK_SUCCESS)
    {
        return false;
    }

    VkDescriptorBufferInfo buffer_info = {
        .buffer = frame->uniform_buffer,
        .offset = 0,
        .range = sizeof(struct WidgetUniform)
    };

    VkWriteDescriptorSet write = {
        .sType =
            VK_STRUCTURE_TYPE_WRITE_DESCRIPTOR_SET,
        .dstSet = frame->uniform_descriptor_set,
        .dstBinding = 0,
        .descriptorCount = 1,
        .descriptorType =
            VK_DESCRIPTOR_TYPE_UNIFORM_BUFFER,
        .pBufferInfo = &buffer_info
    };

    vkUpdateDescriptorSets(
        engine->dev,
        1,
        &write,
        0,
        NULL);

    return true;
}

static bool
nk_vk_register_texture(
    WidgetRenderer *renderer,
    VkEngine *engine,
    VkImageView image_view,
    VkDescriptorSet *out_descriptor_set)
{
    if (renderer->texture_descriptor_sets_len ==
        renderer->texture_descriptor_sets_capacity)
    {
        uint32_t capacity =
            renderer->texture_descriptor_sets_capacity ?
            renderer->texture_descriptor_sets_capacity * 2 :
            16;

        NkVulkanTextureDescriptorSet *items =
            realloc(
                renderer->texture_descriptor_sets,
                capacity * sizeof(*items));

        if (items == NULL)
            return false;

        renderer->texture_descriptor_sets = items;
        renderer->texture_descriptor_sets_capacity =
            capacity;
    }

    VkDescriptorImageInfo image_info = {
        .sampler = engine->texture_sampler,
        .imageView = image_view,
        .imageLayout =
            VK_IMAGE_LAYOUT_SHADER_READ_ONLY_OPTIMAL
    };

    VkDescriptorSetAllocateInfo alloc_info = {
        .sType =
            VK_STRUCTURE_TYPE_DESCRIPTOR_SET_ALLOCATE_INFO,
        .descriptorPool = engine->descriptor_pool,
        .descriptorSetCount = 1,
        .pSetLayouts =
            &renderer->texture_descriptor_set_layout
    };

    VkDescriptorSet descriptor_set;

    if (vkAllocateDescriptorSets(
            engine->dev,
            &alloc_info,
            &descriptor_set) != VK_SUCCESS)
    {
        return false;
    }

    VkWriteDescriptorSet write = {
        .sType =
            VK_STRUCTURE_TYPE_WRITE_DESCRIPTOR_SET,
        .dstSet = descriptor_set,
        .dstBinding = 0,
        .descriptorCount = 1,
        .descriptorType =
            VK_DESCRIPTOR_TYPE_COMBINED_IMAGE_SAMPLER,
        .pImageInfo = &image_info
    };

    vkUpdateDescriptorSets(
        engine->dev,
        1,
        &write,
        0,
        NULL);

    uint32_t index =
        renderer->texture_descriptor_sets_len++;

    renderer->texture_descriptor_sets[index].image_view =
        image_view;

    renderer->texture_descriptor_sets[index].descriptor_set =
        descriptor_set;

    if (out_descriptor_set != NULL)
        *out_descriptor_set = descriptor_set;

    return true;
}


static void *
nk_vk_alloc(void *userdata, nk_size size)
{
    (void)userdata;
    return malloc(size);
}

static void
nk_vk_free(void *userdata, void *ptr)
{
    (void)userdata;
    free(ptr);
}

/**
 * 
 * 
 * VkEngine owns:
    VkDevice
    VMA allocator
    render pass
    descriptor pool
    texture sampler
    queues
    command pools
    swapchain resources

WidgetRenderer owns:
    Nuklear context
    Nuklear command buffer
    pipeline
    pipeline layout
    descriptor-set layouts
    UI buffers
    font image
    font image view
    font descriptor set
    application texture descriptor records
    
    WidgetRendererInit()
    └── nk_vk_init()
          ├── create descriptor-set layouts
          ├── create pipeline layout and pipeline
          ├── create per-frame buffers
          ├── create font atlas pixels
          ├── upload font image
          ├── allocate font descriptor set
          ├── nk_vk_update_font_descriptor()
          └── nk_init()
    
    
 */


static bool
nk_vk_init(
    WidgetRenderer *renderer,
    VkEngine *engine)
{
    if (renderer == NULL || engine == NULL)
        return false;

    if (engine->dev == VK_NULL_HANDLE ||
        engine->dev_physical == VK_NULL_HANDLE ||
        engine->renderpass == VK_NULL_HANDLE ||
        engine->descriptor_pool == VK_NULL_HANDLE ||
        engine->texture_sampler == VK_NULL_HANDLE)
    {
        return false;
    }

    nk_vk_reset_renderer(renderer);

    /*
     * These resources are owned by WidgetRenderer:
     *
     *   descriptor-set layouts
     *   pipeline layout
     *   graphics pipeline
     *   per-frame buffers
     *   font image and image view
     *   font descriptor set
     *   texture descriptor table
     */
    if (!nk_vk_create_descriptor_set_layouts(
            renderer,
            engine))
    {
        goto fail;
    }

    if (!nk_vk_create_pipeline_layout(
            renderer,
            engine))
    {
        goto fail;
    }

    if (!nk_vk_create_pipeline(
            renderer,
            engine))
    {
        goto fail;
    }

    if (!nk_vk_create_frame_resources(
            renderer,
            engine))
    {
        goto fail;
    }

    if (!nk_vk_create_font_atlas(
            renderer,
            engine))
    {
        goto fail;
    }

    return true;

fail:
    nk_vk_destroy(renderer, engine);
    return false;
}

static void *widget_nk_alloc(
    nk_handle userdata,
    void *old,
    nk_size size)
{
    (void)userdata;

    if (size == 0)
    {
        free(old);
        return NULL;
    }

    return realloc(old, size);
}

static void widget_nk_free(
    nk_handle userdata,
    void *old)
{
    (void)userdata;
    free(old);
}

/*
 * vk must still be valid when this function is called:
 *
 *   - vk.dev
 *   - vk.vma
 *   - vk.descriptor_pool
 *
 * are owned by VkEngine and are not destroyed here.
 */
void
nk_vk_shutdown(struct WidgetRenderer *renderer,
               const struct VkEngine *vk)
{
    if (renderer == NULL || vk == NULL) {
        return;
    }

    /*
     * nk_vk_destroy() waits for the device to become idle and destroys
     * renderer-owned Vulkan resources.
     */
    nk_vk_destroy(renderer, (VkEngine *)vk);

    /*
     * Destroy or release anything that nk_vk_destroy() does not handle:
     *
     * - texture_descriptor_sets array
     * - GLFW callback restoration
     * - Nuklear CPU-side state
     * - renderer-owned persistent state
     */

    free(renderer->texture_descriptor_sets);
    renderer->texture_descriptor_sets = NULL;
    renderer->texture_descriptor_sets_len = 0;
    renderer->texture_descriptor_sets_capacity = 0;

    if (renderer->callbacks_installed && renderer->window) 
    {
        glfwSetScrollCallback(renderer->window,
                              renderer->previous_scroll_callback);
        glfwSetCharCallback(renderer->window,
                            renderer->previous_char_callback);
        glfwSetKeyCallback(renderer->window,
                           renderer->previous_key_callback);
        glfwSetMouseButtonCallback(
            renderer->window,
            renderer->previous_mouse_button_callback);
    }

    renderer->callbacks_installed = false;
    renderer->previous_scroll_callback = NULL;
    renderer->previous_char_callback = NULL;
    renderer->previous_key_callback = NULL;
    renderer->previous_mouse_button_callback = NULL;

    nk_buffer_free(&renderer->cmds);
    nk_font_atlas_clear(&renderer->atlas);

    if (renderer->nk_initialized) {
        nk_free(&renderer->ctx);
        renderer->nk_initialized = false;
    }

    renderer->quad_count = 0;
}

void
WidgetRendererDestroy(WidgetRendererHandle handle)
{
    WidgetRenderer *renderer =
        handle_deref(&alloc, handle);

    if (renderer == NULL)
        return;

    event_unbind(
        EVENT_RENDERERS_DESTROY,
        widget_renderer_destroy_callback,
        handle
    );

    /*
     * All renderer-owned Vulkan resources must be idle before cleanup.
     */
    if (vk.dev != VK_NULL_HANDLE)
    {
        VkResult ret = vkDeviceWaitIdle(vk.dev);

        if (ret != VK_SUCCESS)
        {
            engine_crash("vkDeviceWaitIdle failed during renderer shutdown");
            return;
        }
    }

    /*
     * nk_vk_shutdown() destroys all renderer-owned Vulkan and Nuklear
     * resources. vk.dev, vk.vma, and vk.descriptor_pool must still be valid.
     */
    nk_vk_shutdown(
        renderer,
        &vk
    );
    
    /// WidgetRendererInit initialized data buffers
    nk_free(&renderer->ctx);
    nk_buffer_free(&renderer->cmds);
    nk_buffer_free(&renderer->vertex_nk_buffer);
    nk_buffer_free(&renderer->index_nk_buffer);

    /*
     * Destroy any additional WidgetRenderer-owned resources not handled
     * by nk_vk_shutdown().
     */
    // text_engine_destroy(renderer->engine);
    // renderer->engine = NULL;

    handle_free(&alloc, &handle);
}

/**
 * 
 * current_frame
    ├── engine->frames[current_frame]
    │       ├── flight fence
    │       ├── image_available semaphore
    │       ├── render_finished semaphore
    │       └── cmd_buf
    │
    └── widget_renderer->frame[current_frame]
            ├── UI vertex buffer
            ├── UI index buffer
            └── other per-frame UI resources
	    
    

 * Pass the WidgetFrameData belonging to the same logical frame as VkEngine::frames[engine->current_frame].

VkFrame and WidgetFrameData serve different purposes:

    VkFrame: engine-owned synchronization and command recording state.
    WidgetFrameData: UI-owned per-frame GPU resources, such as vertex/index buffers.
    They must be paired by frame slot, not by swapchain image index.

For example:
c

uint32_t frame_slot = engine->current_frame;

VkFrame *vk_frame = &engine->frames[frame_slot];
WidgetFrameData *ui_frame = &engine->widget_renderer->frame[frame_slot];

bool ok = WidgetRendererRecord(
    engine->widget_renderer,
    engine,
    ui_frame);
    
    No—you do not need to reset all those variables on every iteration. The important distinction is between:

    Per-frame state, which must be selected/reset when starting a new frame slot.
    Per-draw state, which must be set whenever a draw command requires it.
    Persistent renderer state, which can remain unchanged until explicitly modified.

In your function, the loop should update the scissor, texture descriptor, and index offset for each Nuklear draw command. It does not need to reset the pipeline, vertex buffer, index buffer, viewport, or descriptor state before every command unless your rendering code changes them.

The main problem is that WidgetFrameData currently appears to contain both UI GPU resources and Vulkan recording state:
 * 
 * */
bool
WidgetRendererRecord(
    WidgetRenderer *renderer,
    VkEngine *engine,
    VkFrame *vk_frame,
    WidgetFrameData *ui_frame)
{
    if (renderer == NULL ||
        engine == NULL ||
        vk_frame == NULL ||
        ui_frame == NULL)
    {
        return false;
    }

    struct nk_buffer vertex_buffer;
    struct nk_buffer index_buffer;

    nk_buffer_init_default(&vertex_buffer);
    nk_buffer_init_default(&index_buffer);

    enum nk_convert_result convert_result =
        nk_convert(
            &renderer->ctx,
            &renderer->cmds,
            &vertex_buffer,
            &index_buffer,
            &renderer->convert_config);

    if (convert_result != NK_CONVERT_SUCCESS)
    {
        nk_buffer_free(&vertex_buffer);
        nk_buffer_free(&index_buffer);
        return false;
    }

    const void *vertices =
	nk_buffer_memory_const(&vertex_buffer);

    const void *indices =
	nk_buffer_memory_const(&index_buffer);

    size_t vertex_size =
	nk_buffer_total(&vertex_buffer);

    size_t index_size =
	nk_buffer_total(&index_buffer);

    uint32_t index_count = 0;

    const struct nk_draw_command *cmd;

    nk_draw_foreach(cmd, &renderer->ctx, &renderer->cmds)
    {
	if (cmd->elem_count != 0)
	    index_count += cmd->elem_count;
    }

    uint32_t vertex_count = 0;

    if (renderer->convert_config.vertex_size != 0)
    {
	vertex_count =
	    (uint32_t)(
		vertex_size /
		renderer->convert_config.vertex_size);
    }

    ui_frame->index_count = index_count;

    if (vertex_count == 0 ||
	index_count == 0 ||
	vertex_size == 0 ||
	index_size == 0)
    {
	nk_buffer_free(&vertex_buffer);
	nk_buffer_free(&index_buffer);
	return true;
    }

    /*
     * Upload the converted Nuklear index data.
     */
    if (!GfxFrameUploadBuffer(
            ui_frame,
            &ui_frame->index_buffer,
            &ui_frame->index_alloc,
            indices,
            index_size,
            VK_BUFFER_USAGE_INDEX_BUFFER_BIT))
    {
        nk_buffer_free(&vertex_buffer);
        nk_buffer_free(&index_buffer);
        return false;
    }

    VkCommandBuffer command_buffer = vk_frame->cmd_buf;

    vkCmdBindPipeline(
        command_buffer,
        VK_PIPELINE_BIND_POINT_GRAPHICS,
        renderer->pipeline);

    VkDeviceSize vertex_offset = 0;

    vkCmdBindVertexBuffers(
        command_buffer,
        0,
        1,
        &ui_frame->vertex_buffer,
        &vertex_offset);

    vkCmdBindIndexBuffer(
        command_buffer,
        ui_frame->index_buffer,
        0,
        VK_INDEX_TYPE_UINT16);

    vkCmdBindDescriptorSets(
        command_buffer,
        VK_PIPELINE_BIND_POINT_GRAPHICS,
        renderer->pipeline_layout,
        0,
        1,
        &ui_frame->uniform_descriptor_set,
        0,
        NULL);

    vkCmdDrawIndexed(
        command_buffer,
        ui_frame->index_count,
        1,
        0,
        0,
        0);

    nk_buffer_free(&vertex_buffer);
    nk_buffer_free(&index_buffer);

    return true;
}

static void
nk_destroy_frame_buffers(void)
{
    /*
     * Destroy resources belonging to each frame in flight.
     */
    for (uint32_t i = 0; i < VK_FRAMES; ++i)
    {
        WidgetFrameData *frame = &wr.frame[i];

        if (frame->mapped_uniform != NULL) {
            vkUnmapMemory(
                vk.dev,
                frame->uniform_memory
            );

            frame->mapped_uniform = NULL;
        }

        if (frame->uniform_buffer != VK_NULL_HANDLE) {
            vkDestroyBuffer(
                vk.dev,
                frame->uniform_buffer,
                NULL
            );

            frame->uniform_buffer = VK_NULL_HANDLE;
        }

        if (frame->uniform_memory != VK_NULL_HANDLE) {
            vkFreeMemory(
                vk.dev,
                frame->uniform_memory,
                NULL
            );

            frame->uniform_memory = VK_NULL_HANDLE;
        }

        if (frame->mapped_vertex != NULL) {
            vkUnmapMemory(
                vk.dev,
                frame->vertex_memory
            );

            frame->mapped_vertex = NULL;
        }

        if (frame->vertex_buffer != VK_NULL_HANDLE) {
            vkDestroyBuffer(
                vk.dev,
                frame->vertex_buffer,
                NULL
            );

            frame->vertex_buffer = VK_NULL_HANDLE;
        }

        if (frame->vertex_memory != VK_NULL_HANDLE) {
            vkFreeMemory(
                vk.dev,
                frame->vertex_memory,
                NULL
            );

            frame->vertex_memory = VK_NULL_HANDLE;
        }

        if (frame->mapped_index != NULL) {
            vkUnmapMemory(
                vk.dev,
                frame->index_memory
            );

            frame->mapped_index = NULL;
        }

        if (frame->index_buffer != VK_NULL_HANDLE) {
            vkDestroyBuffer(
                vk.dev,
                frame->index_buffer,
                NULL
            );

            frame->index_buffer = VK_NULL_HANDLE;
        }

        if (frame->index_memory != VK_NULL_HANDLE) {
            vkFreeMemory(
                vk.dev,
                frame->index_memory,
                NULL
            );

            frame->index_memory = VK_NULL_HANDLE;
        }

        frame->uniform_descriptor_set = VK_NULL_HANDLE;
        frame->max_vertex_buffer = 0;
        frame->max_index_buffer = 0;
        frame->index_count = 0;
        frame->width = 0;
        frame->height = 0;
    }

    /*
     * Destroy renderer-wide GPU vertex buffer.
     */
    if (wr.vertex_gpu_buffer != VK_NULL_HANDLE) {
        vkDestroyBuffer(
            vk.dev,
            wr.vertex_gpu_buffer,
            NULL
        );

        wr.vertex_gpu_buffer = VK_NULL_HANDLE;
    }

    if (wr.vertex_gpu_memory != VK_NULL_HANDLE) {
        vkFreeMemory(
            vk.dev,
            wr.vertex_gpu_memory,
            NULL
        );

        wr.vertex_gpu_memory = VK_NULL_HANDLE;
    }

    /*
     * Destroy renderer-wide GPU index buffer.
     */
    if (wr.index_gpu_buffer != VK_NULL_HANDLE) {
        vkDestroyBuffer(
            vk.dev,
            wr.index_gpu_buffer,
            NULL
        );

        wr.index_gpu_buffer = VK_NULL_HANDLE;
    }

    if (wr.index_gpu_memory != VK_NULL_HANDLE) {
        vkFreeMemory(
            vk.dev,
            wr.index_gpu_memory,
            NULL
        );

        wr.index_gpu_memory = VK_NULL_HANDLE;
    }

    /*
     * Destroy CPU-side quad data.
     */
    wr.quad_count = 0;

    free(wr.quad_vertices);
    wr.quad_vertices = NULL;
    wr.quad_vertex_capacity = 0;
}

void
nk_destroy_buffers(void)
{
    uint32_t i;

    for (i = 0; i < VK_FRAMES; i++)
    {
        WidgetFrameData *frame = &wr.frame[i];

        if (frame->mapped_uniform != NULL)
        {
            vkUnmapMemory(vk.dev,
                          frame->uniform_memory);
            frame->mapped_uniform = NULL;
        }

        if (frame->mapped_vertex != NULL)
        {
            vkUnmapMemory(vk.dev,
                          frame->vertex_memory);
            frame->mapped_vertex = NULL;
        }

        if (frame->mapped_index != NULL)
        {
            vkUnmapMemory(vk.dev,
                          frame->index_memory);
            frame->mapped_index = NULL;
        }

        if (frame->uniform_buffer != VK_NULL_HANDLE)
        {
            vkDestroyBuffer(vk.dev,
                            frame->uniform_buffer,
                            NULL);
            frame->uniform_buffer = VK_NULL_HANDLE;
        }

        if (frame->uniform_memory != VK_NULL_HANDLE)
        {
            vkFreeMemory(vk.dev,
                         frame->uniform_memory,
                         NULL);
            frame->uniform_memory = VK_NULL_HANDLE;
        }

        if (frame->vertex_buffer != VK_NULL_HANDLE)
        {
            vkDestroyBuffer(vk.dev,
                            frame->vertex_buffer,
                            NULL);
            frame->vertex_buffer = VK_NULL_HANDLE;
        }

        if (frame->vertex_memory != VK_NULL_HANDLE)
        {
            vkFreeMemory(vk.dev,
                         frame->vertex_memory,
                         NULL);
            frame->vertex_memory = VK_NULL_HANDLE;
        }

        if (frame->index_buffer != VK_NULL_HANDLE)
        {
            vkDestroyBuffer(vk.dev,
                            frame->index_buffer,
                            NULL);
            frame->index_buffer = VK_NULL_HANDLE;
        }

        if (frame->index_memory != VK_NULL_HANDLE)
        {
            vkFreeMemory(vk.dev,
                         frame->index_memory,
                         NULL);
            frame->index_memory = VK_NULL_HANDLE;
        }
    }
}


bool
nk_create_buffers(void)
{
    uint32_t i;

    if (vk.dev == VK_NULL_HANDLE ||
        vk.dev_physical == VK_NULL_HANDLE)
    {
        return false;
    }

    for (i = 0; i < VK_FRAMES; i++)
    {
        WidgetFrameData *frame = &wr.frame[i];

        frame->uniform_buffer = VK_NULL_HANDLE;
        frame->uniform_memory = VK_NULL_HANDLE;
        frame->mapped_uniform = NULL;

        frame->vertex_buffer = VK_NULL_HANDLE;
        frame->vertex_memory = VK_NULL_HANDLE;
        frame->mapped_vertex = NULL;

        frame->index_buffer = VK_NULL_HANDLE;
        frame->index_memory = VK_NULL_HANDLE;
        frame->mapped_index = NULL;
    }

    for (i = 0; i < VK_FRAMES; i++)
    {
        WidgetFrameData *frame = &wr.frame[i];
        ErrVal err;
        VkResult result;

        if (frame->max_vertex_buffer == 0 ||
            frame->max_index_buffer == 0)
        {
            log_error(
                "Invalid buffer sizes for frame %u: "
                "vertex=%u, index=%u",
                i,
                frame->max_vertex_buffer,
                frame->max_index_buffer);

            goto fail;
        }

        /*
         * Vertex buffer.
         */
        err = new_Buffer_DeviceMemory(
            &frame->vertex_buffer,
            &frame->vertex_memory,
            frame->max_vertex_buffer,
            vk.dev_physical,
            vk.dev,
            VK_BUFFER_USAGE_VERTEX_BUFFER_BIT,
            VK_MEMORY_PROPERTY_HOST_VISIBLE_BIT |
            VK_MEMORY_PROPERTY_HOST_COHERENT_BIT);

        if (err != ERR_OK)
        {
            log_error(
                "Failed to create vertex buffer for frame %u",
                i);
            goto fail;
        }

        /*
         * Index buffer.
         */
        err = new_Buffer_DeviceMemory(
            &frame->index_buffer,
            &frame->index_memory,
            frame->max_index_buffer,
            vk.dev_physical,
            vk.dev,
            VK_BUFFER_USAGE_INDEX_BUFFER_BIT,
            VK_MEMORY_PROPERTY_HOST_VISIBLE_BIT |
            VK_MEMORY_PROPERTY_HOST_COHERENT_BIT);

        if (err != ERR_OK)
        {
            log_error(
                "Failed to create index buffer for frame %u",
                i);
            goto fail;
        }

        /*
         * Uniform buffer.
         */
        frame->uniform_buffer_size = sizeof(struct Mat4f);

        err = new_Buffer_DeviceMemory(
            &frame->uniform_buffer,
            &frame->uniform_memory,
            frame->uniform_buffer_size,
            vk.dev_physical,
            vk.dev,
            VK_BUFFER_USAGE_UNIFORM_BUFFER_BIT,
            VK_MEMORY_PROPERTY_HOST_VISIBLE_BIT |
            VK_MEMORY_PROPERTY_HOST_COHERENT_BIT);

        if (err != ERR_OK)
        {
            log_error(
                "Failed to create uniform buffer for frame %u",
                i);
            goto fail;
        }

        /*
         * Map vertex memory.
         */
        result = vkMapMemory(
            vk.dev,
            frame->vertex_memory,
            0,
            frame->max_vertex_buffer,
            0,
            &frame->mapped_vertex);

        if (result != VK_SUCCESS)
        {
            log_error(
                "Failed to map vertex buffer for frame %u: %d",
                i,
                (int)result);
            goto fail;
        }

        /*
         * Map index memory.
         */
        result = vkMapMemory(
            vk.dev,
            frame->index_memory,
            0,
            frame->max_index_buffer,
            0,
            &frame->mapped_index);

        if (result != VK_SUCCESS)
        {
            log_error(
                "Failed to map index buffer for frame %u: %d",
                i,
                (int)result);
            goto fail;
        }

        /*
         * Map uniform memory.
         */
        result = vkMapMemory(
            vk.dev,
            frame->uniform_memory,
            0,
            frame->uniform_buffer_size,
            0,
            &frame->mapped_uniform);

        if (result != VK_SUCCESS)
        {
            log_error(
                "Failed to map uniform buffer for frame %u: %d",
                i,
                (int)result);
            goto fail;
        }
    }

    return true;

fail:
    nk_destroy_buffers();
    return false;
}



void
WidgetRendererBuildWidgets()
{
    struct nk_context *ctx;
    struct nk_colorf *bg;
    struct nk_image *img;

    ctx = &wr.ctx;
    bg  = &wr.background;
    img = &wr.image;

    ///
    //  NUKLEAR NEW FRAME - handles input before draw commands
    ///
    nk_glfw3_new_frame();

    /*
     * GUI
     */
    if (nk_begin(
            ctx,
            "Demo",
            nk_rect(50, 50, 230, 250),
            NK_WINDOW_BORDER |
            NK_WINDOW_MOVABLE |
            NK_WINDOW_SCALABLE |
            NK_WINDOW_MINIMIZABLE |
            NK_WINDOW_TITLE))
    {
        enum {
            EASY = 0,
            HARD = 1
        };
        static int op = EASY;
        static int property = 20;
        nk_layout_row_static(ctx, 30, 80, 1);

        if (nk_button_label(ctx, "button"))
            fprintf(stdout, "button pressed\n");

        nk_layout_row_dynamic(ctx, 30, 2);

        if (nk_option_label(
                ctx,
                "easy",
                op == EASY))
        {
            op = EASY;
        }

        if (nk_option_label(
                ctx,
                "hard",
                op == HARD))
        {
            op = HARD;
        }

        nk_layout_row_dynamic(ctx, 25, 1);

        nk_property_int(
            ctx,
            "Compression:",
            0,
            &property,
            100,
            10,
            1);

        nk_layout_row_dynamic(ctx, 20, 1);
        nk_label(ctx, "background:", NK_TEXT_LEFT);

        nk_layout_row_dynamic(ctx, 25, 1);

        if (nk_combo_begin_color(
                ctx,
                nk_rgb_cf(*bg),
                nk_vec2(nk_widget_width(ctx), 400)))
        {
            nk_layout_row_dynamic(ctx, 120, 1);

            *bg = nk_color_picker(
                ctx,
                *bg,
                NK_RGBA);

            nk_layout_row_dynamic(ctx, 25, 1);

            bg->r = nk_propertyf(
                ctx, "#R:", 0, bg->r, 1.0f, 0.01f, 0.005f);

            bg->g = nk_propertyf(
                ctx, "#G:", 0, bg->g, 1.0f, 0.01f, 0.005f);

            bg->b = nk_propertyf(
                ctx, "#B:", 0, bg->b, 1.0f, 0.01f, 0.005f);

            bg->a = nk_propertyf(
                ctx, "#A:", 0, bg->a, 1.0f, 0.01f, 0.005f);

            nk_combo_end(ctx);
        }
    }

    nk_end(ctx);

    /*
     * Texture window.
     */
    if (nk_begin(
            ctx,
            "Texture",
            nk_rect(500, 300, 200, 200),
            NK_WINDOW_BORDER |
            NK_WINDOW_MOVABLE |
            NK_WINDOW_SCALABLE |
            NK_WINDOW_MINIMIZABLE |
            NK_WINDOW_TITLE))
    {
        struct nk_command_buffer *canvas;
        struct nk_rect total_space;

        canvas = nk_window_get_canvas(ctx);
        total_space = nk_window_get_content_region(ctx);

        nk_draw_image(
            canvas,
            total_space,
            img,
            nk_white);
    }

    nk_end(ctx);

    /*
     * Optional Nuklear examples.
     */
#ifdef INCLUDE_CALCULATOR
    calculator(ctx);
#endif

#ifdef INCLUDE_CANVAS
    canvas(ctx);
#endif

#ifdef INCLUDE_OVERVIEW
    overview(ctx);
#endif

#ifdef INCLUDE_CONFIGURATOR
    style_configurator(ctx, color_table);
#endif

#ifdef INCLUDE_NODE_EDITOR
    node_editor(ctx);
#endif
}



/**
 * 
 * store Vulkan device state
store swap-chain image information
create sampler
create command pool
create command buffers
create semaphore
create vertex buffer
create index buffer
create uniform buffer
map all buffers
create render resources
 * */


static void
log_vk_sampler_create_info(const VkSamplerCreateInfo *info)
{
    if (info == NULL)
    {
        log_info("VkSamplerCreateInfo = NULL");
        return;
    }

    log_info("VkSamplerCreateInfo:");

    LOG_NK_INT("sType", info->sType);
    LOG_NK_POINTER("pNext", info->pNext);
    LOG_NK_FLAGS("flags", info->flags);

    LOG_NK_INT("magFilter", info->magFilter);
    LOG_NK_INT("minFilter", info->minFilter);
    LOG_NK_INT("mipmapMode", info->mipmapMode);

    LOG_NK_INT("addressModeU", info->addressModeU);
    LOG_NK_INT("addressModeV", info->addressModeV);
    LOG_NK_INT("addressModeW", info->addressModeW);

    LOG_NK_FLOAT("mipLodBias", info->mipLodBias);
    LOG_NK_UINT("anisotropyEnable", info->anisotropyEnable);
    LOG_NK_FLOAT("maxAnisotropy", info->maxAnisotropy);

    LOG_NK_UINT("compareEnable", info->compareEnable);
    LOG_NK_INT("compareOp", info->compareOp);

    LOG_NK_FLOAT("minLod", info->minLod);
    LOG_NK_FLOAT("maxLod", info->maxLod);

    LOG_NK_INT("borderColor", info->borderColor);
    LOG_NK_UINT("unnormalizedCoordinates", info->unnormalizedCoordinates);
}

void nk_glfw3_create_sampler()
{
    VkResult result;
    VkSamplerCreateInfo sampler_info;
    memset(&sampler_info, 0, sizeof(VkSamplerCreateInfo));

    sampler_info.sType = VK_STRUCTURE_TYPE_SAMPLER_CREATE_INFO;
    sampler_info.pNext = NULL;
    sampler_info.maxAnisotropy = 1.0;
    sampler_info.magFilter = VK_FILTER_LINEAR;
    sampler_info.minFilter = VK_FILTER_LINEAR;
    sampler_info.mipmapMode = VK_SAMPLER_MIPMAP_MODE_LINEAR;
    sampler_info.addressModeU = VK_SAMPLER_ADDRESS_MODE_REPEAT;
    sampler_info.addressModeV = VK_SAMPLER_ADDRESS_MODE_REPEAT;
    sampler_info.addressModeW = VK_SAMPLER_ADDRESS_MODE_REPEAT;
    sampler_info.mipLodBias = 0.0f;
    sampler_info.compareEnable = VK_FALSE;
    sampler_info.compareOp = VK_COMPARE_OP_ALWAYS;
    sampler_info.minLod = 0.0f;
    sampler_info.maxLod = 0.0f;
    sampler_info.borderColor = VK_BORDER_COLOR_FLOAT_OPAQUE_BLACK;
    /// convert to engine resource 
    result = vkCreateSampler(vk.dev, &sampler_info, NULL, &vk.texture_sampler);
#ifndef NDEBUG
    log_vk_sampler_create_info(&sampler_info);
#endif

    NK_ASSERT(result == VK_SUCCESS);
}


static void
log_vk_command_pool_create_info(const VkCommandPoolCreateInfo *info)
{
    if (info == NULL)
    {
        log_info("VkCommandPoolCreateInfo = NULL");
        return;
    }

    log_info("VkCommandPoolCreateInfo:");

    LOG_NK_INT("sType", info->sType);
    LOG_NK_POINTER("pNext", info->pNext);
    LOG_NK_FLAGS("flags", info->flags);
    LOG_NK_UINT("queueFamilyIndex", info->queueFamilyIndex);
}


void
nk_glfw3_create_command_pool()
{
    VkResult result;
    VkCommandPoolCreateInfo pool_info;
    memset(&pool_info, 0, sizeof(VkCommandPoolCreateInfo));

    pool_info.sType = VK_STRUCTURE_TYPE_COMMAND_POOL_CREATE_INFO;
    /// updated to involve VkEngine
    pool_info.queueFamilyIndex = vk.family_graphics;
    pool_info.flags = VK_COMMAND_POOL_CREATE_RESET_COMMAND_BUFFER_BIT;
    /// updated by vk.engine dev logical device and command_pool cmd_pool
    result = vkCreateCommandPool(vk.dev, &pool_info, NULL, &vk.cmd_pool);

#ifndef NDEBUG
    log_vk_command_pool_create_info(&pool_info);
#endif

    NK_ASSERT(result == VK_SUCCESS);
}


static void
log_vk_command_buffer_allocate_info(
    const VkCommandBufferAllocateInfo *info
)
{
    if (info == NULL)
    {
        log_info("VkCommandBufferAllocateInfo = NULL");
        return;
    }

    log_info("VkCommandBufferAllocateInfo:");

    LOG_NK_INT("sType", info->sType);
    LOG_NK_POINTER("pNext", info->pNext);
    LOG_VK_HANDLE("commandPool", info->commandPool);
    LOG_NK_INT("level", info->level);
    LOG_NK_UINT("commandBufferCount", info->commandBufferCount);
}


void
nk_glfw3_create_command_buffers()
{

    NK_ASSERT(vk.dev != VK_NULL_HANDLE);
    NK_ASSERT(VK_FRAMES > 0);

    VkCommandBufferAllocateInfo allocate_info;
    memset(&allocate_info, 0, sizeof(allocate_info));

    allocate_info.sType = VK_STRUCTURE_TYPE_COMMAND_BUFFER_ALLOCATE_INFO;
    allocate_info.level = VK_COMMAND_BUFFER_LEVEL_PRIMARY;
    allocate_info.commandBufferCount = 1;

    for (uint32_t i = 0; i < VK_FRAMES; ++i)
    {
        VkFrame *frame = &vk.frames[i];

        NK_ASSERT(frame->cmd_pool != VK_NULL_HANDLE);

        allocate_info.commandPool = frame->cmd_pool;

        VkResult result = vkAllocateCommandBuffers(
	    vk.dev,
            &allocate_info,
            &frame->cmd_buf
        );

#ifndef NDEBUG
        log_vk_command_buffer_allocate_info(&allocate_info);
#endif

        NK_ASSERT(result == VK_SUCCESS);

        if (result != VK_SUCCESS)
        {
            frame->cmd_buf = VK_NULL_HANDLE;
            return;
        }

        frame->id = i;
    }
}

bool
nk_vk_create_frame_buffers(
    VkDeviceSize max_vertex_buffer,
    VkDeviceSize max_element_buffer)
{
    WidgetRenderer *renderer = vk.widget_renderer;

    if (renderer == NULL ||
        vk.dev == VK_NULL_HANDLE ||
        vk.dev_physical == VK_NULL_HANDLE)
    {
        return false;
    }

    const VkMemoryPropertyFlags memory_properties =
        VK_MEMORY_PROPERTY_HOST_VISIBLE_BIT |
        VK_MEMORY_PROPERTY_HOST_COHERENT_BIT;

    /*
     * Create all buffers and allocate their device memory.
     */
    for (uint32_t i = 0; i < VK_FRAMES; ++i)
    {
        WidgetFrameData *frame = &renderer->frame[i];

        frame->vertex_buffer = VK_NULL_HANDLE;
        frame->vertex_memory = VK_NULL_HANDLE;
        frame->index_buffer = VK_NULL_HANDLE;
        frame->index_memory = VK_NULL_HANDLE;
        frame->uniform_buffer = VK_NULL_HANDLE;
        frame->uniform_memory = VK_NULL_HANDLE;

        frame->mapped_vertex = NULL;
        frame->mapped_index = NULL;
        frame->mapped_uniform = NULL;

        /*
         * Vertex data.
         */
        if (new_Buffer_DeviceMemory(
                &frame->vertex_buffer,
                &frame->vertex_memory,
                max_vertex_buffer,
                vk.dev_physical,
                vk.dev,
                VK_BUFFER_USAGE_VERTEX_BUFFER_BIT,
                memory_properties) != ERR_OK)
        {
            goto fail;
        }

        frame->max_vertex_buffer = max_vertex_buffer;

        /*
         * Index data.
         */
        if (new_Buffer_DeviceMemory(
                &frame->index_buffer,
                &frame->index_memory,
                max_element_buffer,
                vk.dev_physical,
                vk.dev,
                VK_BUFFER_USAGE_INDEX_BUFFER_BIT,
                memory_properties) != ERR_OK)
        {
            goto fail;
        }

        frame->max_index_buffer = max_element_buffer;

        /*
         * Per-frame uniform buffer.
         */
        if (new_Buffer_DeviceMemory(
                &frame->uniform_buffer,
                &frame->uniform_memory,
                sizeof(struct Mat4f),
                vk.dev_physical,
                vk.dev,
                VK_BUFFER_USAGE_UNIFORM_BUFFER_BIT,
                memory_properties) != ERR_OK)
        {
            goto fail;
        }

        frame->uniform_buffer_size = sizeof(struct Mat4f);
    }

    /*
     * Map all allocations.
     */
    for (uint32_t i = 0; i < VK_FRAMES; ++i)
    {
        WidgetFrameData *frame = &renderer->frame[i];

        if (vkMapMemory(
                vk.dev,
                frame->vertex_memory,
                0,
                frame->max_vertex_buffer,
                0,
                &frame->mapped_vertex) != VK_SUCCESS)
        {
            goto fail;
        }

        if (vkMapMemory(
                vk.dev,
                frame->index_memory,
                0,
                frame->max_index_buffer,
                0,
                &frame->mapped_index) != VK_SUCCESS)
        {
            goto fail;
        }

        if (vkMapMemory(
                vk.dev,
                frame->uniform_memory,
                0,
                frame->uniform_buffer_size,
                0,
                &frame->mapped_uniform) != VK_SUCCESS)
        {
            goto fail;
        }
    }

    return true;

fail:
    /*
     * Unmap and destroy every resource created so far.
     * vkDestroyBuffer() is safe only after the corresponding buffer
     * has been created successfully.
     */
    for (uint32_t i = 0; i < VK_FRAMES; ++i)
    {
        WidgetFrameData *frame = &renderer->frame[i];

        if (frame->mapped_vertex != NULL)
        {
            vkUnmapMemory(vk.dev, frame->vertex_memory);
            frame->mapped_vertex = NULL;
        }

        if (frame->mapped_index != NULL)
        {
            vkUnmapMemory(vk.dev, frame->index_memory);
            frame->mapped_index = NULL;
        }

        if (frame->mapped_uniform != NULL)
        {
            vkUnmapMemory(vk.dev, frame->uniform_memory);
            frame->mapped_uniform = NULL;
        }

        if (frame->vertex_buffer != VK_NULL_HANDLE)
        {
            vkDestroyBuffer(vk.dev, frame->vertex_buffer, NULL);
            frame->vertex_buffer = VK_NULL_HANDLE;
        }

        if (frame->vertex_memory != VK_NULL_HANDLE)
        {
            vkFreeMemory(vk.dev, frame->vertex_memory, NULL);
            frame->vertex_memory = VK_NULL_HANDLE;
        }

        if (frame->index_buffer != VK_NULL_HANDLE)
        {
            vkDestroyBuffer(vk.dev, frame->index_buffer, NULL);
            frame->index_buffer = VK_NULL_HANDLE;
        }

        if (frame->index_memory != VK_NULL_HANDLE)
        {
            vkFreeMemory(vk.dev, frame->index_memory, NULL);
            frame->index_memory = VK_NULL_HANDLE;
        }

        if (frame->uniform_buffer != VK_NULL_HANDLE)
        {
            vkDestroyBuffer(vk.dev, frame->uniform_buffer, NULL);
            frame->uniform_buffer = VK_NULL_HANDLE;
        }

        if (frame->uniform_memory != VK_NULL_HANDLE)
        {
            vkFreeMemory(vk.dev, frame->uniform_memory, NULL);
            frame->uniform_memory = VK_NULL_HANDLE;
        }

        frame->max_vertex_buffer = 0;
        frame->max_index_buffer = 0;
        frame->uniform_buffer_size = 0;
    }

    return false;
}


static void
log_vk_attachment_description(const VkAttachmentDescription *attachment)
{
    if (attachment == NULL) {
        log_info("VkAttachmentDescription = NULL");
        return;
    }

    log_info("VkAttachmentDescription:");

    LOG_NK_FLAGS("flags", attachment->flags);
    LOG_NK_INT("format", attachment->format);
    LOG_NK_INT("samples", attachment->samples);
    LOG_NK_INT("loadOp", attachment->loadOp);
    LOG_NK_INT("storeOp", attachment->storeOp);
    LOG_NK_INT("stencilLoadOp", attachment->stencilLoadOp);
    LOG_NK_INT("stencilStoreOp", attachment->stencilStoreOp);
    LOG_NK_INT("initialLayout", attachment->initialLayout);
    LOG_NK_INT("finalLayout", attachment->finalLayout);
}

static void
log_vk_attachment_reference(const VkAttachmentReference *reference)
{
    if (reference == NULL) {
        log_info("VkAttachmentReference = NULL");
        return;
    }

    log_info("VkAttachmentReference:");

    LOG_NK_UINT("attachment", reference->attachment);
    LOG_NK_INT("layout", reference->layout);
}

static void
log_vk_subpass_dependency(const VkSubpassDependency *dependency)
{
    if (dependency == NULL) {
        log_info("VkSubpassDependency = NULL");
        return;
    }

    log_info("VkSubpassDependency:");

    LOG_NK_UINT("srcSubpass", dependency->srcSubpass);
    LOG_NK_UINT("dstSubpass", dependency->dstSubpass);
    LOG_NK_FLAGS("srcStageMask", dependency->srcStageMask);
    LOG_NK_FLAGS("dstStageMask", dependency->dstStageMask);
    LOG_NK_FLAGS("srcAccessMask", dependency->srcAccessMask);
    LOG_NK_FLAGS("dstAccessMask", dependency->dstAccessMask);
    LOG_NK_FLAGS("dependencyFlags", dependency->dependencyFlags);
}

static void
log_vk_subpass_description(const VkSubpassDescription *subpass)
{
    if (subpass == NULL) {
        log_info("VkSubpassDescription = NULL");
        return;
    }

    log_info("VkSubpassDescription:");

    LOG_NK_FLAGS("flags", subpass->flags);
    LOG_NK_INT("pipelineBindPoint", subpass->pipelineBindPoint);

    LOG_NK_UINT("inputAttachmentCount",
                subpass->inputAttachmentCount);
    LOG_NK_POINTER("pInputAttachments",
                   subpass->pInputAttachments);

    LOG_NK_UINT("colorAttachmentCount",
                subpass->colorAttachmentCount);
    LOG_NK_POINTER("pColorAttachments",
                   subpass->pColorAttachments);

    LOG_NK_POINTER("pResolveAttachments",
                   subpass->pResolveAttachments);

    LOG_NK_POINTER("pDepthStencilAttachment",
                   subpass->pDepthStencilAttachment);

    LOG_NK_UINT("preserveAttachmentCount",
                subpass->preserveAttachmentCount);
    LOG_NK_POINTER("pPreserveAttachments",
                   subpass->pPreserveAttachments);
}

static void
log_vk_render_pass_create_info(const VkRenderPassCreateInfo *info)
{
    if (info == NULL) {
        log_info("VkRenderPassCreateInfo = NULL");
        return;
    }

    log_info("VkRenderPassCreateInfo:");

    LOG_NK_INT("sType", info->sType);
    LOG_NK_POINTER("pNext", info->pNext);
    LOG_NK_FLAGS("flags", info->flags);

    LOG_NK_UINT("attachmentCount", info->attachmentCount);
    LOG_NK_POINTER("pAttachments", info->pAttachments);

    LOG_NK_UINT("subpassCount", info->subpassCount);
    LOG_NK_POINTER("pSubpasses", info->pSubpasses);

    LOG_NK_UINT("dependencyCount", info->dependencyCount);
    LOG_NK_POINTER("pDependencies", info->pDependencies);
}

bool
nk_glfw3_create_render_pass()
{
    VkAttachmentDescription color_attachment;
    VkAttachmentReference color_reference;
    VkSubpassDependency subpass_dependency;
    VkSubpassDescription subpass_description;
    VkRenderPassCreateInfo render_pass_info;
    VkResult result;

    /*
     * The render pass is not per-frame state. The frame argument is
     * intentionally unused here because VkFrame/WidgetFrameData contain
     * command and synchronization resources, not render-pass resources.
     */


    memset(&color_attachment, 0, sizeof(color_attachment));

    color_attachment.format =
        vk.swapchain_img_format;

    color_attachment.samples =
        VK_SAMPLE_COUNT_1_BIT;

    color_attachment.loadOp =
        VK_ATTACHMENT_LOAD_OP_CLEAR;

    color_attachment.storeOp =
        VK_ATTACHMENT_STORE_OP_STORE;

    color_attachment.stencilLoadOp =
        VK_ATTACHMENT_LOAD_OP_DONT_CARE;

    color_attachment.stencilStoreOp =
        VK_ATTACHMENT_STORE_OP_DONT_CARE;

    color_attachment.initialLayout =
        VK_IMAGE_LAYOUT_UNDEFINED;

    /*
     * Swapchain images are presented after rendering.
     */
    color_attachment.finalLayout =
        VK_IMAGE_LAYOUT_PRESENT_SRC_KHR;

    memset(&color_reference, 0, sizeof(color_reference));

    color_reference.attachment = 0;
    color_reference.layout =
        VK_IMAGE_LAYOUT_COLOR_ATTACHMENT_OPTIMAL;

    memset(&subpass_dependency, 0,
           sizeof(subpass_dependency));

    subpass_dependency.srcSubpass =
        VK_SUBPASS_EXTERNAL;

    subpass_dependency.dstSubpass = 0;

    subpass_dependency.srcStageMask =
        VK_PIPELINE_STAGE_COLOR_ATTACHMENT_OUTPUT_BIT;

    subpass_dependency.dstStageMask =
        VK_PIPELINE_STAGE_COLOR_ATTACHMENT_OUTPUT_BIT;

    subpass_dependency.srcAccessMask = 0;

    subpass_dependency.dstAccessMask =
        VK_ACCESS_COLOR_ATTACHMENT_READ_BIT |
        VK_ACCESS_COLOR_ATTACHMENT_WRITE_BIT;

    memset(&subpass_description, 0,
           sizeof(subpass_description));

    subpass_description.pipelineBindPoint =
        VK_PIPELINE_BIND_POINT_GRAPHICS;

    subpass_description.colorAttachmentCount = 1;

    subpass_description.pColorAttachments =
        &color_reference;

    memset(&render_pass_info, 0,
           sizeof(render_pass_info));

    render_pass_info.sType =
        VK_STRUCTURE_TYPE_RENDER_PASS_CREATE_INFO;

    render_pass_info.attachmentCount = 1;
    render_pass_info.pAttachments = &color_attachment;

    render_pass_info.subpassCount = 1;
    render_pass_info.pSubpasses = &subpass_description;

    render_pass_info.dependencyCount = 1;
    render_pass_info.pDependencies = &subpass_dependency;

#ifndef NDEBUG
    log_vk_attachment_description(&color_attachment);
    log_vk_attachment_reference(&color_reference);
    log_vk_subpass_dependency(&subpass_dependency);
    log_vk_subpass_description(&subpass_description);
    log_vk_render_pass_create_info(&render_pass_info);
#endif

    /*
     * Destroy an old render pass if this function can be called during
     * swapchain recreation.
     */
    if (vk.renderpass != VK_NULL_HANDLE)
    {
        vkDestroyRenderPass(
            vk.dev,
            vk.renderpass,
            NULL);

        vk.renderpass = VK_NULL_HANDLE;
    }

    result = vkCreateRenderPass(
        vk.dev,
        &render_pass_info,
        NULL,
        &vk.renderpass);

    if (result != VK_SUCCESS)
    {
        fprintf(stderr,
                "vkCreateRenderPass failed: %d\n",
                result);

        vk.renderpass = VK_NULL_HANDLE;
        return false;
    }

    /*
     * The WidgetRenderer uses engine->renderpass when creating its
     * graphics pipeline. No render-pass memory is owned by a frame.
     */


    return true;
}


static void
log_vk_descriptor_pool_create_info(
    const VkDescriptorPoolCreateInfo *info
)
{
    uint32_t i;

    if (info == NULL) {
        log_info("VkDescriptorPoolCreateInfo = NULL");
        return;
    }

    log_info("VkDescriptorPoolCreateInfo:");

    LOG_NK_INT("sType", info->sType);
    LOG_NK_POINTER("pNext", info->pNext);
    LOG_NK_FLAGS("flags", info->flags);
    LOG_NK_UINT("maxSets", info->maxSets);
    LOG_NK_UINT("poolSizeCount", info->poolSizeCount);
    LOG_NK_POINTER("pPoolSizes", info->pPoolSizes);

    for (i = 0; i < info->poolSizeCount; i++) 
    {
        log_vk_descriptor_pool_size(&info->pPoolSizes[i], i);
    }
}

bool
nk_glfw3_create_descriptor_pool()
{
    VkDescriptorPoolSize pool_sizes[2];
    VkDescriptorPoolCreateInfo pool_info;
    VkResult result;

    /*
     * One uniform-buffer descriptor is needed for each frame's
     * WidgetFrameData::uniform_descriptor_set.
     */
    uint32_t uniform_descriptor_count = VK_FRAMES;

    /*
     * Texture descriptor sets are registered dynamically. The font
     * descriptor set also uses a combined image sampler, so reserve one
     * additional descriptor for it.
     */
    uint32_t texture_descriptor_count = wr.texture_descriptor_sets_capacity;

    if (texture_descriptor_count == 0)
        texture_descriptor_count = NK_GLFW_MAX_TEXTURES;

    texture_descriptor_count += 1; /* Font texture */

    memset(pool_sizes, 0, sizeof(pool_sizes));

    pool_sizes[0].type =
        VK_DESCRIPTOR_TYPE_UNIFORM_BUFFER;

    pool_sizes[0].descriptorCount =
        uniform_descriptor_count;

    pool_sizes[1].type =
        VK_DESCRIPTOR_TYPE_COMBINED_IMAGE_SAMPLER;

    pool_sizes[1].descriptorCount =
        texture_descriptor_count;

    memset(&pool_info, 0, sizeof(pool_info));

    pool_info.sType =
        VK_STRUCTURE_TYPE_DESCRIPTOR_POOL_CREATE_INFO;

    pool_info.poolSizeCount = 2;
    pool_info.pPoolSizes = pool_sizes;

    /*
     * One descriptor set per frame for the uniform buffer, one for
     * each registered texture, and one for the font texture.
     */
    pool_info.maxSets =
        uniform_descriptor_count +
        texture_descriptor_count;

    pool_info.flags =
        VK_DESCRIPTOR_POOL_CREATE_FREE_DESCRIPTOR_SET_BIT;

#ifndef NDEBUG
    log_vk_descriptor_pool_create_info(&pool_info);
#endif

    /*
     * The descriptor pool is shared and owned by VkEngine.
     */
    result = vkCreateDescriptorPool(
        vk.dev,
        &pool_info,
        NULL,
        &vk.descriptor_pool);

    if (result != VK_SUCCESS)
    {
        fprintf(stderr,
                "vkCreateDescriptorPool failed: %d\n",
                result);

        vk.descriptor_pool = VK_NULL_HANDLE;
        return false;
    }

    return true;
}

void
nk_glfw3_log_uniform_descriptor_set_layout_config(
    const VkDescriptorSetLayoutBinding *binding,
    const VkDescriptorSetLayoutCreateInfo *descriptor_set_info,
    VkResult                           result)
{
    log_info("Uniform descriptor set layout configuration:");


        LOG_VK_HANDLE("logical_device",
                      vk.dev);

        LOG_VK_HANDLE("descriptor_pool",
                      vk.descriptor_pool);

        LOG_VK_HANDLE("uniform_descriptor_set_layout",
                      wr.uniform_descriptor_set_layout);


    LOG_POINTER("binding", binding);

    if (binding)
    {
        LOG_NK_STRUCT("binding",
                      *binding);

        LOG_NK_UINT("binding.binding",
                    binding->binding);

        LOG_NK_INT("binding.descriptorType",
                   (int)binding->descriptorType);

        LOG_NK_UINT("binding.descriptorCount",
                    binding->descriptorCount);

        LOG_NK_FLAGS("binding.stageFlags",
                     binding->stageFlags);

        LOG_POINTER("binding.pImmutableSamplers",
                    binding->pImmutableSamplers);
    }

    LOG_POINTER("descriptor_set_info",
                descriptor_set_info);

    if (descriptor_set_info)
    {
        LOG_NK_STRUCT("descriptor_set_info",
                      *descriptor_set_info);

        LOG_NK_INT("descriptor_set_info.sType",
                   (int)descriptor_set_info->sType);

        LOG_POINTER("descriptor_set_info.pNext",
                    descriptor_set_info->pNext);

        LOG_NK_FLAGS("descriptor_set_info.flags",
                     descriptor_set_info->flags);

        LOG_NK_UINT("descriptor_set_info.bindingCount",
                    descriptor_set_info->bindingCount);

        LOG_POINTER("descriptor_set_info.pBindings",
                    descriptor_set_info->pBindings);
    }

    LOG_NK_INT("vkCreateDescriptorSetLayout result",
               (int)result);

    if (result == VK_SUCCESS)
    {
        LOG_VK_HANDLE("created_uniform_descriptor_set_layout",
                      wr.uniform_descriptor_set_layout);
    }
}

bool
nk_glfw3_create_uniform_descriptor_set_layout()
{
    VkDescriptorSetLayoutBinding binding;
    VkDescriptorSetLayoutCreateInfo descriptor_set_info;
    VkResult result;

    memset(&binding, 0, sizeof(binding));

    binding.binding = 0;
    binding.descriptorType = VK_DESCRIPTOR_TYPE_UNIFORM_BUFFER;
    binding.descriptorCount = 1;
    binding.stageFlags =
        VK_SHADER_STAGE_VERTEX_BIT;
    binding.pImmutableSamplers = NULL;

    memset(&descriptor_set_info, 0,
           sizeof(descriptor_set_info));

    descriptor_set_info.sType =
        VK_STRUCTURE_TYPE_DESCRIPTOR_SET_LAYOUT_CREATE_INFO;

    descriptor_set_info.bindingCount = 1;
    descriptor_set_info.pBindings = &binding;

    /*
     * The layout is a WidgetRenderer resource, but it is created using
     * the logical device owned by VkEngine.
     */
    result = vkCreateDescriptorSetLayout(
        vk.dev,
        &descriptor_set_info,
        NULL,
        &wr.uniform_descriptor_set_layout);

#ifndef NDEBUG
    nk_glfw3_log_uniform_descriptor_set_layout_config(
        &binding,
        &descriptor_set_info,
        result);
#endif

    if (result != VK_SUCCESS)
    {
        fprintf(stderr,
                "vkCreateDescriptorSetLayout for uniform buffer "
                "failed: %d\n",
                result);

        wr.uniform_descriptor_set_layout = VK_NULL_HANDLE;

        return false;
    }

    return true;
}

void
nk_glfw3_log_texture_descriptor_set_layout_config(
    const VkDescriptorSetLayoutBinding *binding,
    const VkDescriptorSetLayoutCreateInfo *descriptor_set_info,
    VkResult                           result)
{
    log_info("Texture descriptor set layout configuration:");


        LOG_VK_HANDLE("logical_device",
                      vk.dev);

        LOG_VK_HANDLE("descriptor_pool",
                      vk.descriptor_pool);


        LOG_VK_HANDLE("texture_descriptor_set_layout",
                      wr.texture_descriptor_set_layout);

    LOG_POINTER("binding", binding);

    if (binding)
    {
        LOG_NK_STRUCT("binding", *binding);

        LOG_NK_UINT("binding.binding",
                    binding->binding);

        LOG_NK_INT("binding.descriptorType",
                   (int)binding->descriptorType);

        LOG_NK_UINT("binding.descriptorCount",
                    binding->descriptorCount);

        LOG_NK_FLAGS("binding.stageFlags",
                     binding->stageFlags);

        LOG_POINTER("binding.pImmutableSamplers",
                    binding->pImmutableSamplers);
    }

    LOG_POINTER("descriptor_set_info",
                descriptor_set_info);

    if (descriptor_set_info)
    {
        LOG_NK_STRUCT("descriptor_set_info",
                      *descriptor_set_info);

        LOG_NK_INT("descriptor_set_info.sType",
                   (int)descriptor_set_info->sType);

        LOG_POINTER("descriptor_set_info.pNext",
                    descriptor_set_info->pNext);

        LOG_NK_FLAGS("descriptor_set_info.flags",
                     descriptor_set_info->flags);

        LOG_NK_UINT("descriptor_set_info.bindingCount",
                    descriptor_set_info->bindingCount);

        LOG_POINTER("descriptor_set_info.pBindings",
                    descriptor_set_info->pBindings);
    }

    LOG_NK_INT("vkCreateDescriptorSetLayout result",
               (int)result);

    if (result == VK_SUCCESS )
    {
        LOG_VK_HANDLE("created_texture_descriptor_set_layout",
                      wr.texture_descriptor_set_layout);
    }
}


 void
nk_glfw3_create_texture_descriptor_set_layout()
{
    const VkDescriptorSetLayoutBinding binding = {
        .binding            = 0,
        .descriptorType     = VK_DESCRIPTOR_TYPE_COMBINED_IMAGE_SAMPLER,
        .descriptorCount    = 1,
        .stageFlags         = VK_SHADER_STAGE_FRAGMENT_BIT,
        .pImmutableSamplers = NULL
    };

    const VkDescriptorSetLayoutCreateInfo descriptor_set_info = {
        .sType        = VK_STRUCTURE_TYPE_DESCRIPTOR_SET_LAYOUT_CREATE_INFO,
        .pNext        = NULL,
        .flags        = 0,
        .bindingCount = 1,
        .pBindings    = &binding
    };

    VkResult result = vkCreateDescriptorSetLayout(
        vk.dev,
        &descriptor_set_info,
        NULL,
        &wr.texture_descriptor_set_layout
    );

    NK_ASSERT(result == VK_SUCCESS);

    #ifndef NDEBUG
    nk_glfw3_log_texture_descriptor_set_layout_config(
    &binding,
    &descriptor_set_info,
    result
    );
    #endif
}

void
nk_glfw3_log_texture_descriptor_set_data(
    const VkDescriptorSetLayout      *descriptor_set_layouts,
    const VkDescriptorSet            *descriptor_sets,
    const VkDescriptorSetAllocateInfo *allocate_info,
    VkResult                          result)
{
    uint32_t i;
    uint32_t descriptor_set_count = 0;

        LOG_VK_HANDLE("logical_device",
                      vk.dev);

        LOG_VK_HANDLE("descriptor_pool",
                      vk.descriptor_pool);


        LOG_VK_HANDLE("texture_descriptor_set_layout",
                      wr.texture_descriptor_set_layout);

        LOG_NK_SIZE("texture_descriptor_sets_len",
                    wr.texture_descriptor_sets_len);

        LOG_NK_SIZE("texture_descriptor_sets_capacity",
                    wr.texture_descriptor_sets_capacity);

    LOG_POINTER("descriptor_set_layouts",
                descriptor_set_layouts);

    LOG_POINTER("descriptor_sets",
                descriptor_sets);

    LOG_POINTER("allocate_info",
                allocate_info);

    if (allocate_info)
    {
        descriptor_set_count = allocate_info->descriptorSetCount;

        LOG_NK_INT("allocate_info.sType",
                   (int)allocate_info->sType);

        LOG_NK_INT("allocate_info.descriptorSetCount",
                   (int)allocate_info->descriptorSetCount);

        LOG_POINTER("allocate_info.pSetLayouts",
                    allocate_info->pSetLayouts);
    }

    LOG_NK_INT("allocation_result",
               (int)result);

    if (!descriptor_set_layouts && descriptor_set_count > 0)
    {
        LOG_POINTER("descriptor_set_layouts_missing",
                    descriptor_set_layouts);
    }

    if (!descriptor_sets && descriptor_set_count > 0)
    {
        LOG_POINTER("descriptor_sets_missing",
                    descriptor_sets);
    }

    for (i = 0; i < descriptor_set_count; ++i)
    {
        LOG_NK_INT("descriptor_set_index",
                   (int)i);

        if (descriptor_set_layouts)
        {
            LOG_VK_HANDLE("descriptor_set_layout",
                          descriptor_set_layouts[i]);
        }

        if (descriptor_sets)
        {
            LOG_VK_HANDLE("descriptor_set",
                          descriptor_sets[i]);
        }


        if ( wr.texture_descriptor_sets &&
            i < wr.texture_descriptor_sets_len)
        {
            LOG_VK_HANDLE(
                "stored_descriptor_set",
                wr.texture_descriptor_sets[i].descriptor_set);

            LOG_VK_HANDLE(
                "stored_image_view",
                wr.texture_descriptor_sets[i].image_view);
        }
    }
}
void
nk_glfw3_create_texture_descriptor_sets()
{
    VkDescriptorSetLayout *layouts;
    VkDescriptorSet *descriptor_sets;
    VkDescriptorSetAllocateInfo allocate_info;
    VkResult result;
    uint32_t i;

    const uint32_t capacity = NK_GLFW_MAX_TEXTURES;

    layouts = malloc(capacity * sizeof(*layouts));
    descriptor_sets = malloc(capacity * sizeof(*descriptor_sets));

    wr.texture_descriptor_sets = malloc(capacity * sizeof(*wr.texture_descriptor_sets));

    NK_ASSERT(layouts != NULL);
    NK_ASSERT(descriptor_sets != NULL);
    NK_ASSERT(wr.texture_descriptor_sets != NULL);

    if (!layouts || !descriptor_sets ||
        !wr.texture_descriptor_sets) {
        free(layouts);
        free(descriptor_sets);
        free(wr.texture_descriptor_sets);
        wr.texture_descriptor_sets = NULL;
        return;
    }

    for (i = 0; i < capacity; ++i) 
    {
        layouts[i] = wr.texture_descriptor_set_layout;
    }

    allocate_info = (VkDescriptorSetAllocateInfo) 
    {
        .sType              = VK_STRUCTURE_TYPE_DESCRIPTOR_SET_ALLOCATE_INFO,
        .descriptorPool     = vk.descriptor_pool,
        .descriptorSetCount = capacity,
        .pSetLayouts        = layouts
    };

    result = vkAllocateDescriptorSets(
        vk.dev,
        &allocate_info,
        descriptor_sets
    );

    NK_ASSERT(result == VK_SUCCESS);

    if (result == VK_SUCCESS) 
    {
        for (i = 0; i < capacity; ++i) 
	{
            wr.texture_descriptor_sets[i] =
                (NkVulkanTextureDescriptorSet) 
		{
                    .image_view = VK_NULL_HANDLE,
                    .descriptor_set = descriptor_sets[i]
                };
        }

        wr.texture_descriptor_sets_len = 0;
        wr.texture_descriptor_sets_capacity = capacity;
    }

    free(layouts);
    free(descriptor_sets);
}

void
nk_glfw3_log_pipeline_layout_data(
    const VkPipelineLayoutCreateInfo *pipeline_layout_info,
    const VkDescriptorSetLayout      *descriptor_set_layouts,
    VkResult                          result)
{


        LOG_VK_HANDLE("logical_device",
                      vk.dev);

        LOG_VK_HANDLE("pipeline_cache",
                      vk.pipeline_cache);

        LOG_VK_HANDLE("descriptor_pool",
                      vk.descriptor_pool);


        LOG_VK_HANDLE("uniform_descriptor_set_layout",
                      wr.uniform_descriptor_set_layout);

        LOG_VK_HANDLE("texture_descriptor_set_layout",
                      wr.texture_descriptor_set_layout);

        LOG_VK_HANDLE("pipeline_layout",
                      wr.pipeline_layout);

        LOG_VK_HANDLE("pipeline",
                      wr.pipeline);

    LOG_POINTER("pipeline_layout_info",
                pipeline_layout_info);

    if (pipeline_layout_info)
    {
        LOG_NK_INT("pipeline_layout_info.sType",
                   (int)pipeline_layout_info->sType);

        LOG_NK_INT("pipeline_layout_info.flags",
                   (int)pipeline_layout_info->flags);

        LOG_NK_UINT("pipeline_layout_info.setLayoutCount",
                    pipeline_layout_info->setLayoutCount);

        LOG_POINTER("pipeline_layout_info.pSetLayouts",
                    pipeline_layout_info->pSetLayouts);

        LOG_POINTER("pipeline_layout_info.pPushConstantRanges",
                    pipeline_layout_info->pPushConstantRanges);

        LOG_NK_UINT("pipeline_layout_info.pushConstantRangeCount",
                    pipeline_layout_info->pushConstantRangeCount);
    }

    if (descriptor_set_layouts)
    {
        if (pipeline_layout_info &&
            pipeline_layout_info->setLayoutCount > 0)
        {
            LOG_VK_HANDLE("descriptor_set_layouts[0]",
                          descriptor_set_layouts[0]);
        }

        if (pipeline_layout_info &&
            pipeline_layout_info->setLayoutCount > 1)
        {
            LOG_VK_HANDLE("descriptor_set_layouts[1]",
                          descriptor_set_layouts[1]);
        }
    }

    LOG_NK_INT("vkCreatePipelineLayout result",
               (int)result);

    if (result == VK_SUCCESS)
    {
        LOG_VK_HANDLE("created_pipeline_layout",
                      wr.pipeline_layout);
    }
}


void
nk_glfw3_create_pipeline_layout()
{
    const VkDescriptorSetLayout descriptor_set_layouts[] = {
        wr.uniform_descriptor_set_layout,
        wr.texture_descriptor_set_layout
    };

    const VkPipelineLayoutCreateInfo pipeline_layout_info = {
        .sType                  = VK_STRUCTURE_TYPE_PIPELINE_LAYOUT_CREATE_INFO,
        .pNext                  = NULL,
        .flags                  = 0,
        .setLayoutCount         = 2,
        .pSetLayouts            = descriptor_set_layouts,
        .pushConstantRangeCount = 0,
        .pPushConstantRanges    = NULL
    };

    VkResult result = vkCreatePipelineLayout(
        vk.dev,
        &pipeline_layout_info,
        NULL,
        &wr.pipeline_layout
    );

#ifndef NDEBUG
    nk_glfw3_log_pipeline_layout_data(
    &pipeline_layout_info,
    descriptor_set_layouts,
    result);
#endif

    NK_ASSERT(result == VK_SUCCESS);
}


NK_INTERN void
nk_glfw3_log_pipeline_configuration(
    const VkPipelineInputAssemblyStateCreateInfo *input_assembly_state,
    const VkPipelineRasterizationStateCreateInfo *rasterization_state,
    const VkPipelineColorBlendAttachmentState    *attachment_state,
    const VkPipelineColorBlendStateCreateInfo    *color_blend_state,
    const VkPipelineViewportStateCreateInfo      *viewport_state,
    const VkPipelineMultisampleStateCreateInfo   *multisample_state,
    const VkPipelineDynamicStateCreateInfo       *dynamic_state,
    const VkDynamicState                          *dynamic_states,
    const VkPipelineShaderStageCreateInfo        *shader_stages,
    const VkVertexInputBindingDescription        *vertex_input_info,
    const VkVertexInputAttributeDescription      *vertex_attributes,
    const VkPipelineVertexInputStateCreateInfo   *vertex_input,
    const VkGraphicsPipelineCreateInfo            *pipeline_info,
    VkResult                                       result)
{
    uint32_t i;

        LOG_VK_HANDLE("logical_device",
                      vk.dev);

        LOG_VK_HANDLE("render_pass",
                      vk.renderpass);

        LOG_VK_HANDLE("pipeline_layout",
                      wr.pipeline_layout);

        LOG_VK_HANDLE("pipeline",
                      wr.pipeline);


    if (input_assembly_state)
    {
        LOG_NK_INT("input_assembly.topology",
                   (int)input_assembly_state->topology);

        LOG_NK_INT("input_assembly.primitiveRestartEnable",
                   (int)input_assembly_state->primitiveRestartEnable);
    }

    if (rasterization_state)
    {
        LOG_NK_INT("rasterization.polygonMode",
                   (int)rasterization_state->polygonMode);

        LOG_NK_FLAGS("rasterization.cullMode",
                     rasterization_state->cullMode);

        LOG_NK_INT("rasterization.frontFace",
                   (int)rasterization_state->frontFace);

        LOG_NK_FLOAT("rasterization.lineWidth",
                     rasterization_state->lineWidth);
    }

    if (attachment_state)
    {
        LOG_NK_INT("blend.blendEnable",
                   (int)attachment_state->blendEnable);

        LOG_NK_INT("blend.srcColorBlendFactor",
                   (int)attachment_state->srcColorBlendFactor);

        LOG_NK_INT("blend.dstColorBlendFactor",
                   (int)attachment_state->dstColorBlendFactor);

        LOG_NK_INT("blend.colorBlendOp",
                   (int)attachment_state->colorBlendOp);

        LOG_NK_INT("blend.srcAlphaBlendFactor",
                   (int)attachment_state->srcAlphaBlendFactor);

        LOG_NK_INT("blend.dstAlphaBlendFactor",
                   (int)attachment_state->dstAlphaBlendFactor);

        LOG_NK_INT("blend.alphaBlendOp",
                   (int)attachment_state->alphaBlendOp);

        LOG_NK_FLAGS("blend.colorWriteMask",
                     attachment_state->colorWriteMask);
    }

    if (color_blend_state)
    {
        LOG_NK_UINT("color_blend.attachmentCount",
                    color_blend_state->attachmentCount);
    }

    if (viewport_state)
    {
        LOG_NK_UINT("viewport.viewportCount",
                    viewport_state->viewportCount);

        LOG_NK_UINT("viewport.scissorCount",
                    viewport_state->scissorCount);
    }

    if (multisample_state)
    {
        LOG_NK_FLAGS("multisample.rasterizationSamples",
                     multisample_state->rasterizationSamples);
    }

    if (dynamic_state)
    {
        LOG_NK_UINT("dynamic.dynamicStateCount",
                    dynamic_state->dynamicStateCount);

        for (i = 0; i < dynamic_state->dynamicStateCount; ++i)
        {
            if (dynamic_states)
            {
                LOG_NK_INT("dynamic_state",
                           (int)dynamic_states[i]);
            }
        }
    }

    if (shader_stages)
    {
        for (i = 0; i < 2; ++i)
        {
            LOG_NK_INT("shader_stage",
                       (int)shader_stages[i].stage);

            LOG_VK_HANDLE("shader_module",
                          shader_stages[i].module);
        }
    }

    if (vertex_input_info)
    {
        LOG_NK_UINT("vertex_input.binding",
                    vertex_input_info->binding);

        LOG_NK_SIZE("vertex_input.stride",
                    vertex_input_info->stride);

        LOG_NK_INT("vertex_input.inputRate",
                   (int)vertex_input_info->inputRate);
    }

    if (vertex_attributes)
    {
        for (i = 0; i < 3; ++i)
        {
            LOG_NK_UINT("vertex_attribute.location",
                        vertex_attributes[i].location);

            LOG_NK_INT("vertex_attribute.format",
                       (int)vertex_attributes[i].format);

            LOG_NK_UINT("vertex_attribute.offset",
                        vertex_attributes[i].offset);
        }
    }

    if (vertex_input)
    {
        LOG_NK_UINT("vertex.bindingDescriptionCount",
                    vertex_input->vertexBindingDescriptionCount);

        LOG_NK_UINT("vertex.attributeDescriptionCount",
                    vertex_input->vertexAttributeDescriptionCount);
    }

    if (pipeline_info)
    {
        LOG_NK_UINT("pipeline.flags",
                    pipeline_info->flags);

        LOG_NK_UINT("pipeline.stageCount",
                    pipeline_info->stageCount);

        LOG_VK_HANDLE("pipeline.layout",
                      pipeline_info->layout);

        LOG_VK_HANDLE("pipeline.renderPass",
                      pipeline_info->renderPass);

        LOG_NK_INT("pipeline.basePipelineIndex",
                   pipeline_info->basePipelineIndex);

        LOG_VK_HANDLE("pipeline.basePipelineHandle",
                      pipeline_info->basePipelineHandle);
    }

    LOG_NK_INT("vkCreateGraphicsPipelines result",
               (int)result);

    if (result == VK_SUCCESS )
    {
        LOG_VK_HANDLE("created_pipeline",
                      wr.pipeline);
    }
}

VkPipelineShaderStageCreateInfo
nk_glfw3_create_shader_from_resource(
    VkDevice dev,
    enum Resource resource,
    VkShaderStageFlagBits stage_bit)
{
    size_t size = 0;
    void *spv_shader = res_file(resource, &size);

    NK_ASSERT(spv_shader != NULL);
    NK_ASSERT(size > 0);
    NK_ASSERT((size % sizeof(uint32_t)) == 0);

    VkShaderModuleCreateInfo create_info = {
        .sType = VK_STRUCTURE_TYPE_SHADER_MODULE_CREATE_INFO,
        .codeSize = size,
        .pCode = (const uint32_t *)spv_shader
    };

    VkShaderModule module = VK_NULL_HANDLE;

    VkResult result = vkCreateShaderModule(
        dev,
        &create_info,
        NULL,
        &module);

    /*
     * The SPIR-V file data is no longer needed after
     * vkCreateShaderModule() returns.
     */
    free(spv_shader);

    NK_ASSERT(result == VK_SUCCESS);

    VkPipelineShaderStageCreateInfo shader_info = {
        .sType =
            VK_STRUCTURE_TYPE_PIPELINE_SHADER_STAGE_CREATE_INFO,
        .stage = stage_bit,
        .module = module,
        .pName = "main"
    };

    return shader_info;
}


void
nk_glfw3_create_pipeline()
{
    VkPipelineInputAssemblyStateCreateInfo input_assembly_state = {
        .sType = VK_STRUCTURE_TYPE_PIPELINE_INPUT_ASSEMBLY_STATE_CREATE_INFO,
        .topology = VK_PRIMITIVE_TOPOLOGY_TRIANGLE_LIST,
        .primitiveRestartEnable = VK_FALSE
    };

    VkPipelineRasterizationStateCreateInfo rasterization_state = {
        .sType = VK_STRUCTURE_TYPE_PIPELINE_RASTERIZATION_STATE_CREATE_INFO,
        .polygonMode = VK_POLYGON_MODE_FILL,
        .cullMode = VK_CULL_MODE_NONE,
        .frontFace = VK_FRONT_FACE_COUNTER_CLOCKWISE,
        .lineWidth = 1.0f
    };

    VkPipelineColorBlendAttachmentState attachment_state = {
        .blendEnable = VK_TRUE,
        .srcColorBlendFactor = VK_BLEND_FACTOR_SRC_ALPHA,
        .dstColorBlendFactor = VK_BLEND_FACTOR_ONE_MINUS_SRC_ALPHA,
        .colorBlendOp = VK_BLEND_OP_ADD,
        .srcAlphaBlendFactor = VK_BLEND_FACTOR_SRC_ALPHA,
        .dstAlphaBlendFactor = VK_BLEND_FACTOR_ONE,
        .alphaBlendOp = VK_BLEND_OP_ADD,
        .colorWriteMask =
            VK_COLOR_COMPONENT_R_BIT |
            VK_COLOR_COMPONENT_G_BIT |
            VK_COLOR_COMPONENT_B_BIT |
            VK_COLOR_COMPONENT_A_BIT
    };

    VkPipelineColorBlendStateCreateInfo color_blend_state = {
        .sType = VK_STRUCTURE_TYPE_PIPELINE_COLOR_BLEND_STATE_CREATE_INFO,
        .attachmentCount = 1,
        .pAttachments = &attachment_state
    };

    VkPipelineViewportStateCreateInfo viewport_state = {
        .sType = VK_STRUCTURE_TYPE_PIPELINE_VIEWPORT_STATE_CREATE_INFO,
        .viewportCount = 1,
        .scissorCount = 1
    };

    VkPipelineMultisampleStateCreateInfo multisample_state = {
        .sType = VK_STRUCTURE_TYPE_PIPELINE_MULTISAMPLE_STATE_CREATE_INFO,
        .rasterizationSamples = VK_SAMPLE_COUNT_1_BIT
    };

    VkDynamicState dynamic_states[] = {
        VK_DYNAMIC_STATE_VIEWPORT,
        VK_DYNAMIC_STATE_SCISSOR
    };

    VkPipelineDynamicStateCreateInfo dynamic_state = {
        .sType = VK_STRUCTURE_TYPE_PIPELINE_DYNAMIC_STATE_CREATE_INFO,
        .dynamicStateCount = 2,
        .pDynamicStates = dynamic_states
    };

    VkVertexInputBindingDescription vertex_binding = {
        .binding = 0,
        .stride = sizeof(struct NkVertex),
        .inputRate = VK_VERTEX_INPUT_RATE_VERTEX
    };

    VkVertexInputAttributeDescription vertex_attributes[3] = {
        {
            .location = 0,
            .binding = 0,
            .format = VK_FORMAT_R32G32_SFLOAT,
            .offset = NK_OFFSETOF(struct NkVertex, pos)
        },
        {
            .location = 1,
            .binding = 0,
            .format = VK_FORMAT_R32G32_SFLOAT,
            .offset = NK_OFFSETOF(struct NkVertex, uv)
        },
        {
            .location = 2,
            .binding = 0,
            .format = VK_FORMAT_R8G8B8A8_UINT,
            .offset = NK_OFFSETOF(struct NkVertex, color)
        }
    };

    VkPipelineVertexInputStateCreateInfo vertex_input = {
        .sType =
            VK_STRUCTURE_TYPE_PIPELINE_VERTEX_INPUT_STATE_CREATE_INFO,
        .vertexBindingDescriptionCount = 1,
        .pVertexBindingDescriptions = &vertex_binding,
        .vertexAttributeDescriptionCount = 3,
        .pVertexAttributeDescriptions = vertex_attributes
    };

    VkPipelineShaderStageCreateInfo shader_stages[2];

    shader_stages[0] =
	nk_glfw3_create_shader_from_resource(
	    vk.dev,
	    RES_NUKLEAR_VERT_GUI,
	    VK_SHADER_STAGE_VERTEX_BIT);

    shader_stages[1] =
	nk_glfw3_create_shader_from_resource(
	    vk.dev,
	    RES_NUKLEAR_FRAG_GUI,
	    VK_SHADER_STAGE_FRAGMENT_BIT);

    VkGraphicsPipelineCreateInfo pipeline_info = {
        .sType = VK_STRUCTURE_TYPE_GRAPHICS_PIPELINE_CREATE_INFO,
        .stageCount = 2,
        .pStages = shader_stages,
        .pVertexInputState = &vertex_input,
        .pInputAssemblyState = &input_assembly_state,
        .pViewportState = &viewport_state,
        .pRasterizationState = &rasterization_state,
        .pMultisampleState = &multisample_state,
        .pColorBlendState = &color_blend_state,
        .pDynamicState = &dynamic_state,

        .layout = wr.pipeline_layout,
        .renderPass = vk.renderpass,
        .subpass = 0,

        .basePipelineHandle = VK_NULL_HANDLE,
        .basePipelineIndex = -1
    };

    VkResult result = vkCreateGraphicsPipelines(
        vk.dev,
        vk.pipeline_cache,
        1,
        &pipeline_info,
        NULL,
        &wr.pipeline);

    NK_ASSERT(result == VK_SUCCESS);


    #ifndef NDEBUG
    nk_glfw3_log_pipeline_configuration(
	&input_assembly_state,
	&rasterization_state,
	&attachment_state,
	&color_blend_state,
	&viewport_state,
	&multisample_state,
	&dynamic_state,
	dynamic_states,
	shader_stages,
	&vertex_binding,
	vertex_attributes,
	&vertex_input,
	&pipeline_info,
	result);    
    #endif


    vkDestroyShaderModule(
        vk.dev,
        shader_stages[0].module,
        NULL);

    vkDestroyShaderModule(
        vk.dev,
        shader_stages[1].module,
        NULL);
}




//! \note MAX_VERTEXES operates as max for GUI and if crash happens  this is the cause
#define MAX_VERTEXES 64000


WidgetRendererHandle
WidgetRendererInit(struct VkEngine *vk)
{

    WidgetRendererHandle handle = handle_alloc(&alloc);
    
    // aim VkEngine at static widget_renderer local static
    vk->widget_renderer = &wr;
    /// aims at same &wr local data
    WidgetRenderer * renderer = vk->widget_renderer;

    // window was initialized beforehand
    renderer->window = vk->window;

    /*
     * Window dimensions.
     */
    glfwGetWindowSize(
        renderer->window,
        &renderer->width,
        &renderer->height);

    glfwGetFramebufferSize(
        renderer->window,
        &renderer->display_width,
        &renderer->display_height);

    renderer->fb_scale.x =
        renderer->width > 0
            ? (float)renderer->display_width /
              (float)renderer->width
            : 1.0f;

    renderer->fb_scale.y =
        renderer->height > 0
            ? (float)renderer->display_height /
              (float)renderer->height
            : 1.0f;

    /*
     * Input state.
     */
    renderer->callbacks_installed = false;

    renderer->previous_scroll_callback = NULL;
    renderer->previous_char_callback = NULL;
    renderer->previous_key_callback = NULL;
    renderer->previous_mouse_button_callback = NULL;

    renderer->scroll.x = 0.0f;
    renderer->scroll.y = 0.0f;

    renderer->text_len = 0;
    renderer->last_button_click = 0.0;
    renderer->is_double_click_down = 0;

    renderer->double_click_pos.x = 0.0f;
    renderer->double_click_pos.y = 0.0f;

    renderer->delta_time_seconds_last = 0.0f;

    /*
     * Application state.
     */
    renderer->demo_operation = 0;
    renderer->compression = 0;

    renderer->background.r = 0.10f;
    renderer->background.g = 0.10f;
    renderer->background.b = 0.10f;
    renderer->background.a = 1.00f;




    /*
     * Vulkan handles.
     */
    renderer->pipeline = VK_NULL_HANDLE;
    renderer->pipeline_layout = VK_NULL_HANDLE;

    renderer->uniform_descriptor_set_layout = VK_NULL_HANDLE;
    renderer->texture_descriptor_set_layout = VK_NULL_HANDLE;

    renderer->font_image = VK_NULL_HANDLE;
    renderer->font_alloc = NULL;
    renderer->font_image_view = VK_NULL_HANDLE;
    renderer->font_descriptor_set = VK_NULL_HANDLE;

    renderer->vertex_gpu_buffer = VK_NULL_HANDLE;
    renderer->vertex_gpu_alloc = NULL;

    renderer->index_gpu_buffer = VK_NULL_HANDLE;
    renderer->index_gpu_alloc = NULL;

    /*
     * Dynamic arrays.
     */
    renderer->texture_descriptor_sets = NULL;
    renderer->texture_descriptor_sets_len = 0;
    renderer->texture_descriptor_sets_capacity = 0;

    renderer->quad_count = 0;
    renderer->quad_vertices = NULL;
    renderer->quad_vertex_capacity = 0;

    /*
     * Per-frame resources.
     */
    for (uint32_t i = 0; i < VK_FRAMES; ++i)
    {
        struct WidgetFrameData *frame = &renderer->frame[i];

        frame->uniform_buffer = VK_NULL_HANDLE;
        frame->uniform_alloc = NULL;
        frame->mapped_uniform = NULL;
        frame->uniform_descriptor_set = VK_NULL_HANDLE;

        frame->vertex_buffer = VK_NULL_HANDLE;
        frame->vertex_alloc = NULL;
        frame->mapped_vertex = NULL;

        frame->index_buffer = VK_NULL_HANDLE;
        frame->index_alloc = NULL;
        frame->mapped_index = NULL;

        frame->max_vertex_buffer  = 0;	// maximum vertexes by count this memory vertex_buffer can hold
        frame->max_index_buffer = 0; // maximum indexes by count this memory index_buffer can hold
        frame->uniform_buffer_size = 0; // maximum sizeof this memory uniform_buffer can hold

        frame->index_count = 0;
        frame->width = 0;
        frame->height = 0;
    }


    memset(
        &renderer->nk_allocator,
        0,
        sizeof(renderer->nk_allocator));

    memset(
        &renderer->convert_config,
        0,
        sizeof(renderer->convert_config));
    
    // safety for use to stop rendering without data
    renderer->nk_initialized = false;

    glfwSetWindowUserPointer(renderer->window, renderer);

    glfwSetScrollCallback(
	renderer->window,
	nk_glfw3_scroll_callback);

    glfwSetCharCallback(
	renderer->window,
	nk_glfw3_char_callback);

    glfwSetKeyCallback(
	renderer->window,
	nk_glfw3_key_callback);

    glfwSetMouseButtonCallback(
	renderer->window,
	nk_glfw3_mouse_button_callback);

    renderer->callbacks_installed = true;    

    renderer->ctx.clip.copy = nk_glfw3_clipboard_copy;
    renderer->ctx.clip.paste = nk_glfw3_clipboard_paste;
    renderer->ctx.clip.userdata = nk_handle_ptr(renderer);	

    /*
     * WidgetRenderer creates and owns its own Vulkan resources using
     * renderer->vk. VkEngine-owned resources remain owned by VkEngine.
     */

    
    /*
     * Nuklear buff;ers and state. Creates Vulkan resources
     */
    if (nk_init(&renderer->ctx,
                &renderer->nk_allocator,
                NULL) != VK_SUCCESS)
    {
        return -1;
    }
    
     
    nk_buffer_init_default(&renderer->cmds);
    nk_buffer_init_default(&renderer->vertex_nk_buffer);
    nk_buffer_init_default(&renderer->index_nk_buffer);
    // NUKLEAR_GLFW_VULKAN GUI INIT
    // modified original initialization in the correct order
    nk_glfw3_create_sampler();
    nk_glfw3_create_command_pool();
    nk_glfw3_create_command_buffers();    
    // final GUI construction
    nk_glfw3_create_render_pass();    
    // nk_glfw3_create_semaphore unneeded because VkEngine owns synchronization
    /// DRE newer functions are less copies more improved for the better design
    nk_vk_create_frame_buffers( MAX_VERTEXES,  MAX_VERTEXES);
    nk_glfw3_create_descriptor_pool();
    nk_glfw3_create_uniform_descriptor_set_layout();
    nk_glfw3_create_texture_descriptor_set_layout();
    nk_glfw3_create_texture_descriptor_sets();
    nk_glfw3_create_pipeline_layout();    
    nk_glfw3_create_pipeline();    
    
    // store font atlas
    WidgetInstallFonts();
    
    return handle;
}
///
//  DESTROYERS
///

void
nk_vk_destroy_frame_buffers(void)
{
    if (vk.dev == VK_NULL_HANDLE)
    {
        return;
    }

    /*
     * Make sure no frame resources are still in use before destroying them.
     * The caller may also perform this wait before calling this function.
     */
    vkDeviceWaitIdle(vk.dev);

    for (uint32_t i = 0; i < VK_FRAMES; ++i)
    {
        VkFrame *frame = &vk.frames[i];

        /*
         * Destroying the command pool also frees all command buffers
         * allocated from it, including frame->cmd_buf.
         */
        if (frame->cmd_pool != VK_NULL_HANDLE)
        {
            vkDestroyCommandPool(
                vk.dev,
                frame->cmd_pool,
                NULL);

            frame->cmd_pool = VK_NULL_HANDLE;
            frame->cmd_buf  = VK_NULL_HANDLE;
        }

        if (frame->image_available != VK_NULL_HANDLE)
        {
            vkDestroySemaphore(
                vk.dev,
                frame->image_available,
                NULL);

            frame->image_available = VK_NULL_HANDLE;
        }

        if (frame->render_finished != VK_NULL_HANDLE)
        {
            vkDestroySemaphore(
                vk.dev,
                frame->render_finished,
                NULL);

            frame->render_finished = VK_NULL_HANDLE;
        }

        if (frame->nk_render_finished != VK_NULL_HANDLE)
        {
            vkDestroySemaphore(
                vk.dev,
                frame->nk_render_finished,
                NULL);

            frame->nk_render_finished = VK_NULL_HANDLE;
        }

        if (frame->flight != VK_NULL_HANDLE)
        {
            vkDestroyFence(
                vk.dev,
                frame->flight,
                NULL);

            frame->flight = VK_NULL_HANDLE;
        }

        frame->id          = 0;
        frame->image_index = 0;
    }
}

