#ifndef WIDGET_RENDERER_H
#define WIDGET_RENDERER_H

#include <stdbool.h>
#include <stdint.h>

#include <vulkan/vulkan.h>
#include "common.h"
#include "../handle/handle.h"
#include "../gfx/vk_util.h"
#include "event/event.h"

#include "nuklear_config.h"
#include "nuklear.h"


/*
 * Forward declarations.
 *
 * The contents of these structures remain private to widget_renderer.c.
 */
typedef struct VkEngine VkEngine;
typedef struct VkFrame VkFrame;
typedef struct WidgetRenderer WidgetRenderer;
typedef struct VkRenderer VkRenderer;
typedef struct WidgetFrameData WidgetFrameData;

/*
 * Handle used by the engine/application to refer to a renderer.
 */
typedef Handle WidgetRendererHandle;


/*
 * Create and initialize the Nuklear widget renderer.
 *
 * Vulkan device, allocator, swapchain-related state, and descriptor
 * infrastructure should already be initialized before this call.
 */
WidgetRendererHandle
WidgetRendererInit(struct VkEngine *vk);


/*
 * Build the Nuklear widget command list for the current frame.
 *
 * This function may call:
 *
 *     nk_glfw3_new_frame()
 *     nk_begin()
 *     nk_layout_row_...()
 *     nk_button_...()
 *     nk_property_...()
 *     nk_combo_...()
 *     nk_draw_image()
 *     nk_end()
 *
 * It should not record Vulkan draw commands.
 */
void
WidgetRendererBuildWidgets();

/*
 * Optional combined UI update function.
 *
 * Use this only if input processing and widget construction are
 * intentionally combined.
 */
bool
WidgetRendererLoop(void);

void
WidgetInstallFonts(void);

void
WidgetRendererDestroy(WidgetRendererHandle handle);

bool WidgetRendererRecord(
    WidgetRenderer *renderer,
    VkEngine *engine,
    VkFrame *vk_frame,
    WidgetFrameData *ui_frame);
    

bool WidgetRendererUpdate(struct Frame *frame);
    

NK_INTERN void
nk_glfw3_clipboard_copy(nk_handle usr,
                        const char *text,
                        int len);

NK_INTERN void
nk_glfw3_clipboard_paste(nk_handle usr,
                         struct nk_text_edit *edit);
    
NK_API void nk_glfw3_char_callback(GLFWwindow *win, unsigned int codepoint);
NK_API void nk_glfw3_key_callback(GLFWwindow *win, int key, int scancode, int action, int mods);
NK_API void nk_glfw3_scroll_callback(GLFWwindow *win, double xoff, double yoff);
NK_API void nk_glfw3_mouse_button_callback(GLFWwindow *win, int button, int action, int mods);    

#endif /* WIDGET_RENDERER_H */
